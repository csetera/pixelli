#**********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#*********************************************************************************/

Import("env")
import subprocess

MKFSTOOL='/bin/x86_64-linux-gnu-mklittlefs/mklittlefs'

def build_littlefs_image(*args, **kwargs):
    tool = f'{env.get("PROJECT_DIR")}{MKFSTOOL}'
    spiffs_target = f'{env.get("PROJECT_DIR")}/.pio/build/{env.get("PIOENV")}/{env.get("ESP32_SPIFFS_IMAGE_NAME")}.bin'
    print(f'Building LittleFS filesystem image into: {spiffs_target}...')
    subprocess.run([ tool, "--create", "data", spiffs_target ], cwd = env.get("PROJECT_DIR"))
    return

#
# Wire up the custom targets
#
env.AddCustomTarget(
    name="build_littlefs_image",
    dependencies=None,
    actions=[
        build_littlefs_image
    ],
    title="Build LittleFS Image",
    description="Build a LittleFS filesystem image for upload"
)
