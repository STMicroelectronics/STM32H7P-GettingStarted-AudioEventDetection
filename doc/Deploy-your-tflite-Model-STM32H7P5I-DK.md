# Deploy a TFLite Model on STM32H7P5I-DK

This guide explains how to replace the Audio Event Detection model used by this
project. The checked-in model is
`yamnet_256_64x96_tl_int8_5_classes.tflite`. Adapt the preprocessing configuration and
class labels to match your model.

Follow these steps:

- [1. Generate the C model](#1-generate-the-c-model)
- [2. Configure preprocessing and classes](#2-configure-preprocessing-and-classes)
- [3. Build and run the application](#3-build-and-run-the-application)

## 1. Generate the C model

Install ST Edge AI Core 4.1. The generation script expects it at
`C:/ST/STEdgeAI/4.1/Utilities/windows/stedgeai.exe`; update the `steai` path in
`model/generate-h7p-model.sh` if it is installed elsewhere.

The script currently names the checked-in model in its `-m` argument. To use a
different model, place it in `model/` and update that argument. Run the script
from the `model/` directory:

```bash
cd model
./generate-h7p-model.sh
```

The script generates files in `model/st_ai_output/` and copies the generated
network sources, headers, memory files, report, and model information JSON into
`application/ai/`. No manual copy step is needed. The CMake files in
`application/ai/` include the generated model and middleware in the build.

## 2. Configure preprocessing and classes

The application currently expects one channel-last int8 input with shape
`1 x 96 x 64 x 1` (6144 bytes) and one float32 output with five scores. The
input is populated as 96 spectrogram columns of 64 Mel bands. The generated
model metadata supplies the int8 input scale and zero-point to the runtime; the
checked-in model uses scale `0.0580373295` and zero-point `31`.

Edit [application/dpu/ai_model_config.h](../application/dpu/ai_model_config.h)
to match the model's input preprocessing. The current configuration is:

```C
#define AI_SPECT_NMEL          (64U)
#define AI_SPECT_COL           (96U)
#define AI_SPECT_HOP_LEN       (160U)
#define AI_SPECT_NFFT          (512U)
#define AI_SPECT_WIN_LEN       (400U)
#define AI_SPECT_NORMALIZE     (0U)
#define AI_SPECT_FORMULA       (MEL_HTK)
#define AI_SPECT_FMIN          (125U)
#define AI_SPECT_FMAX          (7500U)
#define AI_SPECT_TYPE          (SPECTRUM_TYPE_MAGNITUDE)
#define AI_SPECT_LOG_FORMULA   (LOGMELSPECTROGRAM_SCALE_LOG)
#define AI_SPECT_WIN           (user_win)
#define AI_SPECT_MEL_LUT       (user_melFilterLut)
#define AI_SPECT_MEL_START_IDX (user_melFilterStartIndices)
#define AI_SPECT_MEL_STOP_IDX  (user_melFilterStopIndices)
```

The corresponding window and Mel-filter lookup tables are provided by
`application/dpu/user_mel_tables.c` and declared in
`application/dpu/user_mel_tables.h`. Regenerate these tables whenever the
window or Mel-filter settings change. The current declarations contain a
400-value window, 462 Mel coefficients, and 64 start/stop indices. The HSP
implementation in `application/dpu/preproc_dpu.c` also uses the current 462
coefficient count; update its allocation and copy sizes if the table dimensions
change.

The audio sample rate is set separately in
[application/app_config.h](../application/app_config.h):

```C
#define AI_SENSOR_ODR             (16000.0F)
```

The board audio input is fixed. The application currently maps five output
indices in this order in `application/gs_utils.c`: `chirping birds`,
`clapping`, `crying baby`, `dog`, and `rooster`. Update
`AI_MODEL_CLASS_NUMBER` and the `ai_class` name/pictogram table there if the
number or order of outputs changes. The detection confidence threshold is
`AI_OOD_THR` in `application/app_config.h` (currently `0.8`).

## 3. Build and run the application

After generation and configuration, build from the project root using the
available `debug_GCC_STM32H7P5I-DK` preset:

```bash
cube cmake --preset debug_GCC_STM32H7P5I-DK
cube cmake --build --preset debug_GCC_STM32H7P5I-DK
```

The ELF file is generated as
`build/debug_GCC_STM32H7P5I-DK/STM32H7P-GettingStarted-AED.elf`. Program it with
STM32CubeProgrammer, reset the board, and connect to the USB-UART console at
115200 baud, 8 data bits, no parity, 1 stop bit, and no flow control.

The build enables `USE_HSP` for accelerated audio preprocessing and
`USE_TRACE=1` for runtime traces. Press a key in the console to stop audio
processing.
