#**********************************************************************************
# Copyright (C) 2023-2025 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#*********************************************************************************/

#
# PlatformIO custom target to connect a to the Websocket
# serial port
#
# https://websocket-client.readthedocs.io/en/latest/index.html
#
import importlib
Import("env")
# from pprint import pprint
from ZeroconfServiceDiscovery import ZeroconfServiceDiscovery

def on_ws_error(wsapp, exception):
    print("Error: " + str(exception))

def on_ws_message(wsapp, message):
    print(message)

def on_ws_open(wsapp):
    print("Connection opened")

def websocket_serial(*args, **kwargs):
    # Make sure the necessary modules are installed and dynamically loaded
    print("Installing zeroconf module")
    env.Execute("$PYTHONEXE -m pip install zeroconf")
    zeroconf = importlib.import_module('zeroconf') # https://python-zeroconf.readthedocs.io/en/latest/

    print("Installing websocket-client module")
    env.Execute("$PYTHONEXE -m pip install websocket-client")
    websocket = importlib.import_module('websocket')

    # Get some help searching for the target server
    service_discovery = ZeroconfServiceDiscovery(zeroconf)
    selected_service = service_discovery.select_pixelli_instance()
    mdns_name = selected_service.server
    if mdns_name.endswith('.'):
        mdns_name = mdns_name[:-1]
    ws_url = "ws://" + mdns_name + "/ws_serial"

    # Start up the websocket listener
    print("Starting up Websocket connection on: " + ws_url)
    wsapp = websocket.WebSocketApp(ws_url, on_error=on_ws_error, on_message=on_ws_message, on_open=on_ws_open)
    wsapp.run_forever()

    return

#
# Wire up the custom targets
#
env.AddCustomTarget(
    name="websocket_serial",
    dependencies=None,
    actions=[
        websocket_serial
    ],
    title="Websocket Serial",
    description="Connect to Websocket serial on device"
)
