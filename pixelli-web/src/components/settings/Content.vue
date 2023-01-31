<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<template>
  {{  props.meta  }}
</template>

<script lang="ts" setup>
  import { SettingMeta } from '@/models/SettingsMeta';

  const props = defineProps<{
    meta: SettingMeta
  }>()
</script>
