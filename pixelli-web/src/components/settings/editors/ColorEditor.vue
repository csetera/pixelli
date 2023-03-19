<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<template>
  <v-input>
    <v-container fluid>
      <v-row>
        <v-col cols="auto">
          <v-label>{{ props.setting.Name }}</v-label>
        </v-col>

        <v-col>
          <v-btn :color="color" :style="textStyle">
            {{ color }}

            <v-dialog v-model="dialogOpen" activator="parent" width="300">
              <v-color-picker :modes="[ 'hexa' ]" mode="hexa" hide-inputs width="300" v-model="color" />
              <v-btn @click="dialogOpen = false">Done</v-btn>
            </v-dialog>

          </v-btn>
        </v-col>
      </v-row>
    </v-container>
  </v-input>
</template>

<script lang="ts" setup>
  import { computed, ref, watch } from 'vue';
  import { Setting } from '@/models/Settings';
  import { getContrastYIQ } from '@/utils/colors';

  const dialogOpen = ref(false);

  const emit = defineEmits<{
    (e: 'valueUpdated', value: string): void
  }>()

  const props = defineProps<{
    setting: Setting
  }>()

  const color = ref(props.setting.Value as string);
  watch(color, (newValue: string) => {
    emit('valueUpdated', newValue);
  });

  // Return a contrasting text style
  const textStyle = computed(() => {
    return { color: (getContrastYIQ(color.value) >= 128) ? 'black' : 'white' }
  });

</script>
