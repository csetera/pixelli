/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/
import 'vue-router'
import { createRouter, createWebHistory } from 'vue-router'
import { isNavigationFailure } from 'vue-router'
import DefaultLayout from '@/layouts/default/Default.vue';
import Home from '@/views/Home.vue';
import Info from '@/views/Info.vue';
import Settings from '@/views/Settings.vue';
import NotFound from '@/components/utility/NotFound.vue';

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
        component: Home,
        meta: {
          icon: "mdi-home-outline"
        },
      },
      {
        path: 'info',
        name: 'Information',
        component: Info,
        meta: {
          icon: "mdi-information-outline"
        },
      },
      {
        path: 'settings',
        name: 'Settings',
        component: Settings,
        meta: {
          icon: "mdi-cog-outline"
        },
      },
    ],
  },
  {
    path: '/:pathMatch(.*)*',
    name: 'not-found',
    component: NotFound
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
})

//
// Capture and log navigation failures
//
router.afterEach((to, from, failure) => {
  if (isNavigationFailure(failure)) {
    console.log("Navigation failure", to, from, failure);
  }
});

export default router
