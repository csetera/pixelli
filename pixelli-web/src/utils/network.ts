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

/**
 * Make a GET request to the specified path.
 *
 * @param relativePath
 * @param signal
 * @returns
 */
export function doGet(relativePath: string, signal?: AbortSignal): Promise<Response> {
  const init = {
    signal: signal
  }

  return doFetch(relativePath, init);
}

/**
 * POST the specified body to the path.
 *
 * @param relativePath
 * @param body
 * @returns
 */
export function doPost(relativePath: string, body: any, signal?: AbortSignal): Promise<Response> {
  const init = {
    method: 'POST',
    body: JSON.stringify(body),
    signal: signal,
    headers: {
      'Content-type': 'application/json; charset=UTF-8',
    }
  };

  return doFetch(relativePath, init);
}
