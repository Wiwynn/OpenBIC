
enum stage {
	POST_MODE = 1,
	SMM_MODE,
};

typedef struct _kcs_config {
    char *name;
    uint8_t stage;
} kcs_config;

static kcs_config kcs_port[] = {
	{ .name = "KCS3", .stage = POST_MODE},
	{ .name = "KCS2", .stage = SMM_MODE},
};

void plat_kcs_init(void)
{
	LOG_INF("%s", __func__);

	for (uint8_t i = 0; i < ARRAY_SIZE(kcs_port); i++) {
		LOG_INF("%s Wiwynn Debug - %s", __func__, kcs_port[i].name);
		kcs_start(kcs_port[i].name);
	}
}