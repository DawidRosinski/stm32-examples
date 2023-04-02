add_executable(semihosting
    semihosting.c
    ../boards/STM32F4-Discovery/startup_stm32f407xx.s
    ../boards/STM32F4-Discovery/system_stm32f4xx.c
    )

target_link_options(semihosting PUBLIC
    -specs=rdimon.specs -lc -lrdimon
)

target_include_directories(semihosting
    PRIVATE
        Drivers
        ../boards/STM32F4-Discovery
    )

target_link_libraries(semihosting Drivers)



## TO be moved somewhere else 


add_custom_command(TARGET semihosting
    POST_BUILD
    COMMAND ${CMAKE_SIZE_UTIL} semihosting
)

# Create a custom command to generate binary and hex files.
# These can be used depending on which method of loading the firmware to the MCU is used.
add_custom_command(TARGET semihosting
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex semihosting semihosting.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary semihosting semihosting.bin
)
