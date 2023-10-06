add_executable(semihosting semihosting.c)

target_link_options(semihosting PUBLIC
    -specs=rdimon.specs -lc -lrdimon
)

stm32_add_library(hal_gpio)

target_link_libraries(semihosting hal_gpio Stm32F4Disc)

stm32_create_outputs(semihosting)
