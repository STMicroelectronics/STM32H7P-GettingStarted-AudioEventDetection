# Deploy your tflite Model on STM32V873J-DK

This documentation is an example to show you how to deploy your own object
detection tflite model. The model of this example is a
st_ssd_mobilenet_v1_025_224_int8. Please adapt it to your own model/use case. In
order to run your own model you need to follow these steps:

Note: This repo does not support automatic deployment of models from the ST
model zool.

- [Generate C code from tflite file](#generate-c-code-from-tflite-file)
- [Update postprocess](#update-postprocess)
- [Build and Run](#build-and-run)

<!-- TODO: Generate c-model from tflite model -->

## Generate C code from tflite file

In order to generate the `application/model/network_*.c/h` files containing
network info and parameters you must install
[STEdgeAI](https://www.st.com/en/development-tools/stedgeai-core.html) (__v4.1.0__).

1. Add `/c/\<InstallFolder>/Utilities/windows/` in your path to have stedgeai
   known by your bash.

2. Put you tflite model in the `model` folder.

3. Run the following command in order to generate the C code, replacing
   `model.tflite` with your model file name:

```bash
cd application/model
stedgeai generate --model model.tflite -o . --target stm32v8
```

## Update postprocess

1. Define model postprocessing type. For now, only ST-SSD and YOLOV2 types are
   supported. In `main.c`, comment/uncomment the relevant line:

```c
#define USE_ST_SSD
```

2. Update postprocessing parameters in `od_yololc_pp_user.h` or
   `od_ssd_st_pp_user.h` according to your model and type:

```c
#define AI_OD_SSD_ST_PP_TOTAL_DETECTIONS            (6825)
#define AI_OD_SSD_ST_PP_NB_CLASSES                  (2)

/* --------  Tuning below can be modified by the application --------- */
#define AI_OD_SSD_ST_PP_CONF_THRESHOLD              (0.6f)
#define AI_OD_SSD_ST_PP_IOU_THRESHOLD               (0.3f)
#define AI_OD_SSD_ST_PP_MAX_BOXES_LIMIT             (100)
```

You can edit IOU thresholds, anchors values and other parameters.

The list of all the defines needed by each postprocessing type is available in
the [Postprocess defines
documentation](../middleware/stm32-vision-models-postprocessing/lib_vision_models_pp/README.md).

## Build and Run

1. Open the project (`application/ewarm/gettingstarted_objectdetect.ewp`) in IAR
   Embedded Workbench for Arm.
2. Build the project (Project -> Rebuild All).
3. Run the application on your STM32V873J-DK board.

Note: Depending on the model complexity, stack size may need to be increased.
For IAR, this can be configured in `application/ewarm/stm32v873xx_nvm.icf` using
the `__ICFEDIT_size_cstack__` symbol.
