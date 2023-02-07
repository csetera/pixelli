<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<template>
  <v-expansion-panels>
    <v-expansion-panel
      v-for="(value, key) in props.settings" :key="key" :title="key">
        <category-settings :settings="value" @setting-updated="settingUpdated(key, $event)"/>
    </v-expansion-panel>
  </v-expansion-panels>
</template>

<script lang="ts" setup>
  import { CategorizedSettings, Setting } from '@/models/Settings';
  import CategorySettings from './CategorySettings.vue';

  const props = defineProps<{
    settings: CategorizedSettings
  }>()

  function settingUpdated(category: string, setting: Setting): void {
    console.log('settingUpdated', category, setting);
  }
</script>
