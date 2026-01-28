#**********************************************************************************
# Copyright (C) 2026 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#*********************************************************************************/
Import("env") # type: ignore
import os
import subprocess

platform = env.PioPlatform() # type: ignore
board_config = env.BoardConfig() # type: ignore
build_mcu = board_config.get("build.mcu")

def build_simulator_image(firmware_path):
    """Build a flash image for use in the simulator"""

    ESPTOOL_DIR = platform.get_package_dir("tool-esptoolpy")

    # Determine the bootloader offset based on the target device
    match build_mcu:
        case "esp32" | "esp32s2":
            bootloader_offset = "0x1000"
        case "esp32p4":
            bootloader_offset = "0x2000"
        case _:
            bootloader_offset = "0x0000"

    # Build the data file system
    print("Building file system")
    littlefs_tool = os.path.join(env.PioPlatform().get_package_dir("tool-mklittlefs"), "mklittlefs")
    littlefs_img = env.File('$BUILD_DIR/littlefs.bin').abspath
    env.Execute(f"{littlefs_tool} -c data -s 0x360000 {littlefs_img}") 

    # Build the full image
    command = [ 
        os.path.join(ESPTOOL_DIR, 'esptool.py'),
        '--chip', build_mcu,
        'merge-bin',
        '-o', firmware_path,
        '--fill-flash-size', board_config.get("upload.flash_size"), 
        '--flash_size', 'keep',
        '--flash_mode', env['BOARD_FLASH_MODE'], # type: ignore
        '--flash_freq', '40m',
        bootloader_offset, env.File('$BUILD_DIR/bootloader.bin').abspath, # type: ignore
        '0x8000', env.File('$BUILD_DIR/partitions.bin').abspath, # type: ignore
        '0x10000', env.File('$BUILD_DIR/firmware.bin').abspath, # type: ignore
        '0xC90000', env.File('$BUILD_DIR/littlefs.bin').abspath, # type: ignore
    ]

    print(f"Building image with command:\n {' '.join(command)}")
    result = subprocess.run(command, capture_output=True)
    if result.returncode != 0: 
        print(result.stdout)
        return False
    else:
        print("Image built")
        return True

def build_wokwi_image(source, target, env):
    """Build a full flash image that can be consumed by the Wokwi simulator"""
    
    # Get the compiled firmware path
    flash_image = env.File('$BUILD_DIR/wokwi_image.bin').abspath
    if not build_simulator_image(flash_image):
        return

#
# Post-process the binary into a full flash image for Wokwi
#
env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", build_wokwi_image)