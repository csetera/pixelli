/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/
import 'vue-router'
import { createRouter, createWebHistory } from 'vue-router'
import { isNavigationFailure, NavigationFailureType } from 'vue-router'
import DefaultLayout from '@/layouts/default/Default.vue';
import Home from '@/views/Home.vue';
import Info from '@/views/Info.vue';
import Settings from '@/views/Settings.vue';

// Add some structure to the route metadata
// The navigation drawer is driven by the router
// routes
declare module 'vue-router' {
  interface RouteMeta {
    icon?: string
  }
}

const routes = [
  {
    path: '/',
    component: DefaultLayout,
    children: [
      {
        path: '',
        name: 'Home',
        meta: {
          icon: "mdi-home-outline"
        },
        component: Home
      },
      {
        path: 'info',
        name: 'Information',
        meta: {
          icon: "mdi-information-outline"
        },
        component: Info,
      },
      {
        path: 'settings',
        name: 'Settings',
        meta: {
          icon: "mdi-cog-outline"
        },
        component: Settings
      },
    ],
  },
]

console.log("Router index: ", process.env.BASE_URL);
const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
})

router.afterEach((to, from, failure) => {
  // Any kind of navigation failure
  if (isNavigationFailure(failure)) {
    console.log("Navigation failure", to, from, failure);
  }
});

export default router
