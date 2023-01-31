<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->
<template>
  <v-app :theme="themeStore.vuetifyTheme">
    <default-bar />
    <navigation />
    <default-view />
  </v-app>
</template>

<script lang="ts" setup>
  import DefaultBar from './AppBar.vue'
  import DefaultView from './View.vue'
  import Navigation from './Navigation.vue';

  import { useThemeStore } from '@/store/theme-store'

  const themeStore = useThemeStore();
</script>
