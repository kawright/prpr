// Copyright (C) 2024  Kristoffer A. Wright

/*
 * fdback.h - Command Feedback
 */

#ifndef __FDBACK_H__
#define __FDBACK_H__

#include <stdbool.h>

/*
 * Report a command success.
 */
void fdback_ok();

/*
 * Report a command failure.
 */
void fdback_err();

/*
 * Set whether feedback is enabled or disabled.
 */
void fdback_set(bool val);

#endif
