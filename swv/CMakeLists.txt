set(TARGET_NAME swv)

add_executable(${TARGET_NAME} ${TARGET_NAME}.c)

stm32_add_library(hal_gpio)

target_link_libraries(${TARGET_NAME} hal_gpio Stm32F4Disc)

stm32_create_outputs(${TARGET_NAME})
