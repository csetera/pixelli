#**********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#*********************************************************************************/

Import("env")
import pprint
import subprocess

platform = env.PioPlatform() # type: ignore
MKFSTOOL_DIR = platform.get_package_dir("tool-mklittlefs")
MKFSTOOL = f'{MKFSTOOL_DIR}/mklittlefs'

def build_littlefs_image(*args, **kwargs):
    spiffs_target = f'{env.get("PROJECT_DIR")}/.pio/build/{env.get("PIOENV")}/littlefs.bin'
    print(f'Building LittleFS filesystem image into: {spiffs_target}...')
    subprocess.run([ MKFSTOOL, "--create", "data", '--size', '3538944', spiffs_target ], cwd = env.get("PROJECT_DIR"))
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
