/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/

/**
 * Calculate a contrasting color to the one that is specified.
 * Based on https://24ways.org/2010/calculating-color-contrast/.
 *
 * @param hexcolor
 */
export function getContrastYIQ(hexcolor: string): number {
  const normalized = (hexcolor.startsWith("#")) ? hexcolor.slice(1) : hexcolor;

  const r = parseInt(normalized.slice(0, 2), 16);
  const g = parseInt(normalized.slice(2, 4), 16);
  const b = parseInt(normalized.slice(4, 6), 16);

  return ((r * 299) + (g * 587) + (b * 114)) / 1000;
}

/**
 * Convert the specified value to a hex string,
 * prepending a 0 as necessary to get the proper length.
 *
 * @param value
 * @returns
 */
function hexString(value: number): string {
  let hex = value.toString(16);
  if (hex.length == 1) {
    hex = '0' + hex;
  }

  return hex;
}

/**
 * Convert a RGB565 encoded color value to an
 * equivalent CSS color string.
 *
 * @param rgb565 the RGB565 encoded value
 * @returns
 */
export function rgb565ToCssColor(rgb565: number): string {
  // THanks to https://forum.arduino.cc/t/help-converting-rgb565-to-rgb888/275681
  const red = hexString(((((rgb565 >> 11) & 0x1F) * 527) + 23) >> 6);
  const green = hexString(((((rgb565 >> 5) & 0x3F) * 259) + 33) >> 6);
  const blue = hexString((((rgb565 & 0x1F) * 527) + 23) >> 6);

  return `#${red}${green}${blue}`;
}
