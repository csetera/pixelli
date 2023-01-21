<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->
<template>
  <v-navigation-drawer permanent expand-on-hover rail>
    <v-list density="compact" nav>
      <template v-for="route in routes" :key="route.path">
        <v-list-item :prepend-icon="route.icon" :title="route.name" :value="route.path" @click="navigateTo(route)" />
      </template>
    </v-list>
  </v-navigation-drawer>
</template>

<script lang="ts" setup>
  import { computed } from 'vue'
  import { RouteRecord, useRouter } from 'vue-router'

  const router = useRouter();

  /**
   * Simple wrapper class for interacting with a RouteRecord
   */
  class NavigableRoute {
    constructor(public route: RouteRecord) {
    }

    get icon(): string {
      return (this.route.meta && this.route.meta.icon) ? this.route.meta.icon : "";
    }

    get name(): string {
      return (this.route.name) ? this.route.name as string : "";
    }

    get path(): string {
      return (this.route.path) ? this.route.path : "";
    }
  }

  const routes = computed(() => {
    return router.getRoutes().map((route) => new NavigableRoute(route));
  })

  /**
   * Navigate to the navigation target
   *
   * @param route the navigation target
   */
  function navigateTo(route: NavigableRoute) {
    router.push(route.path);
  }
</script>
