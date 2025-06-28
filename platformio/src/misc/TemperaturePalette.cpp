/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "TemperaturePalette.h"

/*
https://www.esri.com/arcgis-blog/products/arcgis-pro/mapping/a-meaningful-temperature-palette/
https://github.com/FastLED/FastLED/wiki/Gradient-color-palettes
*/

const int MIN_TEMP = -50;
const int MAX_TEMP = 150;

DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
    // 0,  228,    240,    255,    // -100 to -60
    // 0,  228,    233,    250,    // -60 to -55
    // 0,  211,    226,    247,    // -55 to -50
      0,  203,    219,    244,    // -50 to -45
      5,  192,    212,    237,    // -45 to -40
     10,  184,    205,    234,    // -40 to -35
     15,  175,    198,    230,    // -35 to -30
     20,  167,    191,    227,    // -30 to -25
     25,  156,    184,    223,    // -25 to -20
     30,  147,    177,    215,    // -20 to -15
     35,  139,    164,    205,    // -15 to -10
     40,  127,    155,    195,    // -10 to -5
     45,  117,    145,    185,    // -5 to 0
     50,   98,    123,    164,    // 0 to 5
     55,   86,    113,    156,    // 5 to 10
     60,   77,    101,    145,    // 10 to 15
     65,   65,     92,    135,    // 15 to 20
     70,   57,     81,    127,    // 20 to 25
     75,   47,     71,    117,    // 25 to 30
     80,   38,     67,    111,    // 30 to 35
     85,   37,     79,    119,    // 35 to 40
     90,   38,     92,    128,    // 40 to 45
     95,   39,    103,    138,    // 45 to 50
    100,   38,    117,    147,    // 50 to 55
    105,   67,    129,    144,    // 55 to 60
    110,  100,    141,    137,    // 60 to 65
    115,  135,    154,    132,    // 65 to 70
    120,  171,    168,    125,    // 70 to 75
    125,  194,    171,    117,    // 75 to 80
    130,  193,    157,     97,    // 80 to 85
    135,  195,    138,     83,    // 85 to 90
    140,  193,    111,     74,    // 90 to 95
    145,  175,     77,     78,    // 95 to 100
    150,  159,     41,     76,    // 100 to 105
    155,  135,     32,     62,    // 105 to 110
    160,  110,     21,     49,    // 110 to 115
    165,   86,     12,     37,    // 115 to 120
    255,   63,      1,     22     // 120 to Max
};

/**
 * @brief Get the Color For Temperature (fahrenheit)
 *
 * @param temp
 * @return CRGB
 */
CRGB TemperaturePalette::GetColorForTemperature(int temp) {
    int adjustedTemp = temp - MIN_TEMP;

    adjustedTemp = (adjustedTemp < 0) ? 0 : adjustedTemp;
    adjustedTemp = (adjustedTemp > 255) ? 255 : adjustedTemp;

    uint8_t paletteIndex = (uint8_t) adjustedTemp;
    CRGBPalette32 heatPalette = heatmap_gp;
    CRGB color = ColorFromPalette(heatPalette, paletteIndex);

    // Logger::get().printf("GetColorForTemperature %d/%d/%d %d/%d/%d\n", temp, adjustedTemp, paletteIndex, color.r, color.g, color.b);
    return color;
}
