target_sources(${CMAKE_PROJECT_NAME} PRIVATE
  ../middleware/hsp_engine/common/utilities/portable/GCC/st_hsp_memcpy32.S
  ../middleware/stm32-audio-sensing-processing/Src/audio_din.c
  ../middleware/stm32-audio-sensing-processing/Src/feature_extraction.c
  ../middleware/stm32-audio-sensing-processing/Src/mel_filterbank.c
  ../arch/cmsis_dsp/Source/TransformFunctions/arm_bitreversal2.c
  ../arch/cmsis_dsp/Source/TransformFunctions/arm_cfft_f32.c
  ../arch/cmsis_dsp/Source/TransformFunctions/arm_cfft_init_f32.c
  ../arch/cmsis_dsp/Source/TransformFunctions/arm_cfft_radix8_f32.c
  ../arch/cmsis_dsp/Source/TransformFunctions/arm_rfft_fast_f32.c
  ../arch/cmsis_dsp/Source/TransformFunctions/arm_rfft_fast_init_f32.c
  ../arch/cmsis_dsp/Source/ComplexMathFunctions/arm_cmplx_mag_f32.c
  ../arch/cmsis_dsp/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.c
  ../arch/cmsis_dsp/Source/CommonTables/arm_common_tables.c
  ../arch/cmsis_dsp/Source/CommonTables/arm_const_structs.c
  ../arch/cmsis_dsp/Source/BasicMathFunctions/arm_dot_prod_f32.c
  ../arch/cmsis_dsp/Source/BasicMathFunctions/arm_mult_f32.c
  ../arch/cmsis_dsp/Source/SupportFunctions/arm_q15_to_float.c
  # Add additional source files here

)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
  ../middleware/stm32-audio-sensing-processing/Inc
  #  generated/middleware
  ../arch/cmsis_dsp/Include
  ../arch/cmsis_dsp/PrivateInclude
  # Add additional include directories here
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional defined symbols here
)

target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional compiler flags here
)

target_link_options(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional linker flags here
)

target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional linker search directories here
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional linker libraries here
)
