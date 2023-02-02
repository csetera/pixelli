<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->
<template>
  <AsyncContent :task="task" v-slot="{ lastValue }">
    <Content v-if="lastValue" :settingsMeta="lastValue" />
  </AsyncContent>
</template>

<script lang="ts" setup>
  import AsyncContent from '@/components/utility/AsyncContent.vue';
  import Content from '@/components/settings/Content.vue';

  import { SettingsMeta } from '@/models/SettingsMeta';
  import { useTask } from 'vue-concurrency';

  const url = import.meta.env.VITE_API_BASE ?
    `${import.meta.env.VITE_API_BASE}/api/settings-meta` :
    '/api/settings-meta';

  const task = useTask(function*() {
    const response = yield fetch(url);
    return response.json() as SettingsMeta;
  });

  task.perform();

</script>
