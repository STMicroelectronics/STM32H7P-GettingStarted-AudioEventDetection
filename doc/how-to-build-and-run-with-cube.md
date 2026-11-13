# How to build and run with STM32CubeIDE for Visual Studio Code

This guide provides step-by-step instructions to build and run the STM32V8 AI
Getting Started application using STM32CubeIDE for Visual Studio Code.

## Prerequisites

- Visual Studio Code installed on your system.
- [STM32CubeIDE for Visual Studio Code][1] extension installed, with STM32H7P
  device support and the required build and debug tools available.
- USB Type-C data cable for the board's ST-LINK connection.

## Hardware Setup

Connect the board's **STLK USB** port to your PC using the USB Type-C data cable
to power the board and provide the debug connection.

## Build and Run

1. Open Visual Studio Code.
2. Select **File > Open Folder...** and open the project root folder containing
   [CMakeLists.txt](../STM32H7P5I-DK/CMakeLists.txt) , STM32H7P5I-DK.
3. When prompted to configure the discovered CMake project as an STM32Cube
   project, click **Yes**. See [Note 1](#note-1).
4. Wait for "Loading STM32Cube project(s)" to complete.
5. Configure and build the project:
   1. if you want to activate the OLED display support, in 
   `.vscode/settings.json`, add `-DAPP_LCD=ON` to `cmake.configureArgs`:
      ```json
       "cmake.configureArgs": [
         "-DAPP_LCD=ON"
         ],
      ```
   2. Open the Command Palette and run **CMake: Select Configure Preset**.
      Select **debug_GCC_STM32H7P5I-DK**, which supplies the project's toolchain
      settings from [CMakePresets.json](STM32H7P5I-DK/CMakePresets.json).
   3. From the activity bar (on the left by default), click the **CMake** icon.
      Under **Configure**, click **Configure** and wait for it to succeed.
   4. Select the **debug_GCC_STM32H7P5I-DK** build preset, then under **Build**, click
      **Build** and wait for it to succeed.
6. Ensure the board is connected as described in [Hardware Setup](#hardware-setup).
7. From the activity bar, click the **Run and Debug** icon.
8. Click the **Run and Debug** button and select
   **STM32Cube: STM32 Launch STLink GDB server**. See [Note 2](#note-2).
9. If the debugger pauses at the program entry point, click **Continue (F5)**
   to run the application.
10. Confirm that the board's LCD gives the right pictogram matching the audio
   event.

### Note 1

If the project has not been configured through the
STM32CubeIDE for Visual Studio Code extension, the build may use tools from
your system rather than the extension-managed tools, which can lead to build
errors. If you missed the configuration prompt, click
**Setup STM32Cube project(s)** in the **STM32Cube** section, then repeat the
configure and build steps.

### Note 2

When starting a new debug session, the startup might fail because the debugger
firmware needs to be updated. To do so, select the STLINK debug device under the
**STM32CUBE DEVICES AND BOARDS** section. Click the **Upgrade STLINK firmware**
button to update the firmware. Then, launch the debug session again.

## References

- [STM32CubeIDE for Visual Studio Code documentation](https://dev.st.com/stm32cube-docs/stm32cubeide-vscode/latest/en/index.html)
- [How to build and run an example](https://dev.st.com/stm32cube-docs/examples/2.0.0/en/use/how-to-build.html)
- [How to debug an example](https://dev.st.com/stm32cube-docs/examples/2.0.0/en/debug/debug_toc.html)

[1]: https://marketplace.visualstudio.com/items?itemName=stmicroelectronics.stm32-vscode-extension
