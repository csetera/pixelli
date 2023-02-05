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
        <v-label>{{ props.meta.Name }}</v-label>
      </v-row>
      <v-row>
        <v-btn :color="data.color" :style="textStyle" @click="openColorPicker">
          Color Chip

          <v-dialog v-model="data.dialog" activator="parent" width="300">
            <v-color-picker :modes="[ 'hexa' ]" mode="hexa" hide-inputs :model-value="data.color" width="300" />
            <v-btn @click="data.dialog = false">Close Dialog</v-btn>
          </v-dialog>

        </v-btn>
      </v-row>
    </v-container>
  </v-input>
</template>

<script lang="ts" setup>
  import { computed, reactive } from 'vue';
  import { SettingMeta } from '@/models/SettingsMeta';

  const props = defineProps<{
    meta: SettingMeta
  }>()

  const data = reactive({
    dialog: false,
    color: '#ff0000'
  });

  const textStyle = computed(() => {
    return { color: getContrastYIQ(data.color) }
  });

  /**
   * Click handler to open the color picker.
   */
  function openColorPicker(): void {
    console.log("Open picker");
  }

  /**
   * Calculate a contrasting color to the one that is specified.
   * Based on https://24ways.org/2010/calculating-color-contrast/.
   *
   * @param hexcolor
   */
  function getContrastYIQ(hexcolor: string): string {
    let normalized = (hexcolor.startsWith("#")) ? hexcolor.slice(1) : hexcolor;

    let r = parseInt(normalized.slice(0, 2), 16);
    let g = parseInt(normalized.slice(2, 4), 16);
    let b = parseInt(normalized.slice(4, 6), 16);

    let yiq = ((r * 299) + (g * 587) + (b * 114)) / 1000;

    return (yiq >= 128) ? 'black' : 'white';
  }
</script>
