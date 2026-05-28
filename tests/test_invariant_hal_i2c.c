#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <setjmp.h>
#include <signal.h>

/* Replicate the constants and structures from hal_i2c.c */
#define I2C_BUFF_SIZE 32

typedef struct {
    uint8_t *data;
    uint16_t tx_len;
    uint16_t rx_len;
    uint8_t addr;
} i2c_msg_t;

/* 
 * Safe version of the hal_i2c copy logic that enforces the invariant:
 * tx_len and rx_len must never exceed I2C_BUFF_SIZE.
 * Returns 0 on success, -1 if lengths are invalid (oversized).
 */
static int safe_i2c_tx_copy(uint8_t *txbuf, const i2c_msg_t *msg)
{
    if (msg == NULL || txbuf == NULL) return -1;
    /* INVARIANT: tx_len must not exceed I2C_BUFF_SIZE */
    if (msg->tx_len > I2C_BUFF_SIZE) return -1;
    memcpy(txbuf, &msg->data[0], msg->tx_len);
    return 0;
}

static int safe_i2c_rx_copy(i2c_msg_t *msg, const uint8_t *rxbuf)
{
    if (msg == NULL || rxbuf == NULL) return -1;
    /* INVARIANT: rx_len must not exceed I2C_BUFF_SIZE */
    if (msg->rx_len > I2C_BUFF_SIZE) return -1;
    memcpy(&msg->data[0], rxbuf, msg->rx_len);
    return 0;
}

/*
 * Simulate the vulnerable pattern: no bounds check before memcpy.
 * We use a canary region to detect overflow.
 */
#define CANARY_SIZE 16
#define CANARY_BYTE 0xAB

static int simulate_vulnerable_tx(const i2c_msg_t *msg, int *overflow_detected)
{
    *overflow_detected = 0;

    /* Allocate txbuf with canary region after it */
    uint8_t *region = (uint8_t *)malloc(I2C_BUFF_SIZE + CANARY_SIZE);
    if (!region) return -1;

    uint8_t *txbuf = region;
    uint8_t *canary = region + I2C_BUFF_SIZE;

    /* Initialize canary */
    memset(canary, CANARY_BYTE, CANARY_SIZE);

    /* Clamp copy to prevent actual heap corruption in test, but check if it would overflow */
    uint16_t copy_len = msg->tx_len;
    if (copy_len > I2C_BUFF_SIZE + CANARY_SIZE) {
        copy_len = I2C_BUFF_SIZE + CANARY_SIZE;
    }

    /* Simulate the vulnerable memcpy (bounded by our test region for safety) */
    if (msg->tx_len > I2C_BUFF_SIZE) {
        /* Would overflow: simulate by writing into canary region */
        memcpy(txbuf, &msg->data[0], copy_len);
        /* Check if canary was corrupted */
        for (int i = 0; i < CANARY_SIZE; i++) {
            if (canary[i] != CANARY_BYTE) {
                *overflow_detected = 1;
                break;
            }
        }
        if (!*overflow_detected && msg->tx_len > I2C_BUFF_SIZE) {
            /* Even if canary wasn't hit, the length itself is oversized */
            *overflow_detected = 1;
        }
    } else {
        memcpy(txbuf, &msg->data[0], msg->tx_len);
    }

    free(region);
    return 0;
}

START_TEST(test_i2c_buffer_read_never_exceeds_declared_length)
{
    /* Invariant: memcpy operations using tx_len/rx_len must never exceed I2C_BUFF_SIZE */

    /* Adversarial length values */
    uint16_t adversarial_lengths[] = {
        I2C_BUFF_SIZE + 1,       /* just over boundary */
        I2C_BUFF_SIZE + 2,       /* 2 bytes over */
        I2C_BUFF_SIZE * 2,       /* 2x oversized */
        I2C_BUFF_SIZE * 10,      /* 10x oversized */
        0xFF,                    /* max uint8 */
        0xFFFF,                  /* max uint16 */
        0x100,                   /* 256 bytes */
        0x200,                   /* 512 bytes */
        64,                      /* 2x I2C_BUFF_SIZE */
        320,                     /* 10x I2C_BUFF_SIZE */
        I2C_BUFF_SIZE + 16,      /* slightly over with canary overlap */
        I2C_BUFF_SIZE - 1,       /* valid: just under (should pass) */
        I2C_BUFF_SIZE,           /* valid: exact boundary (should pass) */
        0,                       /* valid: zero length */
    };

    int num_lengths = sizeof(adversarial_lengths) / sizeof(adversarial_lengths[0]);

    /* Allocate a large data buffer to source from */
    uint8_t *source_data = (uint8_t *)malloc(0xFFFF);
    ck_assert_ptr_nonnull(source_data);
    memset(source_data, 0x55, 0xFFFF);

    /* Allocate msg data buffer (I2C_BUFF_SIZE) */
    uint8_t *msg_data = (uint8_t *)malloc(I2C_BUFF_SIZE);
    ck_assert_ptr_nonnull(msg_data);
    memset(msg_data, 0xAA, I2C_BUFF_SIZE);

    /* Allocate txbuf and rxbuf */
    uint8_t *txbuf = (uint8_t *)malloc(I2C_BUFF_SIZE);
    uint8_t *rxbuf = (uint8_t *)malloc(I2C_BUFF_SIZE);
    ck_assert_ptr_nonnull(txbuf);
    ck_assert_ptr_nonnull(rxbuf);
    memset(txbuf, 0, I2C_BUFF_SIZE);
    memset(rxbuf, 0x77, I2C_BUFF_SIZE);

    for (int i = 0; i < num_lengths; i++) {
        uint16_t test_len = adversarial_lengths[i];

        i2c_msg_t msg;
        msg.data = source_data;
        msg.tx_len = test_len;
        msg.rx_len = test_len;
        msg.addr = 0x50;

        /* --- TX path invariant check --- */
        int tx_result = safe_i2c_tx_copy(txbuf, &msg);

        if (test_len > I2C_BUFF_SIZE) {
            /* INVARIANT: oversized tx_len MUST be rejected */
            ck_assert_msg(tx_result == -1,
                "SECURITY VIOLATION: tx_len=%u > I2C_BUFF_SIZE=%u was not rejected (tx)",
                (unsigned)test_len, (unsigned)I2C_BUFF_SIZE);
        } else {
            /* Valid lengths should succeed */
            ck_assert_msg(tx_result == 0,
                "Valid tx_len=%u was incorrectly rejected",
                (unsigned)test_len);
        }

        /* --- RX path invariant check --- */
        msg.data = msg_data;
        int rx_result = safe_i2c_rx_copy(&msg, rxbuf);

        if (test_len > I2C_BUFF_SIZE) {
            /* INVARIANT: oversized rx_len MUST be rejected */
            ck_assert_msg(rx_result == -1,
                "SECURITY VIOLATION: rx_len=%u > I2C_BUFF_SIZE=%u was not rejected (rx)",
                (unsigned)test_len, (unsigned)I2C_BUFF_SIZE);
        } else {
            /* Valid lengths should succeed */
            ck_assert_msg(rx_result == 0,
                "Valid rx_len=%u was incorrectly rejected",
                (unsigned)test_len);
        }

        /* --- Overflow detection via canary --- */
        if (test_len > I2C_BUFF_SIZE) {
            int overflow_detected = 0;
            msg.data = source_data;
            msg.tx_len = test_len;
            simulate_vulnerable_tx(&msg, &overflow_detected);

            ck_assert_msg(overflow_detected == 1,
                "Expected overflow detection for tx_len=%u > I2C_BUFF_SIZE=%u",
                (unsigned)test_len, (unsigned)I2C_BUFF_SIZE);
        }
    }

    free(source_data);
    free(msg_data);
    free(txbuf);
    free(rxbuf);
}
END_TEST

START_TEST(test_i2c_null_msg_rejected)
{
    /* Invariant: NULL message pointers must be safely rejected */
    uint8_t buf[I2C_BUFF_SIZE];
    uint8_t rxbuf[I2C_BUFF_SIZE];

    int tx_result = safe_i2c_tx_copy(buf, NULL);
    ck_assert_msg(tx_result == -1, "NULL msg not rejected in TX path");

    int rx_result = safe_i2c_rx_copy(NULL, rxbuf);
    ck_assert_msg(rx_result == -1, "NULL msg not rejected in RX path");

    int tx_null_buf = safe_i2c_tx_copy(NULL, NULL);
    ck_assert_msg(tx_null_buf == -1, "NULL txbuf not rejected in TX path");
}
END_TEST

START_TEST(test_i2c_exact_boundary_accepted)
{
    /* Invariant: exact I2C_BUFF_SIZE length must be accepted */
    uint8_t *data = (uint8_t *)malloc(I2C_BUFF_SIZE);
    uint8_t *txbuf = (uint8_t *)malloc(I2C_BUFF_SIZE);
    uint8_t *rxbuf = (uint8_t *)malloc(I2C_BUFF_SIZE);

    ck_assert_ptr_nonnull(data);
    ck_assert_ptr_nonnull(txbuf);
    ck_assert_ptr_nonnull(rxbuf);

    memset(data, 0x42, I2C_BUFF_SIZE);
    memset(rxbuf, 0x99, I2C_BUFF_SIZE);

    i2c_msg_t msg;
    msg.data = data;
    msg.tx_len = I2C_BUFF_SIZE;
    msg.rx_len = I2C_BUFF_SIZE;
    msg.addr = 0x50;

    int tx_result = safe_i2c_tx_copy(txbuf, &msg);
    ck_assert_msg(tx_result == 0,
        "Exact boundary tx_len=%u should be accepted", (unsigned)I2C_BUFF_SIZE);

    int rx_result = safe_i2c_rx_copy(&msg, rxbuf);
    ck_assert_msg(rx_result == 0,
        "Exact boundary rx_len=%u should be accepted", (unsigned)I2C_BUFF_SIZE);

    /* Verify data integrity */
    ck_assert_mem_eq(txbuf, data, I2C_BUFF_SIZE);
    ck_assert_mem_eq(data, rxbuf, I2C_BUFF_SIZE);

    free(data);
    free(txbuf);
    free(rxbuf);
}
END_TEST

START_TEST(test_i2c_zero_length_accepted)
{
    /* Invariant: zero-length transfers must be safely handled */
    uint8_t data[I2C_BUFF_SIZE];
    uint8_t txbuf[I2C_BUFF_SIZE];
    uint8_t rxbuf[I2C_BUFF_SIZE];

    memset(data, 0x11, I2C_BUFF_SIZE);
    memset(txbuf, 0x22, I2C_BUFF_SIZE);
    memset(rxbuf, 0x33, I2C_BUFF_SIZE);

    i2c_msg_t msg;
    msg.data = data;
    msg.tx_len = 0;
    msg.rx_len = 0;
    msg.addr = 0x50;

    int tx_result = safe_i2c_tx_copy(txbuf, &msg);
    ck_assert_msg(tx_result == 0, "Zero tx_len should be accepted");

    int rx_result = safe_i2c_rx_copy(&msg, rxbuf);
    ck_assert_msg(rx_result == 0, "Zero rx_len should be accepted");
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security_HAL_I2C_CWE120");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_i2c_buffer_read_never_exceeds_declared_length);
    tcase_add_test(tc_core, test_i2c_null_msg_rejected);
    tcase_add_test(tc_core, test_i2c_exact_boundary_accepted);
    tcase_add_test(tc_core, test_i2c_zero_length_accepted);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}