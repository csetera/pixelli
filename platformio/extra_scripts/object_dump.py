#**********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#*********************************************************************************/

#
# PlatformIO custom target to dump execute objdump against the  firmware ELF file
#
import subprocess
Import("env")

def object_dump(*args, **kwargs):
    elf_file = f'{env.get("PROJECT_DIR")}/.pio/build/{env.get("PIOENV")}/firmware.elf'
    output_target = f'{env.get("PROJECT_DIR")}/.pio/build/{env.get("PIOENV")}/objdump.txt'
    print("Dumping to: " + output_target)
    subprocess.run([ "objdump", "-t", "-x", "-C", elf_file ], stdout=open(output_target, "w"))
    return

#
# Wire up the custom targets
#
env.AddCustomTarget(
    name="object_dump",
    dependencies="$BUILD_DIR/${PROGNAME}.elf",
    actions=[
        object_dump
    ],
    title="Dump firmware objects",
    description="Display information from object files"
)
