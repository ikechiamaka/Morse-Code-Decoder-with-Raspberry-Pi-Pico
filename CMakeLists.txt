# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.13)

# Include the pico-sdk common tooling
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set the name and version of the project
project(MorseCodeDecoder VERSION 1.0)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
# Initialize the pico-sdk
pico_sdk_init()

# Create the executable for the MorseCodeDecoder project
add_executable(MorseCodeDecoder
        main.c
        )

# Pull in pico_stdlib which aggregates commonly used features
target_link_libraries(MorseCodeDecoder pico_stdlib)

# Enable USB output, disable UART output
pico_enable_stdio_usb(MorseCodeDecoder 1)
pico_enable_stdio_uart(MorseCodeDecoder 0)

# Create map/bin/hex/uf2 files etc.
pico_add_extra_outputs(MorseCodeDecoder)
