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
        <setting-editor v-for="meta in props.settingMetas" :key="meta.Name" :setting-meta="meta" />
      </v-form>
    </v-expansion-panel-text>
</template>

<script lang="ts" setup>
  import { SettingMeta } from '@/models/SettingsMeta';
  import SettingEditor from '@/components/settings/SettingEditor.vue';

  const props = defineProps<{
    settingMetas: SettingMeta[]
  }>()
</script>
