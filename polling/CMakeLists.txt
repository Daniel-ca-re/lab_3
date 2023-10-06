cmake_minimum_required(VERSION 3.13)

# Always include it
include(pico_sdk_import.cmake)

# Project's name
project(polling)

# SDK Initialization - Mandatory
pico_sdk_init()

# C/C++ project files
add_executable(polling
    main.c
    funtions.c
)

# pico_stdlib library. You can add more if they are needed
target_link_libraries(polling
    pico_stdlib
    hardware_timer
)
target_include_directories(polling PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
pico_enable_stdio_usb(polling 1)
pico_enable_stdio_uart(polling 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(polling)