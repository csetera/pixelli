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
  import { computed, onMounted, toRaw  } from 'vue'
  import { RouteRecord, useRouter } from 'vue-router'
  import { useServerFeaturesStore } from '@/store/server-features-store';

  const router = useRouter();
  const serverFeaturesStore = useServerFeaturesStore();

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

    get navigable(): boolean {
      return (this.route.meta && this.route.meta.navigable) ? this.route.meta.navigable : false;
    }

    get path(): string {
      return (this.route.path) ? this.route.path : "";
    }

    get requiresFeature(): string | undefined {
      return this.route.meta.requiresFeature;
    }

    public isNavigable(serverFeatures: string[]): boolean {
      if (!this.navigable) {
        return false;
      }

      if (this.requiresFeature) {
        return serverFeatures.includes(this.requiresFeature);
      }

      return true;
    }
  }

  const routes = computed(() => {
    const features = serverFeaturesStore.features;

    return router.getRoutes()
      .map((route) => new NavigableRoute(route))
      .filter((route) => route.isNavigable(features));
  })

  /**
   * Navigate to the navigation target
   *
   * @param route the navigation target
   */
  function navigateTo(route: NavigableRoute) {
    router.push(route.path);
  }

  onMounted(() => {
    serverFeaturesStore.fetchFeatures();
  });
</script>
