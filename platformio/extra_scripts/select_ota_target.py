#**********************************************************************************
# Copyright (C) 2025 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#*********************************************************************************/
import importlib
from ZeroconfServiceDiscovery import ZeroconfServiceDiscovery
Import("env")

def before_upload(source, target, env):
    """
    Hook the before_upload event to choose the target
    """
    # Make sure the necessary modules are installed and dynamically loaded
    print("Installing zeroconf module")
    env.Execute("$PYTHONEXE -m pip install zeroconf")
    zeroconf = importlib.import_module('zeroconf') # https://python-zeroconf.readthedocs.io/en/latest/

    # Get some help searching for the target server
    service_discovery = ZeroconfServiceDiscovery(zeroconf)
    selected_service = service_discovery.select_pixelli_instance()
    mdns_name = selected_service.server
    if mdns_name.endswith('.'):
        mdns_name = mdns_name[:-1]

    # Set the upload port to the selected service
    env.Replace(UPLOAD_PORT=mdns_name)

env.AddPreAction("upload", before_upload)
