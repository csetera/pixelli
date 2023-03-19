/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/

//
// Typescript interfaces for API "settings" response
//

/**
 * Supported setting types
 */
export enum SettingType {
  Number = 'number',
  String = 'string',
  Password = 'password',
  Percent = 'percent',
  Color = 'color'
}

/**
 * Type for a single setting value
 */
export type SettingValue = string | number | boolean;

/**
 * A single setting
 */
export interface Setting {
  Name: string;
  Type: SettingType;
  Value: SettingValue;
}

/**
 * A group of settings.
 */
export type CategorizedSettings = Record<string, Setting[]>;
