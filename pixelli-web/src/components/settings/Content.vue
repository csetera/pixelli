<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<template>
  <v-container>
    <v-row>
      <v-expansion-panels>
        <v-expansion-panel v-for="(settingsArray, category) in settings" :key="category" :title="category">
          <category-settings :settings="settingsArray" @setting-updated="settingUpdated(category, $event)"/>
        </v-expansion-panel>
      </v-expansion-panels>
    </v-row>
    <v-row class="pa-md-4">
      <v-btn :disabled="!updated" @click="saveSettings">Save</v-btn>
    </v-row>
  </v-container>
</template>

<script lang="ts" setup>
  import { reactive, ref, toRaw  } from 'vue';
  import { CategorizedSettings, Setting } from '@/models/Settings';
  import CategorySettings from './CategorySettings.vue';

  const emit = defineEmits<{
    (e: 'saveSettings', value: CategorizedSettings): void
  }>()

  const props = defineProps<{
    settings: CategorizedSettings
  }>()

  const updated = ref(false);
  const settings = reactive(props.settings);

  /**
   * Handle the Save button by emitting a request to the parent
   * component to do the save/reload.
   */
  function saveSettings(): void {
    emit('saveSettings', toRaw(settings));
  }

  /**
   * Handler for the emitted event from the child component.
   *
   * @param category
   * @param setting
   */
  function settingUpdated(category: string, setting: Setting): void {
    const categorySettings = settings[category];
    categorySettings.forEach((categorySetting) => {
      if (categorySetting.Name == setting.Name) {
        categorySetting.Value = setting.Value;
        updated.value = true;
      }
    });
  }
</script>
