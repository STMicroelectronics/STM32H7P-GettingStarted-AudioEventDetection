# Stubs to be able to add compiler flag overrides, e.g. -Os
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
  ../application/app_aed.c
  ../application/cpu_stats.c
  ../application/gs_utils.c
  ../application/dpu/preproc_dpu.c
  ../application/dpu/ai_dpu.c
  ../application/dpu/user_mel_tables.c
  ../stm32h7pxx_drivers/hal/stm32h7pxx_hal_dbgmcu.c
  ../middleware/stedgeai-lib/Npu/Devices/STM32H7xx/mcu_cache.c
  ../middleware/stedgeai-lib/Misc/Src/ai_device_adaptor.c
  # Add additional source files here
)

if(APP_LCD)
  target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ../application/oled.c
    ../application/pictograms/pict_st_logo.c
    ../application/pictograms/pict_baby_cry.c
    ../application/pictograms/pict_bird_chirp.c
    ../application/pictograms/pict_dog_bark.c
    ../application/pictograms/pict_unknown.c
    ../application/pictograms/pict_rooster.c
    ../application/pictograms/pict_clap.c
    ../application/pictograms/pict_sleep.c
  )
  target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC APP_LCD)
endif()

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
  ../application
  ../application/dpu
  ../application/pictograms
  ../middleware/stm32-audio-sensing-processing/Inc
  ../arch/cmsis_dsp/Include
  # Add additional include directories here
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
  USE_HSP
  USE_TRACE=1
  # Add additional defined symbols here
)

target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional compiler flags here
)

target_link_options(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional linker flags here
)

target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC
  ../middleware/stedgeai-lib/Lib
  # Add additional linker search directories here
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional linker libraries here
)
