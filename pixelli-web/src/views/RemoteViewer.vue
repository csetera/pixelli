<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->
<template>
  <v-container class="fill-height">
    <v-responsive v-if="data.error" class="d-flex align-center text-center">
      <v-alert type="error" closable location="top center">Something went wrong</v-alert>
    </v-responsive>

    <v-responsive v-else-if="!receivedFirstBitmap" class="d-flex align-center text-center fill-height">
      <h2 class="text-h3">Loading</h2>
      <v-progress-circular :size="50" indeterminate />
    </v-responsive>

    <v-responsive v-else class="d-flex align-center text-center fill-height">
      <RemoteMatrix :height="height" :width="width" :colors="ledColors"/>
    </v-responsive>
  </v-container>

</template>

<script lang="ts" setup>
  import { computed, reactive, ref, onMounted, onUnmounted } from 'vue';
  import { rgb565ToCssColor } from '@/utils/colors';
  import LEDColor from '@/components/remote/LEDColor';
  import RemoteMatrix from '@/components/remote/Matrix.vue';

  /**
   * THe command bytes sent by the server
   */
  enum Commands {
    ON_CONNECT = 1,
    SHOW = 2
  }

  /**
   * Type information for reactive data
   */
  interface DataHolder {
    connected: boolean;
    pixelData?: Uint16Array,
    error?: any,
    socket?: WebSocket;
  }

  /**
   * Initial non-reactive data
   */
  const data: DataHolder = {
    connected: false
  };

  /**
   * Reactive data
   */
  const receivedFirstBitmap = ref(false);
  const height = ref(1);
  const width = ref(1);
  const reactiveData = reactive(data);

  /**
   * Computes the array of LEDColor objects
   * from the pixel values sent by the server.
   */
  const ledColors = computed<LEDColor[]>(() => {
    const result: LEDColor[] = [];

    if (reactiveData.pixelData) {
      const pixelCount = reactiveData.pixelData?.byteLength / 2;

      for (var i = 0; i < pixelCount; i++) {
        let rgb565 = reactiveData.pixelData[i];
        let cssColor = rgb565ToCssColor(rgb565);

        result.push(new LEDColor(i, cssColor));
      }
    }

    return result;
  })

  function getWebsocketURL(): string | undefined {
    if (!import.meta.env.VITE_API_BASE) {
      return undefined;
    }

    const url = new URL(import.meta.env.VITE_API_BASE);
    url.protocol = "ws:";
    url.pathname = "/ws_remote";

    return url.toString();
  }

  /**
   * Handle the websocket close event
   */
  function handleClose(): void {
    console.log("The connection has been closed successfully.");
    reactiveData.connected = false;
  }

  /**
   * Handle the websocket error event
   *
   * @param event
   */
  function handleError(event: Event): void {
    console.log("WebSocket error: ", event);
    reactiveData.error = event;
  }

  /**
   * Handle an event containing a message from the
   * server.
   *
   * @param event
   */
  function handleMessage(event: MessageEvent): void {
    const buffer = event.data as ArrayBuffer;
    const bytes = new Int8Array(buffer);

    switch (bytes[0]) {
      case Commands.ON_CONNECT:
        width.value = bytes[1];
        height.value = bytes[2];
        break;

      case Commands.SHOW:
        receivedFirstBitmap.value = true;
        reactiveData.pixelData = new Uint16Array(buffer.slice(1))
        break;
    }
  }

  /**
   * Handle the websocket open event
   */
  function handleOpen(): void {
    reactiveData.connected = true;
  }

  /**
   * Hook the Vue mounted event
   */
  onMounted(() => {
    // Connect the socket
    const socketURL = getWebsocketURL();
    if (socketURL) {
      const socket = new WebSocket(socketURL);

      // Configure the socket
      socket.binaryType = 'arraybuffer';
      socket.onclose = handleClose;
      socket.onerror = handleError;
      socket.onopen = handleOpen;
      socket.onmessage =  handleMessage;

      // Hold the websocket in reactive state
      reactiveData.socket = socket;
    }
  })

  /**
   * Hook the Vue unmounted event
   */
  onUnmounted(() => {
    if (reactiveData.socket) {
      reactiveData.socket.close();
    }
  })

</script>
