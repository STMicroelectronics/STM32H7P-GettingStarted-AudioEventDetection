# Release Notes for STM32H7P-GettingStarted-AED Application

## Purpose

This project provides an STM32 Microcontroler embedded real time environement
to execute
[STEdgeAI core](https://www.st.com/en/development-tools/stedgeai-core.html)
generated model targetting audio applications. The purpose of this package is
to stream physical data acquired by sensors into a processing chain including a
preprocessing step that typically would perform a first level of feature
extraction, the machine learning inference itself, and a post processing step
before exposing the results to the user in real time.

## Key Features

- Support of Audio Event Detection (AED) using Yamnet 256 on STM32H7P

## Software components

| Name                            | Version              | Release notes
|-----                            | -------              | -------------
| STEdge AI runtime               |  v3.2.0              |
| stm32-audio-sensing-processing  |  v1.4.0              | [release notes](Middlewares/ST/stm32-audio-sensing-processing/Release_Notes.html)
| STM32H7P CMSIS                  |                      |
| STM32H7P CMSIS DSP              |                      |
| stm32h7pxx_drivers              |  V2.0.0-alpha.2.0    | [release notes](stm32cubefw_h7p/stm32h7pxx_drivers/Release_Notes.html)
| stm32h7pxx_dfp                  |  V2.0.0-alpha.1.rc3  | [release notes](stm32cubefw_h7p/stm32h7pxx_dfp/Release_Notes.html)
| HSP engine                      |  V2.0.0-alpha.1.rc3  | [release notes](stm32cubefw_h7p/middleware/hsp_engine/st_readme.txt)

## Update history

### 0.1.1 / November 2025

Fix Issue cache maintenance.

### 0.1.0 / November 2025

Initial release of the STM32H7P-GettingStarted-AED.
