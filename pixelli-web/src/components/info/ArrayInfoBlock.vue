<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<template>
  <v-container>
    <v-row justify="space-around">
      <v-card width="90%">
        <v-card-item>
          <v-card-title>{{ props.title }}</v-card-title>
        </v-card-item>

        <v-card-text>
          <template v-if="hasValues">
            <v-list :items="props.values"></v-list>
          </template>
          <template v-else>
            No {{ props.title }}
          </template>
        </v-card-text>
      </v-card>
    </v-row>
  </v-container>
</template>

<script lang="ts" setup>
  import { computed } from 'vue';

  const props = defineProps<{
    title: string,
    values: any[];
  }>()

  const hasValues = computed(() => props.values.length > 0);
</script>
