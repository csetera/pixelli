<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<!-- Dynamic wrapper component for editors of different types -->
<template>
  <component :is="editorComponent" :setting="setting" @value-updated="editorValueUpdated" />
</template>

<script lang="ts" setup>
  import { computed } from 'vue';
  import { Setting, SettingType, SettingValue } from '@/models/Settings'

  import ColorEditor from '@/components/settings/editors/ColorEditor.vue';
  import NumberEditor from '@/components/settings/editors/NumberEditor.vue';
  import PasswordEditor from '@/components/settings/editors/PasswordEditor.vue';
  import PercentEditor from '@/components/settings/editors/PercentEditor.vue';
  import StringEditor from '@/components/settings/editors/StringEditor.vue';

  type EditorConfiguration = {
    [key in SettingType]: any;
  };

  const editors: EditorConfiguration = {
    color: ColorEditor,
    number: NumberEditor,
    password: PasswordEditor,
    percent: PercentEditor,
    string: StringEditor
  };

  const emit = defineEmits<{
    (e: 'settingUpdated', value: Setting): void
  }>()

  const props = defineProps<{
    setting: Setting
  }>()

  const editorComponent = computed(() => {
    return props.setting.Type in editors ? editors[props.setting.Type] : StringEditor;
  })

  function editorValueUpdated(value: SettingValue): void {
    emit('settingUpdated', {
      Name: props.setting.Name,
      Type: props.setting.Type,
      Value: value
    });
  }
</script>
