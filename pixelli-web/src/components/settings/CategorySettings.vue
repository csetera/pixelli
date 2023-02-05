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
        <metadata-driven-setting-editor v-for="meta in props.meta" :key="meta.Name" :meta="meta" />
      </v-form>
    </v-expansion-panel-text>
</template>

<script lang="ts" setup>
  import { SettingMeta } from '@/models/SettingsMeta';
  import MetadataDrivenSettingEditor from '@/components/settings/editors/MetadataDrivenSettingEditor.vue';

  const props = defineProps<{
    meta: SettingMeta[]
  }>()
</script>
