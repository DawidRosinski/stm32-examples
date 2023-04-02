add_executable(gpio
    gpio.c
    ../boards/STM32F4-Discovery/startup_stm32f407xx.s
    ../boards/STM32F4-Discovery/system_stm32f4xx.c
    )

target_include_directories(gpio
    PRIVATE
        Drivers
        ../boards/STM32F4-Discovery
    )

target_link_libraries(gpio Drivers)



## TO be moved somewhere else 


add_custom_command(TARGET gpio
    POST_BUILD
    COMMAND ${CMAKE_SIZE_UTIL} gpio
)

# Create a custom command to generate binary and hex files.
# These can be used depending on which method of loading the firmware to the MCU is used.
add_custom_command(TARGET gpio
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex gpio gpio.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary gpio gpio.bin
)
