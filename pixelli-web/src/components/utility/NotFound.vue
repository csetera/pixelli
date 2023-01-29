<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->

<!-- A simple component that is used when the router can't match a path.  It always -->
<!-- forces the route back to Home.  -->
<template>
  <div></div>
</template>

<script lang="ts" setup>
  import { useRouter } from 'vue-router';

  useRouter().replace("/");
</script>
