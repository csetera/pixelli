/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/

//
// Typescript interfaces for API "info" and "features" responses
//
export interface Features {
  Features: string[];
}

export interface GeneralInfo {
  Build: Date;
  IpAddr: string;
  SdkVersion: string;
}

export interface SketchInfo {
    Size: number;
    FreeSpace: number;
}

export interface HeapInfo {
    Size: number;
    Free: number;
    MinFree: number;
    MaxAlloc: number;
}

export interface PsramInfo {
    Size: number;
    Free: number;
    MinFree: number;
    MaxAlloc: number;
}

export interface ChipInfo {
    Model: string;
    Revision: number;
    Cores: number;
}

export interface FlashInfo {
    ChipSpeed: number;
    ChipMode: number;
}

export interface DeviceInfo {
    Features: string[];
    General: GeneralInfo;
    Sketch: SketchInfo;
    Heap: HeapInfo;
    Psram: PsramInfo;
    Chip: ChipInfo;
    Flash: FlashInfo;
}

