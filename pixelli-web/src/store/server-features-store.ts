/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/
import { defineStore } from 'pinia'
import { Features } from '@/models/DeviceInfo';
import { doGet } from '@/utils/network';
import { Router } from 'vue-router';

/**
 * Define the structure within the store
 */
export interface FeatureStoreProperties {
  features: string[],
}

export const useServerFeaturesStore = defineStore('server-features-store', {
  state: () => ({
    features: [],
  }),

  getters: {
    getFeatures(state: FeatureStoreProperties): string[] {
      return state.features;
    }
  },

  actions: {
    async fetchFeatures() {
      try {
        const featuresResponse = await (await doGet('/api/features')).json() as Features;
        this.features = featuresResponse.Features;
      } catch (error) {
        return error
      }
    }
  }
});
