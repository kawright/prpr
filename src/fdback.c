// Copyright (C) 2024  Kristoffer A. Wright

/*
 * fdback.c - Command Feeback
 */

#include <stdbool.h>
#include <stdio.h>

#include "fdback.h"

static bool _enabled = true;

void fdback_ok() {
    if (_enabled) printf("OK\n");
}

void fdback_err() {
    if (_enabled) printf("ERR\n");
}

void fdback_set(bool val) {
    _enabled = val;
}
