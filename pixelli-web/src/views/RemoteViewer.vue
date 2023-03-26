<!-- *********************************************************************************
# Copyright (C) 2023 Craig Setera
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
#********************************************************************************  -->
<template>
  <v-container class="fill-height">
    <v-responsive class="d-flex align-center text-center fill-height">
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
  const height = ref(1);
  const width = ref(1);
  const reactiveData = reactive(data);

  /**
   * Computes the array of LEDColor objects
   * from the pixel values sent by the server.
   */
  const ledColors = computed<LEDColor[]>(() => {
    let loggedOne = false;
    const result: LEDColor[] = [];

    if (reactiveData.pixelData) {
      for (var i = 0; i < reactiveData.pixelData?.byteLength; i++) {
        let rgb565 = reactiveData.pixelData[i];
        let cssColor = rgb565ToCssColor(rgb565);
        if ((rgb565 != 0) && !loggedOne) {
          loggedOne = true;
          console.log("Color pixel", rgb565, cssColor);
        }

        result.push(new LEDColor(i, cssColor));
      }
    }

    return result;
  })

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
        reactiveData.pixelData = new Uint16Array(buffer.slice(1))
        // console.log("show", reactiveData.pixelData);
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
    const socket = new WebSocket("ws://pixelli_mock.local/ws_remote");

    // Configure the socket
    socket.binaryType = 'arraybuffer';
    socket.onclose = handleClose;
    socket.onerror = handleError;
    socket.onopen = handleOpen;
    socket.onmessage =  handleMessage;

    // Hold the websocket in reactive state
    reactiveData.socket = socket;
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