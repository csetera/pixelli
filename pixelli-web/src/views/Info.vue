<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->
<template>
  <AsyncContent :task="task" v-slot="{ lastValue }">
    <Content v-if="lastValue" :info="lastValue" />
  </AsyncContent>
</template>

<script lang="ts" setup>
  import AsyncContent from '@/components/utility/AsyncContent.vue';
  import Content from '@/components/info/Content.vue';

  import { DeviceInfo } from '@/models/DeviceInfo';
  import { useTask } from 'vue-concurrency';

  const url = import.meta.env.VITE_API_BASE ?
    `${import.meta.env.VITE_API_BASE}/api/info` :
    '/api/info';

  const task = useTask(function*() {
    const response = yield fetch(url);
    return response.json() as DeviceInfo;
  });

  task.perform();

</script>
