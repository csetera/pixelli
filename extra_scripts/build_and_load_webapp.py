#**********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#*********************************************************************************/

#
# PlatformIO custom target to build the web application
# and copy it into the "data/webapp" folder where it can
# be built into a file system image and uploaded to the
# device.
#
import os
import shutil
import subprocess
Import("env")

def is_included_in_path(path, name):
    qualified = os.path.sep.join([path, name])
    if os.path.isdir(qualified):
        return True

    if qualified.endswith(".map") or qualified.endswith(".map.gz"):
        return False
    else:
        return True # qualified.endswith(".gz")

def webapp_copy_ignores(path, names):
    return [name for name in names if not is_included_in_path(path, name)]

def build_webapp(*args, **kwargs):
    data_dir =  os.path.sep.join([ env['PROJECT_DIR'], "data", "webapp" ])
    webapp_dir = os.path.sep.join([ env['PROJECT_DIR'], "pixelli-web" ])
    webapp_dist_dir = os.path.sep.join([webapp_dir, "dist"])

    print("Building the webapp from '{0}' into '{1}'".format(webapp_dir, data_dir))
    subprocess.run(["yarn", "build"], cwd=webapp_dir)

    if (os.path.exists(data_dir)):
        shutil.rmtree(data_dir)

    shutil.copytree(webapp_dist_dir, data_dir, ignore=webapp_copy_ignores)

#
# Wire up the custom targets
#
env.AddCustomTarget(
    name="build_webapp",
    dependencies=None,
    actions=[
        build_webapp
    ],
    title="Build Webapp",
    description="Build the Webapp"
)
