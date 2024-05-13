// Copyright (C) 2024  Krisoffer A. Wright

/*
 * err.h - Error handling
 */

#ifndef __ERR_H__
#define __ERR_H__

#include <stdarg.h>
#include <stdbool.h>


/*
 * The size of the buffer for error messages (minus one for the null terminator).
 */
#define MAX_ERR_MSG_LEN     127


/*
 * Enum type for listing all error codes.
 */
typedef enum __ERR_CODE__ {
    ERR_OK              = 0,            // OK. No error.
    ERR_GENERAL         = 1,            // Unhandled runtime error.
    ERR_ARGV            = 2,            // Malformed argument vector.
    ERR_MEM             = 3,            // Out-of-memory.
    ERR_IO              = 4,            // File open/read/write fail.
    ERR_SYNTAX          = 5,            // Command parse error.
    ERR_RANGE           = 6             // Out-of-range data.
} ErrCode;


/*
 * Struct type for storing an error state.
 */
typedef struct __ERR_ST__ {
    ErrCode         code;
    char            msg [MAX_ERR_MSG_LEN];
} ErrSt;


/*
 * Initialize an ErrSt. May also be used to reset an already initialized instance back to default values.
 */
void init_err_st(ErrSt *err_st);


/*
 * Throw an error by setting the fields of an ErrSt. Allows a formatted error message.
 */
void throw(ErrSt *err_st, ErrCode code, const char *msg, ...);


/*
 * Test if an error has been thrown on an ErrSt. Returns true if the code field is not ERR_OK.
 */
bool is_err_thrown(ErrSt *err_st);


/*
 * Print the fields of an ErrSt to STDERR, then exit the process with the code field value as the exit code.
 */
void panic(const ErrSt *err_st);


/*
 * Print the fields of an ErrSt to STDERR. Does not exit the process.
 */
void warning(const ErrSt *err_st);


#endif
