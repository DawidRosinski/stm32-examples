if (NOT TARGET Stm32F4Custom)

    add_library(Stm32F4Custom INTERFACE)

    target_sources(Stm32F4Custom INTERFACE
        startup_stm32f417xx.s
        system_stm32f4xx.c
        board_setup.c
    )

    stm32_add_library(hal)
    stm32_add_library(hal_rcc)
    stm32_add_library(hal_pwr)
    stm32_add_library(hal_flash)
    stm32_add_library(hal_cortex)

    target_link_libraries(Stm32F4Custom INTERFACE hal hal_rcc hal_pwr hal_flash hal_cortex)

    target_include_directories(Stm32F4Custom
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
    )

endif()