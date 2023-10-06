add_executable(spi_master spi_master.c)

stm32_add_library(hal_gpio)
stm32_add_library(hal_spi)
stm32_add_library(hal_uart)
stm32_add_library(hal_dma)

target_link_libraries(spi_master hal_gpio hal_spi hal_uart hal_dma Stm32F4Disc)

stm32_create_outputs(spi_master)
