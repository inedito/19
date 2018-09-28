/*

 * bucket.c
 * Defines header declarations.
 *
 * inedito

 */

// Headers

#include "header/bucket.h"

// Functions

int bucket_error ( char *message ) {

    // Check message

    if ( message == NULL ) return BUCKET_CODE_ERROR_NULL;

    // Write message to STDERR

    fprintf ( stderr, "ERROR: %s\n", message );

    // Return error code

    return BUCKET_CODE_ERROR_GENERIC;
}

struct configuration_entry_structure *bucket_lookup ( struct configuration_entry_structure *entries, char *file_name ) {

    // Prepare variables for searching

    struct configuration_entry_structure *buffer = NULL, *entry = entries;

    // Get entry by current file name

    while ( entry != NULL ) {

        // Compare file name with pattern entry

        if ( strncmp ( entry->pattern, file_name, strlen ( entry->pattern ) ) == 0 ) {

            // Entry found

            buffer = entry;
            break;
        }

        // Move to next entry

        entry = entry->next;
    }

    // Return found entry

    return buffer;
}

int bucket_monitor ( struct configuration_structure configuration ) {

    // Validate configuration structure

    if ( configuration_validate ( &configuration ) != CONFIGURATION_CODE_SUCCESS ) {

        // Configuration structure is not valid

        printf ( "Configuration structure is not valid\n" );
        return BUCKET_CODE_ERROR_CONFIGURATION;
    }

    // Open bucket

    DIR *bucket_descriptor = opendir ( configuration.bucket );
    if ( bucket_descriptor == NULL ) return bucket_error ( "Bucket opening" );

    // Monitor bucket

    struct dirent *bucket_file;

    while ( ( bucket_file = readdir ( bucket_descriptor ) ) != NULL ) {

        // Filter on regular files

        if ( bucket_file->d_type == DT_REG ) {

            // Lookup entry

            struct configuration_entry_structure *entry = bucket_lookup ( configuration.entries, bucket_file->d_name );
            if ( entry == NULL ) return bucket_error ( "No compatible entry found" );

            // Move file to entry bucket

            if ( bucket_move ( configuration.bucket, entry->bucket, bucket_file->d_name ) != BUCKET_CODE_SUCCESS ) return bucket_error ( "File moving" );
        }
    }

    // Close bucket

    if ( closedir ( bucket_descriptor ) != 0 ) return bucket_error ( "Bucket closing" );

    // Return status code

    return BUCKET_CODE_SUCCESS;
}

int bucket_move ( char *bucket_monitor, char *bucket_entry, char *file_name ) {

    // Check inputs

    if ( bucket_entry == NULL ) return bucket_error ( "Entry bucket not valid" );
    if ( bucket_monitor == NULL ) return bucket_error ( "Monitor bucket not valid" );
    if ( file_name == NULL ) return bucket_error ( "File name not valid" );

    // Prepare paths

    char *path_destination = calloc ( strlen ( bucket_entry ) + strlen ( file_name ), sizeof ( char ) );
    char *path_source = calloc ( strlen ( bucket_monitor ) + strlen ( file_name ), sizeof ( char ) );

    if ( path_destination == NULL || path_source == NULL ) return bucket_error ( "Memory allocation" );

    strcat ( path_destination, bucket_entry );
    strcat ( path_destination, file_name );

    strcat ( path_source, bucket_monitor );
    strcat ( path_source, file_name );

    // Move file to entry bucket

    int status = rename ( path_source, path_destination );

    // Return status code

    return status;
}
