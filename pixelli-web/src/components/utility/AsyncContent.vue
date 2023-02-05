<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<!-- Based on example from https://vue-concurrency.netlify.app/examples/loading-states/ -->
<template>
  <!-- Loading indicator -->
  <slot name="loading" v-if="task.isRunning">
    <v-responsive class="d-flex align-center text-center fill-height">
      <h2 class="text-h3">Loading</h2>
      <v-progress-circular :size="50" indeterminate />
    </v-responsive>
  </slot>

  <!-- Error indicator -->
  <slot name="error" v-else-if="task.isError" :error="lastError">
    <v-responsive v-if="true" class="d-flex align-center text-center">
      <v-alert type="error" closable location="top center">{{ lastError.message || "Something went wrong" }}</v-alert>
    </v-responsive>
  </slot>

  <!-- Actual content -->
  <slot v-else-if="task.performCount > 0" :lastValue="lastValue" />
</template>

<script lang="ts" setup>
  import { computed } from "vue";
  import { Task } from 'vue-concurrency';

  const props = defineProps<{
    task: Task<any, any>
  }>()

  const lastValue = computed(() => props.task.last && props.task.last.value);
  const lastError = computed(() => props.task.last && props.task.last.error);

</script>
