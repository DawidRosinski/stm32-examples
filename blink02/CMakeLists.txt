set(TARGET_NAME blink02)

add_executable(${TARGET_NAME} ${TARGET_NAME}.c)

stm32_add_library(hal_gpio)

target_link_libraries(${TARGET_NAME} hal_gpio Stm32F4Custom)

stm32_create_outputs(${TARGET_NAME})