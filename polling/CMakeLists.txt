cmake_minimum_required(VERSION 3.13)

# Always include it
include(pico_sdk_import.cmake)

# Project's name
project(lab04_polling)

# SDK Initialization - Mandatory
pico_sdk_init()

# C/C++ project files
add_executable(lab04_polling
    main.c
    functions.c
)

# pico_stdlib library. You can add more if they are needed
target_link_libraries(lab04_polling
    pico_stdlib
    hardware_timer
)

pico_enable_stdio_usb(lab04_polling 1)
pico_enable_stdio_uart(lab04_polling 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(lab04_polling)
