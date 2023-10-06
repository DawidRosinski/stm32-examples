set(TARGET_NAME spi_slave)

add_executable(${TARGET_NAME} ${TARGET_NAME}.c)

stm32_add_library(hal_gpio)
stm32_add_library(hal_spi)
stm32_add_library(hal_uart)
stm32_add_library(hal_dma)

target_link_libraries(${TARGET_NAME} hal_gpio hal_spi hal_uart hal_dma Stm32F4Disc)

stm32_create_outputs(${TARGET_NAME})