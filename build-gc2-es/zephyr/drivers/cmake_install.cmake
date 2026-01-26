# Install script for directory: /home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/zephyr/drivers

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/opt/toolchains/zephyr-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/console/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/interrupt_controller/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/misc/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/pcie/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/disk/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/adc/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/clock_control/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/reset_control/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/gpio/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/i2c/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/ipmi/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/pinmux/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/sensor/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/spi/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/usb/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/watchdog/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/hwinfo/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/espi/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/peci/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/jtag/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/flash/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/serial/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/timer/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/cache/cmake_install.cmake")
  include("/home/pablo1997/MyAllProject/ZephyrOpenbic/TestGc2Bic_0102/OpenBIC/build-gc2-es/zephyr/drivers/i3c/cmake_install.cmake")

endif()

