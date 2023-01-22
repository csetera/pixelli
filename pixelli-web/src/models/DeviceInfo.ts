/**********************************************************************************
 # Copyright (C) 2023 Craig Setera
 #
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at https://mozilla.org/MPL/2.0/.
 #*********************************************************************************/

//
// Typescript interfaces for API "info" response
//
export interface Sketch {
    Size: number;
    FreeSpace: number;
}

export interface Heap {
    Size: number;
    Free: number;
    MinFree: number;
    MaxAlloc: number;
}

export interface Psram {
    Size: number;
    Free: number;
    MinFree: number;
    MaxAlloc: number;
}

export interface Chip {
    Model: string;
    Revision: number;
    Cores: number;
}

export interface Flash {
    ChipSpeed: number;
    ChipMode: number;
}

export interface DeviceInfo {
    Build: Date;
    IpAddr: string;
    SdkVersion: string;
    sketch: Sketch;
    Heap: Heap;
    Psram: Psram;
    Chip: Chip;
    Flash: Flash;
}

