cmake_minimum_required(VERSION 3.13)

# Initialize pico-sdk from submodule
include(pico-sdk/pico_sdk_init.cmake)

# Define project
project(rp2040_light_sensor)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add sources to executable
add_executable(rp2040_light_sensor
    hello_world.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(rp2040-light-sensor pico_stdlib)

# Create map/bin/hex/uf2 file in addition to elf
pico_add_extra_outputs(rp2040_light_sensor)