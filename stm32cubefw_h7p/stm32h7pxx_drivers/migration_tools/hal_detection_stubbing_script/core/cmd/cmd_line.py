"""
/**
  *************************************************************************************************
  * @file    cmd_line.py
  * @brief   Provides command-line services for the HAL1 detection script.
  *************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in the root
  * directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *************************************************************************************************
  */
"""

import os
import sys
import re
import logging
import argparse
import ast
from pathlib import Path
import importlib.util
from typing import Optional, List, Tuple, Dict, Any

from hal_detection_stubbing_script.core.config.hal_detection_stubbing_default_config import (
                                                                                                DEFAULT_CONFIG,
                                                                                                CONFIG_FILENAME
                                                                                        )
from hal_detection_stubbing_script.core import services
from hal_detection_stubbing_script.core.stub import stub_app_files_ignore_config

VALID_DETECTION_CHOICES = ['dry-run', 'stub']
VALID_CONFIG_CHOICES = ['list', 'modify', 'default']

class DetectionAction(argparse.Action):
    """
    Custom argparse action for -d/--detection.
    Sets a flag in the namespace to indicate if the option was used.
    """
    def __call__(self, parser, namespace, values, option_string=None):
        setattr(namespace, self.dest, values)
        setattr(namespace, f"{self.dest}_used", True)

class ConfigAction(argparse.Action):
    """
    Custom argparse action for -c/--config.
    Sets a flag in the namespace to indicate if the option was used.
    """
    def __call__(self, parser, namespace, values, option_string=None):
        setattr(namespace, self.dest, values)
        setattr(namespace, f"{self.dest}_used", True)
        if values is not None and values.lower() not in VALID_CONFIG_CHOICES:
            parser.error(
                f"Invalid config option '{values}'. "
                f"Valid options are: {', '.join(VALID_CONFIG_CHOICES)}."
            )

def get_config_path() -> Path:
    """Return the path to the config file."""
    script_dir = Path(sys.argv[0]).parent.resolve()
    return script_dir / CONFIG_FILENAME

def list_config() -> None:
    """List current configuration."""
    config_path = get_config_path()
    if not config_path.exists():
        print("Config file not found. Using default config:")
        print(DEFAULT_CONFIG)
        return
    spec = importlib.util.spec_from_file_location("hal1_detection_config", str(config_path))
    config = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(config)
    print(f"Configuration from {config_path}:")
    for var in dir(config):
        if not var.startswith("__"):
            value = getattr(config, var)
            print(f"{var} = {repr(value)}")

def modify_config() -> None:
    """Interactively modify configuration."""
    config_path = get_config_path()
    if not config_path.exists():
        with open(config_path, "w", encoding="utf-8") as f:
            f.write(DEFAULT_CONFIG)
    spec = importlib.util.spec_from_file_location("hal1_detection_config", str(config_path))
    config = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(config)
    config_vars = [var for var in dir(config) if not var.startswith("__")]

    default_vars: Dict[str, Any] = {}
    for line in DEFAULT_CONFIG.splitlines():
        match = re.match(r'^(\w+)\s*=\s*(.+)', line)
        if match:
            var, val = match.groups()
            try:
                default_vars[var] = ast.literal_eval(val)
            except (ValueError, SyntaxError):
            # except Exception:
                default_vars[var] = val.strip('"').strip("'")

    changes: Dict[str, Any] = {}

    while True:
        print("\nCurrent configuration:")
        for idx, var in enumerate(config_vars, 1):
            print(f"{idx}. {var} = {repr(getattr(config, var))}")
        print("\nOptions:")
        print("  [number] - Modify variable")
        print("  r[number] - Reset variable to default")
        print("  s - Save and exit")
        print("  q - Quit without saving")
        try:
            choice = input("Enter your choice: ").strip()
        except (KeyboardInterrupt, EOFError):
            print("\nAborted by user.")
            break

        if choice == "q":
            print("No changes saved.")
            break
        if choice == "s":
            if changes:
                update_config_variables(config_path, changes)
                print("Changes saved.")
            else:
                print("No changes to save.")
            break
        if choice.startswith("r") and choice[1:].isdigit():
            idx = int(choice[1:]) - 1
            if 0 <= idx < len(config_vars):
                var = config_vars[idx]
                changes[var] = default_vars.get(var, getattr(config, var))
                print(f"{var} will be reset to default: {repr(changes[var])}")
            else:
                print("Invalid variable number.")
        elif choice.isdigit():
            idx = int(choice) - 1
            if 0 <= idx < len(config_vars):
                var = config_vars[idx]
                current_value = getattr(config, var)
                try:
                    new_value = input(f"Enter new value for {var} (current: {repr(current_value)}): ")
                except (KeyboardInterrupt, EOFError):
                    print("\nAborted by user.")
                    break
                try:
                    parsed_value = ast.literal_eval(new_value)
                    new_value = parsed_value
                except (ValueError, SyntaxError):
                # except Exception:
                    print("Warning: Could not parse input as a Python literal. Keeping as string.")
                if var == "StubbingCompilationFlag" and (not new_value or str(new_value).strip() == ""):
                    print("Error: StubbingCompilationFlag must not be empty.")
                    continue
                changes[var] = new_value
                print(f"{var} will be updated to {repr(new_value)}.")
            else:
                print("Invalid variable number.")
        else:
            print("Invalid choice.")

def update_config_variables(config_path: Path, changes: Dict[str, Any]) -> None:
    """Update config variables in the config file."""
    lines = []
    with open(config_path, "r", encoding="utf-8") as f:
        for line in f:
            for var, new_value in changes.items():
                if line.strip().startswith(f"{var} "):
                    if isinstance(new_value, str):
                        line = f"{var} = {repr(new_value)}\n"
                    else:
                        line = f"{var} = {new_value}\n"
                    break
            lines.append(line)
    with open(config_path, "w", encoding="utf-8") as f:
        f.writelines(lines)

def reset_config_to_default() -> None:
    """Reset config file to default."""
    config_path = get_config_path()
    with open(config_path, "w", encoding="utf-8") as f:
        f.write(DEFAULT_CONFIG)
    print(f"Config reset to default at {config_path}")

def interactive_config_menu() -> None:
    """Interactive menu for config management."""
    print("\nConfig management options:")
    print("  1) List current config")
    print("  2) Modify config")
    print("  3) Reset to default config")
    while True:
        try:
            choice = input("Enter 1, 2, or 3: ").strip()
        except (KeyboardInterrupt, EOFError):
            print("\nAborted by user.")
            sys.exit(0)
        if choice == "1":
            list_config()
            break
        if choice == "2":
            modify_config()
            break
        if choice == "3":
            reset_config_to_default()
            break
        print("Invalid input. Please enter 1, 2, or 3.")
    sys.exit(0)

def handle_config_option(option: Optional[str]) -> None:
    """Handle config option."""
    if option is None:
        interactive_config_menu()
    else:
        option = option.lower()
        if option == "list":
            list_config()
        elif option == "modify":
            modify_config()
        elif option == "default":
            reset_config_to_default()
        else:
            print("Invalid config option. Use 'list', 'modify', or 'default'.")
        sys.exit(0)

def interactive_detection_choice() -> str:
    """Prompt user for detection mode."""
    print("\nPlease select detection mode:")
    print("  1) dry-run (detect and generate a log file) no-user-source file modifications")
    print("  2) stub (detect, stub and generate a log file) with eventually user-source file modifications")
    while True:
        try:
            choice = input("Enter 1 or 2: ").strip()
        except (KeyboardInterrupt, EOFError):
            print("\nAborted by user.")
            sys.exit(1)
        if choice == "1":
            return "dry-run"
        if choice == "2":
            return "stub"
        print("Invalid input. Please enter 1 for 'dry-run' or 2 for 'stub'.")

def handle_source_path(pathsource: str) -> Tuple[Optional[Path], Optional[Path]]:
    """Return folder or file path for source."""
    if os.path.isdir(pathsource):
        return Path(pathsource), None
    if os.path.isfile(pathsource):
        return None, Path(pathsource)
    print(f"Error: The provided path '{pathsource}' does not exist or is not accessible.")
    sys.exit(1)

def parse_arguments() -> argparse.Namespace:
    """Parse command-line arguments and handle exclusivity and interactivity."""
    parser = argparse.ArgumentParser(
        description=(
            "HAL1 detection script command-line interface.\n\n"
            "USAGE MODES (choose one):\n"
            "  1. Config management mode:\n"
            "     -c [list|modify|default]   # If omitted, interactive menu is shown\n"
            "     (Do NOT use with -d, -psrc, or -m)\n"
            "  2. Detection/stubbing mode (-psrc and -m are required):\n"
            "     -d [dry-run|stub] -psrc PATH -m all|module1 module2 ...\n"
            "     if -d is omitted dry-run option is used by default:\n"
            "     the script detect and generate a log file, (no user-source file modifications)\n" \
            "     if the command -d stub -psrc PATH -m all|module1 module2 is used:\n"
            "     the script detect and generate a log file (with eventually user-source file modifications)\n"
            "     (Do NOT use with -c)\n\n"
            "Example:\n"
            "  py hal1_detection.py -psrc ./src -m all\n"
        ),
        formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument(
        "-c", "--config",
        nargs='?',
        const=None,
        default=None,
        action=ConfigAction,
        help= ("Config management mode: list, modify, or default (reset).\n"
               "If config mode is omitted, you will be prompted interactively.")
    )
    parser.add_argument(
        "-psrc", "--pathsource",
        default=None,
        help= ("Source path (file or folder) for detection/stubbing.\n"
                "REQUIRED with -d and -m."
                )
    )
    parser.add_argument(
        '-d', '--detection',
        nargs='?',
        const=None,
        default=None,
        action=DetectionAction,
        help=("Detection mode: dry-run or stub.\n"
              "dry-run : detect and generate a log file, (no user-source file modifications)\n"
              "stub    : detect, stub and generate a log file with eventually user-source file modifications\n"
              "REQUIRED with -psrc and -m.\n"
              "If -d is used without detection mode options, you will be prompted interactively."
              )
    )
    parser.add_argument(
        "-m", "--modules",
        nargs="+",
        metavar="all|module1 module2 ...",
        default=None,
        help=("Specify 'all' to process all modules, or provide a space-separated list of module names.\n"
              "REQUIRED with -psrc and -d."
              )
    )

    args = parser.parse_args()

    # Ensure _used flags are present
    if not hasattr(args, "config_used"):
        args.config_used = False
    if not hasattr(args, "detection_used"):
        args.detection_used = False

    # 1. Config mode (exclusive)
    if args.config_used:
        if args.detection_used or args.pathsource or args.modules:
            parser.error(
                            "The -c/--config option cannot be used with -d/--detection, -psrc/--pathsource,"
                            "or -m/--modules."
                        )
        return args

    # 2. Detection mode (exclusive)
    if args.detection_used:
        if args.config_used:
            parser.error("The -d/--detection option cannot be used with -c/--config.")
        if not args.pathsource or not args.modules:
            parser.error("When using -d/--detection, both -psrc/--pathsource and -m/--modules are required.")
        return args

    # 3. If -psrc or -m is used without -d Default to dry-run

    if not args.config_used and not args.detection_used:
        if not args.pathsource or not args.modules:
            parser.error("Default mode is '-d dry-run'. You must provide both -psrc/--pathsource and -m/--modules.")
        args.detection = "dry-run"
        args.detection_used = True
        return args

    # if args.pathsource or args.modules:
    #     parser.error("The -psrc/--pathsource and -m/--modules options must be used together with -d/--detection.")

    # 4. If nothing is used, error
    parser.error(
                    "You must use either -c/--config or -d/--detection with -psrc/--pathsource and -m/--modules\n"
                    " or -psrc/--pathsource and -m/--modules for default dry-run."
                )

    return args

def get_args() -> Tuple[Optional[Path], List[Path], Optional[List[str]], bool]:
    """Get parsed arguments and validate modules."""
    args = parse_arguments()

    # Config management mode
    if args.config_used:
        # Interactive menu if no value provided
        if args.config is None:
            interactive_config_menu()
        else:
            handle_config_option(args.config)
        sys.exit(0)

    # Detection mode
    if args.detection_used:
        # Interactive prompt if no value provided or invalid value
        if args.detection is None or args.detection.lower() not in VALID_DETECTION_CHOICES:
            args.detection = interactive_detection_choice()
        else:
            args.detection = args.detection.lower()

    src_folder, src_file = handle_source_path(args.pathsource)

    if src_file:
        src_files = [src_file]
    else:
        src_files = services.get_src_files(
            src_folder,
            stub_app_files_ignore_config.excluded_drivers,
            stub_app_files_ignore_config.patterns,
            stub_app_files_ignore_config.special_files
        )

    if not src_files:
        logging.warning("Source folder is empty or contains no valid source files!")
        sys.exit(1)

    base_dir = Path(__file__).parent.parent.parent
    modules_db_path = base_dir / 'db' / 'modules.csv'
    modules_db = services.read_modules_from_csv(modules_db_path)

    if args.modules and "all" in [module.lower() for module in args.modules]:
        modules = None
    else:
        modules = [module.lower() for module in args.modules]
        invalid_modules = [module for module in modules if module not in modules_db]
        if invalid_modules:
            print(f"Error: The following module(s): {', '.join(invalid_modules)} are not in the database.")
            sys.exit(1)

    is_dry_run = args.detection == "dry-run"
    return src_folder, src_files, modules, is_dry_run
