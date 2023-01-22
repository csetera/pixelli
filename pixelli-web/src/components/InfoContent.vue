<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->
<template>
  <v-container class="fill-height">
    {{  info  }}
  </v-container>
</template>

<script lang="ts" setup>
  import { useDeviceStore } from '@/store/device';
  import { storeToRefs } from "pinia";
  import { onMounted } from 'vue'

  const store = useDeviceStore();
  const { info } = storeToRefs(store);

  onMounted(() => {
    store.loadInfo();
  })
</script>
