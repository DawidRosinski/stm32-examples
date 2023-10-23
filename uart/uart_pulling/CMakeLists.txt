add_executable(uart_pulling uart_pulling.c)

stm32_add_library(hal_gpio)
stm32_add_library(hal_uart)

target_link_libraries(uart_pulling hal_gpio hal_uart hal_dma Stm32F4Disc)

stm32_create_outputs(uart_pulling)
