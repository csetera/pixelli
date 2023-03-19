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
