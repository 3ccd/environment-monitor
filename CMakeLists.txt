cmake_minimum_required(VERSION 3.13...3.27)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(environment-monitor)

set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h CACHE STRING "" FORCE)
add_subdirectory(external/lvgl)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

include_directories(environment-monitor
        ${PROJECT_SOURCE_DIR}/include)

# rest of your project
add_executable(environment-monitor
        src/bmp280_i2c.c
        src/st7789.c
        src/main.c
        src/graphics.c
)

# pull in common dependencies and additional spi hardware support
target_link_libraries(environment-monitor pico_stdlib hardware_i2c hardware_spi)
target_link_libraries(environment-monitor lvgl)

pico_add_extra_outputs(environment-monitor)

pico_enable_stdio_usb(environment-monitor 1)
pico_enable_stdio_uart(environment-monitor 0)
