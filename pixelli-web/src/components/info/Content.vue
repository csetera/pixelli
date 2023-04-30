<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<template>
  <array-info-block title="Features" :values="props.info.Features" />
  <object-info-block title="General" :values="props.info.General" />
  <object-info-block title="Chip" :values="props.info.Chip" />
  <object-info-block title="Sketch" :values="props.info.Sketch" />
  <object-info-block title="Heap" :values="props.info.Heap" />
  <object-info-block title="Flash" :values="props.info.Flash" />
  <object-info-block title="Pseudo Static RAM" :values="props.info.Psram" />
</template>

<script lang="ts" setup>
  import { DeviceInfo } from '@/models/DeviceInfo';
  import ArrayInfoBlock from './ArrayInfoBlock.vue';
  import ObjectInfoBlock from './ObjectInfoBlock.vue';

  const props = defineProps<{
    info: DeviceInfo
  }>()
</script>
