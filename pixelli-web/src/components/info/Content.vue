<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<template>
  <info-block title="General" :values="props.info.General" />
  <info-block title="Chip" :values="props.info.Chip" />
  <info-block title="Sketch" :values="props.info.Sketch" />
  <info-block title="Heap" :values="props.info.Heap" />
  <info-block title="Flash" :values="props.info.Flash" />
  <info-block title="Pseudo Static RAM" :values="props.info.Psram" />
</template>

<script lang="ts" setup>
  import { DeviceInfo } from '@/models/DeviceInfo';
  import InfoBlock from './InfoBlock.vue';

  const props = defineProps<{
    info: DeviceInfo
  }>()
</script>
