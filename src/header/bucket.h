/*

 * bucket.h
 * Declares header dependencies, constants, structures and functions.
 *
 * inedito

 */

#ifndef __19_HEADER_BUCKET__
#define __19_HEADER_BUCKET__

// Headers

#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include "configuration.h"

// Constants

#define BUCKET_CODE_ERROR_CONFIGURATION -1001
#define BUCKET_CODE_ERROR_GENERIC       -1001
#define BUCKET_CODE_ERROR_NULL          -1002
#define BUCKET_CODE_SUCCESS             0

#define BUCKET_MEMORY_SIZE_MAX          128
#define BUCKET_MEMORY_SIZE_MIN          1

// Structures

struct bucket_file_structure {

    char *name;
    struct bucket_file_structure *next;
};

struct bucket_structure {

    char *bucket, *name, *pattern;
    struct bucket_file_structure *files;
};

// Functions

/*

 * int bucket_entry_monitor ( struct bucket_structure * )
 * Collect files in entry bucket.
 *
 * Input
 * - struct bucket_structure * : bucket structure
 *
 * Output
 * - int : code
 *
 * Possible values are:
 * - BUCKET_CODE_ERROR_* : one of the available error code returned by "bucket_error" function
 * - BUCKET_CODE_SUCCESS : function terminated with no error

 */
int bucket_entry_monitor ( struct bucket_structure * );

/*

 * void bucket_representation ( struct bucket_structure * )
 * Print an entry bucket representation to STDOUT (standard output).
 *
 * Input
 * - struct bucket_structure * : bucket structure
 *
 * Output
 * None

 */
void bucket_entry_representation ( struct bucket_structure );

/*

 * int bucket_error ( char * )
 * Print a error message to STDERR (standard error).
 *
 * Input
 * - char * : message
 *
 * Output
 * - int : code
 *
 * Possible values are:
 * - BUCKET_CODE_ERROR_NULL    : input argument is NULL
 * - BUCKET_CODE_ERROR_GENERIC : generic error

 */
int bucket_error ( char * );

/*

 * struct configuration_entry_structure *bucket_lookup ( struct configuration_entry_structure *, char * )
 * Look for a compatible entry comparing entry pattern file name.
 *
 * Input
 * - configuration_entry_structure * : configuration entries
 * - char *                          : file name
 *
 * Output
 * - int : code
 *
 * Possible values are:
 * - BUCKET_CODE_ERROR_* : one of the available error code returned by "bucket_error" function
 * - BUCKET_CODE_SUCCESS : function terminated with no error

 */
struct configuration_entry_structure *bucket_lookup ( struct configuration_entry_structure *, char * );

/*

 * int bucket_monitor ( struct configuration_structure )
 * Observe files in monitor bucket, lookup a compatible entry from configuration and move file to relative bucket.
 *
 * Input
 * - struct configuration_structure : configuration structure
 *
 * Output
 * - int : code
 *
 * Possible values are:
 * - BUCKET_CODE_ERROR_* : one of the available error code returned by "bucket_error" function
 * - BUCKET_CODE_SUCCESS : function terminated with no error

 */
int bucket_monitor ( struct configuration_structure );

/*

 * int bucket_move ( char *, char *, char * )
 * Move a file from monitor bucket to entry bucket.
 *
 * Input
 * - char * : monitor bucket
 * - char * : entry bucket
 * - char * : file name
 *
 * Output
 * - int : code
 *
 * Possible values are:
 * - BUCKET_CODE_ERROR_* : one of the available error code returned by "bucket_error" function
 * - BUCKET_CODE_SUCCESS : function terminated with no error

 */
int bucket_move ( char *, char *, char * );

#endif
