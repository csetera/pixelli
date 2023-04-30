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
          <v-table>
            <tbody>
              <tr v-for="(value, key) in props.values" :key="key">
                <td width="20%">{{ key }}</td>
                <td>{{ value }}</td>
              </tr>
            </tbody>
          </v-table>
        </v-card-text>
      </v-card>
    </v-row>
  </v-container>
</template>

<script lang="ts" setup>
  const props = defineProps<{
    title: string,
    values: { [key: string]: any; }
  }>()
</script>
