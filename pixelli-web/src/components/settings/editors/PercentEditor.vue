<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<template>
  <v-slider min="0" max="100" :label="props.setting.Name" v-model="value" />
</template>

<script lang="ts" setup>
  import { ref, watch } from 'vue';
  import { Setting } from '@/models/Settings'

  const emit = defineEmits<{
    (e: 'valueUpdated', value: number): void
  }>()

  const props = defineProps<{
    setting: Setting
  }>()

  const value = ref(props.setting.Value as number);
  watch(value, (newValue: number) => {
    emit('valueUpdated', newValue);
  });
</script>
