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
import RemoteViewer from '@/views/RemoteViewer.vue';
import Settings from '@/views/Settings.vue';
import NotFound from '@/components/utility/NotFound.vue';

// Add some structure to the route metadata
// The navigation drawer is driven by the router
// routes
declare module 'vue-router' {
  interface RouteMeta {
    icon?: string,
    navigable: boolean,
    requiresFeature?: string,
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
          icon: "mdi-home-outline",
          navigable: true
        },
      },
      {
        path: 'info',
        name: 'Information',
        component: Info,
        meta: {
          icon: "mdi-information-outline",
          navigable: true
        },
      },
      {
        path: 'settings',
        name: 'Settings',
        component: Settings,
        meta: {
          icon: "mdi-cog-outline",
          navigable: true
        },
      },
      {
        path: 'remote-view',
        name: 'Remote View',
        component: RemoteViewer,
        meta: {
          icon: "mdi-binoculars",
          navigable: true,
          requiresFeature: 'RemoteView'
        },
      },
    ],
  },
  {
    path: '/:pathMatch(.*)*',
    name: 'not-found',
    component: NotFound,
    meta: {
      navigable: false
    }
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
