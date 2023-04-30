<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<!-- A Grid layout representation of a Matrix with individual pixels -->
<template>
  <div class="matrix" :style="matrixStyle">
    <LED v-for="ledColor in props.colors" :key="ledColor.index" :color="ledColor.color" />
  </div>
</template>

<script lang="ts" setup>
  import { computed } from 'vue';
  import LED from './LED.vue';
  import LEDColor from './LEDColor';

  const props = defineProps<{
    colors: LEDColor[],
    height: number,
    width: number
  }>()

  const matrixStyle = computed(() => `grid-template-columns: repeat(${props.width}, 1fr)`);
</script>

<style scoped>
  .matrix {
    display: grid;
    gap: 2px;
  }
</style>
