cmake_minimum_required(VERSION 3.24)

# initialize the FW based on STM32_FW_PATH
include(stm32-cmake/cmake/stm32_fw_import.cmake)

project(stm32_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

include(stm32-cmake/cmake/mcu_options.cmake)
stm32_fw_init(F4 1.26.1)

add_subdirectory(blink)
add_subdirectory(gpio)
add_subdirectory(semihosting)