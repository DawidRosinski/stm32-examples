add_executable(can_pulling can_pulling.c)

stm32_add_library(hal_gpio)
stm32_add_library(hal_can)
# stm32_add_library(hal_uart)
# stm32_add_library(hal_dma)

target_link_libraries(can_pulling hal_gpio hal_can Stm32F4Disc)

stm32_create_outputs(can_pulling)
