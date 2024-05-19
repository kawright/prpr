#!/bin/bash

# Copyright (C) 2024  Kristoffer A. Wright

# loc.sh - Counts the lines of C code in the src folder. Only counts .c and .h files.

find src -name '*.[hc]' | xargs wc -l
