---
pagetitle: Release Notes for HSP engine SW Pack
lang: en
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

<center>
# Release Notes for
# <mark>HSP Engine SW Pack</mark>

</center>

# Purpose

STM32Cube enables developers to achieve design success. With a comprehensive suite of professional development tools and embedded software components, STM32Cube allows developers to differentiate products, streamline design cycles, and reduce costs. STM32Cube ecosystem supports all design steps, including selection, configuration, development, debugging, programming, and monitoring.
The STM32Cube embedded software offer provides ready-to-use software components that can be added to a project. It includes STM32 peripheral driver APIs with two levels of abstraction, middleware, board drivers, and examples. There are several distribution channels, including the STM32CubeMX2 tool, the ST website, and GitHub. All embedded software comes with enhanced online documentation, with flowcharts and user sequences.

The HSP Engine Middleware is an efficient interface to configure and process complex signal processing through the STM32 HSP peripheral.
The middleware provides high-level APIs (Direct Command, DSP, and CNN) to perform mathematical operations such as those found in standard ARM DSP or CMSIS-NN.
It contains also services to build and configure complex processing chains using the Sequencer Mode, through a processing list manager.

## Documentation

More documentation is available at [**HSP Engine User Manual**](https://www.st.com/resource/en/user_manual/um3360-hsp-processing-functions-on-stm32-mcus-stmicroelectronics.pdf).
:::

::: {.col-sm-12 .col-lg-8}
# Update history

::: {.collapse}
<input type="checkbox" id="collapse-section-2.0.0" checked aria-hidden="true">
<label for="collapse-section-2.0.0" aria-hidden="true">__2.0.0 / 26-August-2026__</label>
<div>

## Main changes

First Official release of **HSP Engine SW Pack**.\

\

## Contents


## Known limitations

- Timestamp Capture is not supported.
- Plugins is not supported.
- No online documentation is available in this release. Please refer to the old documentation format [CHM:](Doc/chm/mw_hsp_engine.chm) HSP Engine Middleware Developer Manual

## Development toolchains and compilers

- IAR Embedded Workbench for ARM (EWARM) toolchain V9.60.3 + ST-LINK
- MDK-ARM Keil uVision V5.42
- STM32CubeIDE for Visual Studio Code (GCC13 compiler)

## Supported devices and boards

- STM32H7P series

## Backward compatibility

- None

## Dependencies

- STM32H7Pxx HAL Drivers V2.0.0

</div>
:::

:::
:::

<footer class="sticky">
::: {.columns}
::: {.column width="95%"}
For complete documentation on STM32 microcontrollers,
visit: [www.st.com/stm32](http://www.st.com/stm32)
:::
::: {.column width="5%"}
<abbr title="Based on template cx566953 version 2.1">Info</abbr>
:::
:::

This release note uses up to date web standards and, for this reason, should not be opened with Internet Explorer but preferably with popular browsers such as Google Chrome, Mozilla Firefox, Opera or Microsoft Edge.
</footer>