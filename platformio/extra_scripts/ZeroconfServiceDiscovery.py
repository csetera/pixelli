#**********************************************************************************
# Copyright (C) 2025 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#*********************************************************************************/
import time
from typing import Dict, List

class ZeroconfServiceDiscovery:
    """
    A class for discovering and selecting services using Zeroconf.
    
    Usage:
        # If you have zeroconf installed and imported
        import zeroconf
        
        discoverer = ZeroconfServiceDiscovery(zeroconf)
        
        # Discover services
        services = discoverer.discover_services()
        
        # Select a service interactively
        selected_service = discoverer.select_pixelli_instance()
    """
    
    def __init__(self, zeroconf_module):
        """
        Initialize the service discovery with the zeroconf module.
        
        Args:
            zeroconf_module: The imported zeroconf module
        """
        self.zeroconf_module = zeroconf_module
        self.Zeroconf = zeroconf_module.Zeroconf
        self.ServiceBrowser = zeroconf_module.ServiceBrowser
        self.ServiceListener = zeroconf_module.ServiceListener
    
    class CapturingListener:
        """A service listener that captures discovered services."""
        
        def __init__(self, service_infos: Dict):
            self.service_infos = service_infos

        def update_service(self, zc, type_: str, name: str) -> None:
            """Called when a service is updated."""
            info = zc.get_service_info(type_, name)
            if info:
                self.service_infos[name] = info

        def remove_service(self, zc, type_: str, name: str) -> None:
            """Called when a service is removed."""
            if name in self.service_infos:
                del self.service_infos[name]

        def add_service(self, zc, type_: str, name: str) -> None:
            """Called when a new service is discovered."""
            info = zc.get_service_info(type_, name)
            if info:
                self.service_infos[name] = info

    def discover_services(self, service_type: str = "_http._tcp.local.", timeout: int = 5) -> List:
        """
        Discover services of the specified type.
        
        Args:
            service_type: The service type to search for (default: "_http._tcp.local.")
            timeout: How long to search for services in seconds (default: 5)
            
        Returns:
            List of discovered service info objects
        """
        service_infos = {}
        listener = self.CapturingListener(service_infos)
        
        # Create zeroconf instance and service browser
        zc = self.Zeroconf()
        browser = self.ServiceBrowser(zc, service_type, listener)
        
        try:
            print(f"Looking for services of type {service_type}...")
            time.sleep(timeout)
        finally:
            browser.cancel()
            zc.close()

        return list(service_infos.values())

    def select_pixelli_instance(self, service_type: str = "_http._tcp.local.", timeout: int = 5):
        """
        Discover services and allow user to select one interactively.
        
        Args:
            service_type: The service type to search for (default: "_http._tcp.local.")
            timeout: How long to search for services in seconds (default: 5)
            
        Returns:
            Selected service info object
        """
        services = self.discover_services(service_type, timeout)
        
        if not services:
            print("No services found.")
            return None
        
        print("\nDiscovered services:")
        for index, service in enumerate(services):
            print(f"{index + 1}: {service.name}")

        while True:
            try:
                user_input = int(input(f"\nEnter a number (1-{len(services)}): \n"))
                if user_input < 1 or user_input > len(services):
                    raise ValueError("Not in the list")
                break
            except ValueError:
                print(f"Invalid input. Please enter a number between 1 and {len(services)}.")

        return services[user_input - 1]
