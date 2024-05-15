// Copyright (C) 2024  Kristoffer A. Wright

/*
 * asset.h - Asset Data
 */

#ifndef __ASSET_H__
#define __ASSET_H__

// ati_8x14.ttf
extern char _binary_asset_ati_9x14_ttf_start[];
extern char _binary_asset_ati_9x14_ttf_end[];

// ibm_iso8.ttf
extern char _binary_asset_ibm_iso8_ttf_start[];
extern char _binary_asset_ibm_iso8_ttf_end[];

// help.txt
extern char _binary_asset_help_txt_start[];
extern char _binary_asset_help_txt_end[];

// version.txt
extern char _binary_asset_version_txt_start[];
extern char _binary_asset_version_txt_end[];

/*
 * Initialize asset data. In particular, prepares string asset data by replacing the last character (should be a new
 * line) of each with a null-terminator.
 */
void init_assets();

#endif
