/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/

import App from './App.vue'
import { createApp } from 'vue'
import { registerPlugins } from '@/plugins'

const app = createApp(App)

app.config.errorHandler = (err, instance, info) => {
  console.error(err, instance, info);
}

app.config.warnHandler = (msg, instance, trace) => {
  console.warn(msg, instance, trace);
}

registerPlugins(app)

app.mount('#app')
