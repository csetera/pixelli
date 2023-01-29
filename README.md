# Pixelli

[ESP32](https://www.espressif.com/en/products/socs/esp32) software to drive a 3D printable LED matrix based on WS2812B LED strips.

![Matrix Video](docs/matrix-1500.gif)

## Contents

* [Introduction](#introduction)
* [Feature Overview](#feature-overview)
* [Getting started](#getting-started)
    * [Clone](#clone)
    * [Build](#build)
        * [Configuration](#configuration)
        * [Environments](#environments)
* [Additional Notes](#additional-notes)
    * [Software Design](#software-design)
    * [API](#api)
    * [Logging](#logging)
    * [Testing](#testing)
* [Contribute](#contribute)
* [License](#license)

## Introduction

This repository provides the implemnetation of ESP32 software to drive an LED matrix built using 3D printed parts and WS2812B LED strips.

## Feature overview

*   Easy to configure using [ESP Smartconfig](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_smartconfig.html)
*   Rotating display:
    * Current time
    * Current temperature
    * Top headlines
*   IP Geolocation


All 3D printed parts can be found on [Thingiverse](https://www.thingiverse.com/thing:5761343).  Look for a future Instructables write-up with the full build details.

## Getting Started

### Clone

This project does not provide binary builds at this time.  Clone this repository to get started:

```
git clone https://github.com/csetera/pixelli.git
```

### Build

The software can be built and managed using [PlatformIO](https://platformio.org/).  To learn more about using PlatformIO for development take a look at [these tutorials](https://docs.platformio.org/en/stable/tutorials/index.html).

#### Configuration

Before attempting to build for the first time, the project must be configured.  Configuration of the project is handled by the `config.ini` file.  Copy `config_example.ini` to `config.ini` and configure the various values.

```ini
################################################################
# Sample configuration for setup and development
#
# Copy to config.ini and fill in details
################################################################

##############################
# Explicit WiFi configuration
##############################
[wifi]
mdns_name=pixelli
mock_mdns_name=pixelli_mock

##############################
# OTA update related settings
##############################
[ota]
password=xxxxx

##############################
# API Keys
##############################
[api_keys]
abstractapi=xxxxxxx
newsapi=xxxxxx
openweathermap=xxxxxx
```

There are currently three services required for the software to function:

* [Abstract API](https://app.abstractapi.com/) <br/> For IP Geolocation
* [OpenWeatherMap](https://openweathermap.org/) <br /> for local weather information
* [News API](https://newsapi.org/) <br/> To retrieve top news headlines

Each service will require a registered API key in order to function.

#### Environments

The `platformio.ini` file provides multiple build environments for use, depending on the goals.

* esp32_matrix_serial <br/> Targets a matrix of WS2812B LEDs driven by an ESP32.  Uploads and logging occur over serial port.
* esp32_matrix_ota <br/> Targets a matrix of WS2812B LEDs driven by an ESP32.  Uploads and logging occur over the air.
* esp32_mock_matrix_serial <br/> Targets an OLED "mock" matrix driven by an ESP32 to use for testing purposes.  Uploads and logging occur over serial port.
* esp32_mock_matrix_ota <br/> Targets an OLED "mock" matrix driven by an ESP32 to use for testing purposes.  Uploads and logging occur over the air.

### Web Application

The [Vue.js](https://vuejs.org/) web application for use in controlling Pixelli can be found in the [pixelli-web](pixelli-web/README.md) folder.  This web application can be accessed at, for example, http://pixelli.local.  See the web application Readme for more information about developing and debugging the web application.  Deploy the web application to the ESP32, execute the following Platform IO tasks:
1. Custom -> Build Webpp
1. Platform -> Build Filesystem Image
1. Platform -> Upload Filesystem Image

## Additional Notes

### Software Design

The software is broken up between two primary categories of functionality:

* Services <br/> API and other data services that are headless.
* Widgets <br/> Widgets consume the data provided by the Services to produce the output in the display.

The `DisplayManager` is responsible for managing which widgets are displayed and in what order.  Data and widget updates are managed through cooperative multitasking provided by the [TaskScheduler library](https://github.com/arkhipenko/TaskScheduler).

### API

[ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) provides the support for REST API implementations.  At the moment, there is only one API available:

```
http://pixelli.local/api/info
```

### Logging

In addition to the standard Serial-based logging, the software also provides a WebSocket based logger endpoint.  The WebSocker is available at `ws://pixelli.local/ws_serial` (assuming the MDNS name has been set to `pixelli`).  An additional custom script `Websocket Serial` can be found in the PlatformIO Project Tasks view in the Custom section.  That script will start up a Python-based WebSocket client to receive the logger output.

### Testing

There are no unit tests at this time.  The software does provide support for a "mock" matrix comprised of an ESP32 and a 1.5inch RGB OLED Display Module (for example [one of these](https://www.amazon.com/gp/product/B07V579YK2/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)) that is driven by an SSD1351.  This allows new functioality to be created without the need to carry around the actual matrix!

## Contribute

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[Mozilla Public License](https://choosealicense.com/licenses/mit/)
