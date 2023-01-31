<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->
<template>
  <v-app-bar>
    <v-app-bar-title>
      <v-icon icon="mdi-led-on" />
      Pixelli
    </v-app-bar-title>

    <!-- Theme action -->
    <v-tooltip text="Toggle Light/Dark">
      <template v-slot:activator="{ props }">
        <v-btn v-bind="props" iconv @click="toggleTheme()">
          <v-icon>mdi-theme-light-dark</v-icon>
        </v-btn>
      </template>
    </v-tooltip>
  </v-app-bar>
</template>

<script lang="ts" setup>
  import { useThemeStore } from '@/store/theme-store'

  const themeStore = useThemeStore();

  /**
   * Toggle the current theme
   */
  function toggleTheme(): void {
    themeStore.toggleTheme();
  }
</script>
