set(TARGET_NAME assembly_code_01)

add_executable(${TARGET_NAME} ${TARGET_NAME}.c startup.s)

stm32_create_outputs(${TARGET_NAME})