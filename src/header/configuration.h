/*

 * configuration.h
 * Declares header dependencies, constants, structures and functions.
 *
 * inedito

 */

#ifndef __19_HEADER_CONFIGURATION__
#define __19_HEADER_CONFIGURATION__

// Headers

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

// Constants

#define CONFIGURATION_CODE_ERROR_GENERIC  -1001
#define CONFIGURATION_CODE_ERROR_NULL     -1002
#define CONFIGURATION_CODE_ERROR_VALIDATE -1003
#define CONFIGURATION_CODE_SUCCESS        0

#define CONFIGURATION_MEMORY_SIZE_MAX     128
#define CONFIGURATION_MEMORY_SIZE_MIN     1

#define CONFIGURATION_SEPARATORS          "\n =,"

// Structures

struct configuration_entry_structure {

    char *bucket, *name, *pattern;
    struct configuration_entry_structure *next;
};

struct configuration_structure {

    char *bucket;
    struct configuration_entry_structure *entries;
};

// Functions

/*

 * int configuration_error ( char * )
 * Print a error message to STDERR (standard error).
 *
 * Input
 * - char * : message
 *
 * Output
 * - int : code
 *
 * Possible values are:
 * - CONFIGURATION_CODE_ERROR_NULL    : input argument is NULL
 * - CONFIGURATION_CODE_ERROR_GENERIC : generic error

 */
int configuration_error ( char * );

/*

 * int configuration_parse ( char *, struct configuration_structure * )
 * Parse a configuration file (already read) and return its structure.
 *
 * Inputs
 * - char *                           : file content
 * - struct configuration_structure * : configuration structure
 *
 * Output
 * - int : status code
 *
 * Possible values are:
 * - CONFIGURATION_CODE_ERROR_* : one of the available error code returned by "configuration_error" function
 * - CONFIGURATION_CODE_SUCCESS : function terminated with no error

 */
int configuration_parse ( char *, struct configuration_structure * );

/*

 * int configuration_read ( char *, char ** )
 * Read a configuration file (in read only) and return its content.
 *
 * Inputs
 * - char *  : file name
 * - char ** : file content
 *
 * Output
 * - int : status code
 *
 * Possible values are:
 * - CONFIGURATION_CODE_ERROR_* : one of the available error code returned by "configuration_error" function
 * - CONFIGURATION_CODE_SUCCESS : function terminated with no error

 */
int configuration_read  ( char *, char ** );

/*

 * void configuration_representation ( struct configuration_structure * )
 * Print a configuration representation to STDOUT (standard output).
 *
 * Input
 * - struct configuration_structure * : configuration structure
 *
 * Output
 * None

 */
void configuration_representation ( struct configuration_structure * );

/*

 * int configuration_validate ( struct configuration_structure * )
 * Validate a configuration structure and return status code.
 *
 * Input
 * - struct configuration_structure * : configuration structure
 *
 * Output
 * - int : status code
 *
 * Possible values are:
 * - CONFIGURATION_CODE_ERROR_VALIDATE : one of more fields are not valid
 * - CONFIGURATION_CODE_SUCCESS        : function terminated with no error

 */
int configuration_validate ( struct configuration_structure * );

#endif
