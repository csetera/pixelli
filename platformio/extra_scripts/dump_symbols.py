#**********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#*********************************************************************************/

#
# PlatformIO custom target to dump the symbols in the firmware ELF file
#
import subprocess
Import("env")

def dump_symbols(*args, **kwargs):
    elf_file = f'{env.get("PROJECT_DIR")}/.pio/build/{env.get("PIOENV")}/firmware.elf'
    output_target = f'{env.get("PROJECT_DIR")}/.pio/build/{env.get("PIOENV")}/symbols.txt'
    print("Dumping to: " + output_target)
    subprocess.run([ "nm", "-Cls", "--radix=d", "--size-sort", elf_file ], stdout=open(output_target, "w"))
    return

#
# Wire up the custom targets
#
env.AddCustomTarget(
    name="dump_symbols",
    dependencies="$BUILD_DIR/${PROGNAME}.elf",
    actions=[
        dump_symbols
    ],
    title="Dump firmware symbols",
    description="Dump symbols from object files"
)
