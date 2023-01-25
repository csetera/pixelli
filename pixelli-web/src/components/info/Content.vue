<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<template>
  <v-card title="Device Info">
    <template v-slot:text>
        {{ info }}
    </template>
  </v-card>
</template>

<script lang="ts" setup>
  import { defineProps } from "vue";
  import { DeviceInfo } from '@/models/DeviceInfo';

  const props = defineProps<{
    info: DeviceInfo
  }>()
</script>
