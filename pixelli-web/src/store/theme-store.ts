/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/
import { defineStore } from 'pinia'
import { useStorage } from '@vueuse/core'

/**
 * Define the structure within the theme store.
 */
export interface ThemeStoreProperties {
  darkTheme: boolean
}

/**
 * Define the theme store, backed by local application
 * storage.
 */
export const useThemeStore = defineStore('theme-store', {
  state: () => ({
    darkTheme: useStorage<boolean>('darkTheme', true)
  }),

  getters: {
    /**
     * Return a boolean indicating whether to use the dark theme.
     *
     * @returns A boolean indicating whether to use the dark theme.
     */
    useDarkTheme(): boolean {
      return this.darkTheme;
    },

    /**
     * Return the name of the Vuetify theme to be used
     *
     * @returns the name of the Vuetify theme to be used
     */
    vuetifyTheme(): string {
      return this.darkTheme ? "dark" : "light";
    }
  },

  actions: {
    /**
     * Toggle between the dark and light themes.
     */
    toggleTheme(): void {
      this.darkTheme = !this.darkTheme;
    }
  },
})
