// Copyright (C) 2024  Kristoffer A. Wright

/*
 * asset.c - Asset Data
 */

#include <stdint.h>

#include "asset.h"

void init_assets() {
    uint16_t help_len = (uint16_t) (_binary_asset_help_txt_end - _binary_asset_help_txt_start);
    _binary_asset_help_txt_start[help_len - 1] = '\0';

    uint16_t ver_len = (uint16_t) (_binary_asset_version_txt_end - _binary_asset_version_txt_end);
    _binary_asset_version_txt_start[ver_len - 1] = '\0';
}
