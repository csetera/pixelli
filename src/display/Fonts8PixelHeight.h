/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include <U8g2_for_Adafruit_GFX.h>

/**
 * @brief 8-pixel height fonts
 */

char* font_names[] = {
    "u8g2_font_6x10_tf",
    "u8g2_font_m2icon_9_tf",
    "u8g2_font_amstrad_cpc_extended_8f",
    "u8g2_font_amstrad_cpc_extended_8r",
    "u8g2_font_amstrad_cpc_extended_8n",
    "u8g2_font_amstrad_cpc_extended_8u",
    "u8g2_font_6x10_tn",
    "u8g2_font_6x10_mn",
    "u8g2_font_t0_11_tf",
    "u8g2_font_t0_11_tr",
    "u8g2_font_t0_11_te",
    "u8g2_font_t0_11_mf",
    "u8g2_font_t0_11_mr",
    "u8g2_font_t0_11_me",
    "u8g2_font_t0_11_t_all",
    "u8g2_font_t0_11b_tf",
    "u8g2_font_t0_11b_tr",
    "u8g2_font_t0_11b_te",
    "u8g2_font_t0_11b_mf",
    "u8g2_font_t0_11b_mr",
    "u8g2_font_t0_11b_me",
    "u8g2_font_t0_12_tf",
    "u8g2_font_t0_12_tr",
    "u8g2_font_t0_12_te",
    "u8g2_font_t0_12_mf",
    "u8g2_font_t0_12_mr",
    "u8g2_font_t0_12_me",
    "u8g2_font_t0_12b_tf",
    "u8g2_font_t0_12b_tr",
    "u8g2_font_t0_12b_te",
    "u8g2_font_t0_12b_mf",
    "u8g2_font_t0_12b_mr",
    "u8g2_font_t0_12b_me",
    "u8g2_font_profont12_tf",
    "u8g2_font_profont12_tr",
    "u8g2_font_profont12_tn",
    "u8g2_font_profont12_mf",
    "u8g2_font_profont12_mr",
    "u8g2_font_profont12_mn",
    "u8g2_font_diodesemimono_tr",
    "u8g2_font_bitcasual_tf",
    "u8g2_font_bitcasual_tr",
    "u8g2_font_bitcasual_tn",
    "u8g2_font_bitcasual_tu",
    "u8g2_font_bitcasual_t_all",
    "u8g2_font_nerhoe_tf",
    "u8g2_font_nerhoe_tr",
    "u8g2_font_nerhoe_tn",
    "u8g2_font_HelvetiPixel_tr",
    "u8g2_font_Wizzard_tr",
    "u8g2_font_helvB08_tf",
    "u8g2_font_helvB08_tr",
    "u8g2_font_helvB08_tn",
    "u8g2_font_helvB08_te",
    "u8g2_font_helvR08_tf",
    "u8g2_font_helvR08_tr",
    "u8g2_font_helvR08_tn",
    "u8g2_font_helvR08_te",
    "u8g2_font_ncenB08_tf",
    "u8g2_font_ncenB08_tr",
    "u8g2_font_ncenB08_tn",
    "u8g2_font_ncenB08_te",
    "u8g2_font_ncenR08_tf",
    "u8g2_font_ncenR08_tr",
    "u8g2_font_ncenR08_tn",
    "u8g2_font_ncenR08_te",
    "u8g2_font_luBIS08_tf",
    "u8g2_font_luBIS08_tr",
    "u8g2_font_luBIS08_tn",
    "u8g2_font_luBIS08_te",
    "u8g2_font_luBS08_tf",
    "u8g2_font_luBS08_tr",
    "u8g2_font_luBS08_tn",
    "u8g2_font_luBS08_te",
    "u8g2_font_luIS08_tf",
    "u8g2_font_luIS08_tr",
    "u8g2_font_luIS08_tn",
    "u8g2_font_luIS08_te",
    "u8g2_font_luRS08_tf",
    "u8g2_font_luRS08_tr",
    "u8g2_font_luRS08_tn",
    "u8g2_font_luRS08_te",
    "u8g2_font_robot_de_niro_tf",
    "u8g2_font_robot_de_niro_tr",
    "u8g2_font_robot_de_niro_tn",
    "u8g2_font_pressstart2p_8f",
    "u8g2_font_pressstart2p_8r",
    "u8g2_font_pressstart2p_8n",
    "u8g2_font_pressstart2p_8u"
};

const uint8_t* fonts[] {
    u8g2_font_6x10_tf,
    u8g2_font_m2icon_9_tf,
    u8g2_font_amstrad_cpc_extended_8f,
    u8g2_font_amstrad_cpc_extended_8r,
    u8g2_font_amstrad_cpc_extended_8n,
    u8g2_font_amstrad_cpc_extended_8u,
    u8g2_font_6x10_tn,
    u8g2_font_6x10_mn,
    u8g2_font_t0_11_tf,
    u8g2_font_t0_11_tr,
    u8g2_font_t0_11_te,
    u8g2_font_t0_11_mf,
    u8g2_font_t0_11_mr,
    u8g2_font_t0_11_me,
    u8g2_font_t0_11_t_all,
    u8g2_font_t0_11b_tf,
    u8g2_font_t0_11b_tr,
    u8g2_font_t0_11b_te,
    u8g2_font_t0_11b_mf,
    u8g2_font_t0_11b_mr,
    u8g2_font_t0_11b_me,
    u8g2_font_t0_12_tf,
    u8g2_font_t0_12_tr,
    u8g2_font_t0_12_te,
    u8g2_font_t0_12_mf,
    u8g2_font_t0_12_mr,
    u8g2_font_t0_12_me,
    u8g2_font_t0_12b_tf,
    u8g2_font_t0_12b_tr,
    u8g2_font_t0_12b_te,
    u8g2_font_t0_12b_mf,
    u8g2_font_t0_12b_mr,
    u8g2_font_t0_12b_me,
    u8g2_font_profont12_tf,
    u8g2_font_profont12_tr,
    u8g2_font_profont12_tn,
    u8g2_font_profont12_mf,
    u8g2_font_profont12_mr,
    u8g2_font_profont12_mn,
    u8g2_font_diodesemimono_tr,
    u8g2_font_bitcasual_tf,
    u8g2_font_bitcasual_tr,
    u8g2_font_bitcasual_tn,
    u8g2_font_bitcasual_tu,
    u8g2_font_bitcasual_t_all,
    u8g2_font_nerhoe_tf,
    u8g2_font_nerhoe_tr,
    u8g2_font_nerhoe_tn,
    u8g2_font_HelvetiPixel_tr,
    u8g2_font_Wizzard_tr,
    u8g2_font_helvB08_tf,
    u8g2_font_helvB08_tr,
    u8g2_font_helvB08_tn,
    u8g2_font_helvB08_te,
    u8g2_font_helvR08_tf,
    u8g2_font_helvR08_tr,
    u8g2_font_helvR08_tn,
    u8g2_font_helvR08_te,
    u8g2_font_ncenB08_tf,
    u8g2_font_ncenB08_tr,
    u8g2_font_ncenB08_tn,
    u8g2_font_ncenB08_te,
    u8g2_font_ncenR08_tf,
    u8g2_font_ncenR08_tr,
    u8g2_font_ncenR08_tn,
    u8g2_font_ncenR08_te,
    u8g2_font_luBIS08_tf,
    u8g2_font_luBIS08_tr,
    u8g2_font_luBIS08_tn,
    u8g2_font_luBIS08_te,
    u8g2_font_luBS08_tf,
    u8g2_font_luBS08_tr,
    u8g2_font_luBS08_tn,
    u8g2_font_luBS08_te,
    u8g2_font_luIS08_tf,
    u8g2_font_luIS08_tr,
    u8g2_font_luIS08_tn,
    u8g2_font_luIS08_te,
    u8g2_font_luRS08_tf,
    u8g2_font_luRS08_tr,
    u8g2_font_luRS08_tn,
    u8g2_font_luRS08_te,
    u8g2_font_robot_de_niro_tf,
    u8g2_font_robot_de_niro_tr,
    u8g2_font_robot_de_niro_tn,
    u8g2_font_pressstart2p_8f,
    u8g2_font_pressstart2p_8r,
    u8g2_font_pressstart2p_8n,
    u8g2_font_pressstart2p_8u
};

#define NUM_FONTS 88
