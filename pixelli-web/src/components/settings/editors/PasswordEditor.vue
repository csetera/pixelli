<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<template>
  <v-text-field
    :append-icon="showPassword ? 'mdi-eye' : 'mdi-eye-off'"
    :label="props.setting.Name"
    :type="showPassword ? 'text' : 'password'"
    @click:append="showPassword = !showPassword"
    v-model="value" />
</template>

<script lang="ts" setup>
  import { ref, watch } from 'vue';
  import { Setting } from '@/models/Settings';

  const emit = defineEmits<{
    (e: 'valueUpdated', value: string): void
  }>()

  const props = defineProps<{
    setting: Setting
  }>()

  const showPassword = ref(false);
  const value = ref(props.setting.Value as string);
  watch(value, (newValue: string) => {
    emit('valueUpdated', newValue);
  });
</script>
