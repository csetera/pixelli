<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->
<template>
  <AsyncContent :task="task" v-slot="{ lastValue }">
    <Content v-if="lastValue" :settings="lastValue" />
  </AsyncContent>
</template>

<script lang="ts" setup>
  import AsyncContent from '@/components/utility/AsyncContent.vue';
  import Content from '@/components/settings/Content.vue';

  import { CategorizedSettings } from '@/models/Settings';
  import { useTask } from 'vue-concurrency';
  import { doFetch } from '@/utils/network';

  const task = useTask(function*() {
    const response = yield doFetch('/api/settings');
    return response.json() as CategorizedSettings;
  });

  task.perform();

</script>
