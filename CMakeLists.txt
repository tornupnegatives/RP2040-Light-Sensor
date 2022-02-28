# Configure CMake
cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize pico_sdk from submodule
include(pico-sdk/pico_sdk_init.cmake)

# Define project
project(rp2040_light_sensor C CXX ASM)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add sources to executable
include_directories(inc)
add_executable(rp2040_light_sensor
        src/main.c
)

# Enable warnings
target_compile_options(rp2040_light_sensor PUBLIC -Werror -Wall -Wextra)

# Executable metadata
pico_set_program_name(rp2040_light_sensor "rp2040_light_sensor")
#pico_set_program_description(foo "this is a foo")
pico_set_program_version(rp2040_light_sensor "0.1")
#pico_set_program_url(foo "www.plinth.com/foo")

# Enable floating point support
pico_set_float_implementation(rp2040_light_sensor pico)

# Enable double support
#pico_set_double_implementation(rp2040_light_sensor pico)

# Redirect IO to USB serial (1 to enable, 0 to disable)
pico_enable_stdio_usb(rp2040_light_sensor 1)
pico_enable_stdio_uart(rp2040_light_sensor 0)

# Add libraries
target_link_libraries(rp2040_light_sensor 
        pico_stdlib
)

# Create map/bin/hex/uf2 file in addition to elf
pico_add_extra_outputs(rp2040_light_sensor)