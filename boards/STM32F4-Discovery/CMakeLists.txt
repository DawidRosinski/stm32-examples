if (NOT TARGET Stm32F4Disc)

    add_library(Stm32F4Disc INTERFACE)

    target_sources(Stm32F4Disc INTERFACE
        startup_stm32f407xx.s
        system_stm32f4xx.c
        board_setup.c
    )

    stm32_add_library(hal)
    stm32_add_library(hal_rcc)
    stm32_add_library(hal_pwr)
    stm32_add_library(hal_flash)
    stm32_add_library(hal_cortex)

    target_link_libraries(Stm32F4Disc INTERFACE hal hal_rcc hal_pwr hal_flash hal_cortex)

    target_include_directories(Stm32F4Disc
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
    )

endif()