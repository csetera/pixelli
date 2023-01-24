/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/
import 'vue-router'
import { createRouter, createWebHistory } from 'vue-router'
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
    component: () => import('@/layouts/default/Default.vue'),
    children: [
      {
        path: '',
        name: 'Home',
        meta: {
          icon: "mdi-home-outline"
        },
        // route level code-splitting
        // this generates a separate chunk (about.[hash].js) for this route
        // which is lazy-loaded when the route is visited.
        component: () => import('@/views/Home.vue'),
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

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
})

export default router
