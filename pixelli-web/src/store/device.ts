/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/
import { defineStore } from 'pinia'
import { DeviceInfo } from '@/models/DeviceInfo';

interface DeviceStoreStructure {
  info?: DeviceInfo
}

export const useDeviceStore = defineStore('device', {
  state: () => ({
    info: undefined
  } as DeviceStoreStructure),

  actions: {
    /**
     * Load the information from the device API
     */
    async loadInfo() {
      const result = await fetch(`${import.meta.env.VITE_API_BASE}/info`);
      this.info = await result.json();
    },
  },
})
