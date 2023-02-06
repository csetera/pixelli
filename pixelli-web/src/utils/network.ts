/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/

/**
 * fetch a network resources, accounting for different API base paths.
 *
 * @param relativePath
 * @returns
 */
export function doFetch(relativePath: string, init?: RequestInit): Promise<Response> {
  const url = import.meta.env.VITE_API_BASE ?
    `${import.meta.env.VITE_API_BASE}${relativePath}` :
    relativePath;

  return fetch(url, init);
}
