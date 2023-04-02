add_executable(blink
    blink.c
    ../boards/STM32F4-Discovery/startup_stm32f407xx.s
    ../boards/STM32F4-Discovery/system_stm32f4xx.c
    )

target_include_directories(blink
    PRIVATE
        Drivers
        # System_and_Startup
        ../boards/STM32F4-Discovery
    )

target_link_libraries(blink Drivers)



## TO be moved somewhere else 


add_custom_command(TARGET blink
    POST_BUILD
    COMMAND ${CMAKE_SIZE_UTIL} blink
)

# Create a custom command to generate binary and hex files.
# These can be used depending on which method of loading the firmware to the MCU is used.
add_custom_command(TARGET blink
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex blink blink.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary blink blink.bin
)
