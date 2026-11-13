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

| Name                            | Version  | Release notes
|-----                            | -------  | -------------
| STEdge AI runtime               |  v4.1.0  | -
| stm32-audio-sensing-processing  |  v1.6.0  | [release notes](middleware\stm32-audio-sensing-processing\Release_Notes.html)
| HSP engine                      |  V2.0.0  | [release notes](middleware\hsp_engine\Release_Notes.md)
| STM32H7P CMSIS                  |  v6.3.0  | -
| STM32H7P CMSIS DSP              |  v1.7.1  | -
| LED Part Drivers                |  V2.2.0  | [release notes](part_drivers\led\Release_Notes.md)
| ST7315 Part Drivers             |  V2.0.0  | [release notes](part_drivers\st7315\Release_Notes.md)
| basic_stdio                     |  V2.1.0  | [release notes](utilities\basic_stdio\Release_Notes.md)
| syscalls                        |  V2.0.2  | [release notes](utilities\syscalls\Release_Notes.md)
| stm32h7pxx_drivers              |  V2.0.0  | [release notes](stm32h7pxx_drivers\Release_Notes.md)
| stm32h7pxx_dfp                  |  V2.0.0  | [release notes](stm32h7pxx_dfp\Release_Notes.md)

## Update history

### 1.0.0 / October 2026

Updated all dependencies to their latest versions.

### 0.1.1 / November 2025

Fix Issue cache maintenance.

### 0.1.0 / November 2025

Initial release of the STM32H7P-GettingStarted-AED.
