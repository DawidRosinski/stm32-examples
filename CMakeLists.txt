cmake_minimum_required(VERSION 3.24)

# initialize the FW based on STM32_FW_PATH
include(stm32-cmake/cmake/stm32_fw_import.cmake)

project(stm32_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

include(stm32-cmake/cmake/mcu_options.cmake)
stm32_fw_init(F4 1.26.1)

set(STM32_BOARDS
    -D_STM32_F4_DISC=0
    -D_STM32_CUSTOM=1)

add_definitions(${STM32_BOARDS})

if (${STM32_BOARD} STREQUAL "stm32f4_disc")
    add_definitions(-D_STM32_BOARD=0)
    add_subdirectory(boards/STM32F4-Discovery)
    add_subdirectory(blink)
    add_subdirectory(gpio)
    add_subdirectory(semihosting)
    add_subdirectory(uart)
    add_subdirectory(swv)
    add_subdirectory(spi)
    add_subdirectory(assembly_code_01)
    add_subdirectory(can)
elseif(${STM32_BOARD} STREQUAL "stm32_custom")
    add_definitions(-D_STM32_BOARD=1)
    add_subdirectory(boards/stm32f4-custom)
    add_subdirectory(blink02)
    # add_subdirectory(spi02)
endif()

