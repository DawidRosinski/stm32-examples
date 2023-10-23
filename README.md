`cd build`

Select board by setting the `STM32_BOARD` to `stm32f4_disc` or `stm32_custom`:

`cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DSTM32_BOARD=stm32f4_disc -DSTM32_CPU=STM32F407xx -DCMAKE_TOOLCHAIN_FILE:PATH="..\stm32-cmake\cmake\toolchain.cmake"  ..`

`cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DSTM32_BOARD=stm32_custom -DSTM32_CPU=STM32F417xx -DCMAKE_TOOLCHAIN_FILE:PATH="..\stm32-cmake\cmake\toolchain.cmake"  ..`