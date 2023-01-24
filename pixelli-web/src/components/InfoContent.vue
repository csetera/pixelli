<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->
<template>
  <v-container class="fill-height">
    <template v-if="task.isRunning">
      <v-progress-circular indeterminate />
    </template>
    <template v-else-if="task.isError">
      <v-alert text="Something went wrong"></v-alert>
    </template>
    <template v-else>
      {{  task.last?.value  }}
    </template>
  </v-container>
</template>

<script lang="ts" setup>
  import { DeviceInfo } from '@/models/DeviceInfo';
  import { useTask } from 'vue-concurrency';

  const url = `${import.meta.env.VITE_API_BASE}/info`;
  const task = useTask(function*() {
    const response = yield fetch(url);
    return response.json() as DeviceInfo;
  });

  task.perform();

</script>
