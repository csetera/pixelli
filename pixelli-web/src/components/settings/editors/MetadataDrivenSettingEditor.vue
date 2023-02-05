<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<!-- Dynamic wrapper component for editors of different types -->
<template>
  <component :is="editors[props.meta.Type]" :meta="meta"/>
</template>

<script lang="ts" setup>
  import { SettingMeta, SettingType } from '@/models/SettingsMeta';

  import ColorEditor from '@/components/settings/editors/ColorEditor.vue';
  import NumberEditor from '@/components/settings/editors/NumberEditor.vue';
  import PercentEditor from '@/components/settings/editors/PercentEditor.vue';
  import StringEditor from '@/components/settings/editors/StringEditor.vue';

  type EditorConfiguration = {
    [key in SettingType]: any;
  };

  const editors: EditorConfiguration = {
    color: ColorEditor,
    number: NumberEditor,
    percent: PercentEditor,
    string: StringEditor
  };

  const props = defineProps<{
    meta: SettingMeta
  }>()
</script>
