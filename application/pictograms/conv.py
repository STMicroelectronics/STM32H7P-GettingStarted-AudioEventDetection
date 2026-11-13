#!/usr/bin/env python3

from pathlib import Path
import argparse
from glob import glob
import re
from PIL import Image


WIDTH = 128
HEIGHT = 64


def generate_files(input_path: Path, output_dir: Path, threshold: int):
    output_dir.mkdir(parents=True, exist_ok=True)

    image = Image.open(input_path).convert("RGBA")

    # Fond blanc pour gérer correctement la transparence
    background = Image.new("RGBA", image.size, (255, 255, 255, 255))
    image = Image.alpha_composite(background, image)

    # Conversion en niveaux de gris puis redimensionnement
    image = image.convert("L")
    image = image.resize((WIDTH, HEIGHT), Image.Resampling.LANCZOS)

    # Conversion en bitmap :
    # noir  -> bit 0
    # blanc -> bit 1
    bitmap = bytearray()

    for y in range(HEIGHT):
        for byte_x in range(0, WIDTH, 8):
            value = 0

            for bit in range(8):
                pixel = image.getpixel((byte_x + bit, y))

                if pixel >= threshold:
                    value |= 1 << (7 - bit)

            bitmap.append(value)

    output_stem = f"pict_{input_path.stem}"
    c_path = output_dir / f"{output_stem}.c"
    h_path = output_dir / f"{output_stem}.h"
    variable_name = re.sub(r"[^a-zA-Z0-9_]", "_", output_stem)
    if variable_name[0].isdigit():
        variable_name = f"_{variable_name}"

    guard = re.sub(r"[^A-Z0-9]", "_", f"{output_stem.upper()}_H")

    h_content = f"""/**
  ******************************************************************************
    * @file   {h_path.name}
    * @brief  64 x 128 monochrome image bitmap file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef {guard}
#define {guard}

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#ifdef __cplusplus
extern "C" {{
#endif

/* Exported variables --------------------------------------------------------*/
extern const uint8_t {variable_name}[{len(bitmap)}];

#ifdef __cplusplus
}}
#endif

#endif /* {guard} */
"""

    c_lines = []

    for index in range(0, len(bitmap), 13):
        line = ", ".join(f"0x{value:02x}" for value in bitmap[index:index + 13])
        c_lines.append(f"  {line},")

        c_content = f"""/**
  ******************************************************************************
     * @file   {c_path.name}
     * @brief  64 x 128 monochrome image bitmap file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "{h_path.name}"

/* Exported variables by reference--------------------------------------------*/
const uint8_t {variable_name}[{len(bitmap)}] =
{{
{chr(10).join(c_lines)}
}};
"""

    h_path.write_text(h_content, encoding="ascii")
    c_path.write_text(c_content, encoding="ascii")

    print(f"Image source : {input_path}")
    print(f"Generated    : {c_path}")
    print(f"Generated    : {h_path}")
    print(f"Bitmap size  : {WIDTH}x{HEIGHT}")
    print(f"Data size    : {len(bitmap)} bytes")


def main():
    parser = argparse.ArgumentParser(
        description="Convert an image to a 128x64 monochrome C bitmap"
    )

    parser.add_argument(
        "inputs",
        nargs="+",
        help="Image source or wildcard, for example clap.png or *.png",
    )
    parser.add_argument(
        "-o",
        "--output-dir",
        type=Path,
        default=Path("."),
        help="Output directory",
    )
    parser.add_argument(
        "-t",
        "--threshold",
        type=int,
        default=128,
        help="Black/white threshold between 0 and 255",
    )

    args = parser.parse_args()

    if not 0 <= args.threshold <= 255:
        parser.error("The threshold must be between 0 and 255")

    input_paths = []
    for input_pattern in args.inputs:
        matches = [Path(path) for path in glob(input_pattern)]
        input_paths.extend(path for path in matches if path.is_file())

    if not input_paths:
        parser.error("No input image matched the specified path or wildcard")

    for input_path in sorted(set(input_paths)):
        generate_files(input_path, args.output_dir, args.threshold)


if __name__ == "__main__":
    main()