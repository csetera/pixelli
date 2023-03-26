<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->
<template>
  <div class="led" :style="ledColor" />
</template>

<script lang="ts" setup>
  import { computed } from 'vue';

  const props = defineProps<{
    color: string
  }>()

  const ledColor = computed(() => `background-color: ${props.color}`)
</script>

<style scoped>
  .led {
    aspect-ratio: 1 / 1;
  }
</style>
