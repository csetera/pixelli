<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<template>
    <v-expansion-panel-text>
      <v-form>
        <metadata-driven-setting-editor
          v-for="setting in props.settings"
          :key="setting.Name"
          :setting="setting"
          @setting-updated="settingUpdated"/>
      </v-form>
    </v-expansion-panel-text>
</template>

<script lang="ts" setup>
  import { Setting } from '@/models/Settings';
  import MetadataDrivenSettingEditor from '@/components/settings/editors/MetadataDrivenSettingEditor.vue';

  const emit = defineEmits<{
    (e: 'settingUpdated', value: Setting): void
  }>()

  const props = defineProps<{
    settings: Setting[]
  }>()

  function settingUpdated(setting: Setting): void {
    emit("settingUpdated", setting);
  }
</script>
