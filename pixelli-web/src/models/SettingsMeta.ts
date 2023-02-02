/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/

//
// Typescript interfaces for API "settings-meta" response
//

/**
 * Supported setting types
 */
export enum SettingType {
  Number = 'number',
  String = 'string',
  Percent = 'percent',
  Color = 'color'
}

/**
 * Metadata for a single setting
 */
export interface SettingMeta {
  Name: string;
  Type: SettingType;
}

/**
 * Metadata for a group of settings.
 */
export type SettingsMeta = Record<string, SettingMeta[]>;
