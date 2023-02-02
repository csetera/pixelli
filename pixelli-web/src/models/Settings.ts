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
 * Type for a single setting value
 */
export type SettingValue = string | number | boolean;

/**
 * A named setting value
 */
export type NamedSettingValue = Record<string, SettingValue>;

/**
 * A categorized array of settings
 */
export type CategorizedSettings = Record<string, NamedSettingValue>;

