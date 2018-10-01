/*

 * bucket.c
 * Defines header declarations.
 *
 * inedito

 */

// Headers

#include "header/bucket.h"

// Functions

int bucket_entry_monitor ( struct bucket_structure *entry ) {

    // Check input

    if ( entry == NULL ) return bucket_error ( "Entry not valid" );

    // Open entry bucket

    DIR *bucket_descriptor = opendir ( entry->bucket );
    if ( bucket_descriptor == NULL ) return bucket_error ( "Bucket opening" );

    // Initialize bucket structure

    struct bucket_file_structure *last;
    free ( entry->files );

    // Monitor entry bucket

    struct dirent *bucket_file;

    while ( ( bucket_file = readdir ( bucket_descriptor ) ) != NULL ) {

        // Filter on regular files

        if ( bucket_file->d_type == DT_REG ) {

            // Prepare file

            struct bucket_file_structure *file = calloc ( BUCKET_MEMORY_SIZE_MIN, sizeof ( struct bucket_file_structure ) );
            if ( file == NULL ) return bucket_error ( "Memory allocation" );

            file->name = calloc ( strlen ( entry->bucket ) + strlen ( bucket_file->d_name ), sizeof ( char ) );
            if ( file->name == NULL ) return bucket_error ( "Memory allocation" );

            // Fill file

            strcat ( file->name, entry->bucket );
            strcat ( file->name, bucket_file->d_name );

            file->next = NULL;

            // Align files list

            if ( entry->files == NULL ) {

                // Update files head list

                entry->files = file;
                last = entry->files;
            }

            else {

                // Update last file in list

                last->next = file;
                last = last->next;
            }
        }
    }

    // Close entry bucket

    if ( closedir ( bucket_descriptor ) != 0 ) return bucket_error ( "Bucket closing" );

    // Return status code

    return BUCKET_CODE_SUCCESS;
}

void bucket_entry_representation ( struct bucket_structure entry ) {

    // Print entry bucket information

    printf ( "ENTRY BUCKET\n| - Name: %s\n| - Bucket %s\n| - Pattern: %s\n\n", entry.name, entry.pattern, entry.bucket );

    // Loop on entry bucket files

    struct bucket_file_structure *file = entry.files;

    printf ( "ENTRY BUCKET FILES\n" );

    while ( file != NULL ) {

        // Print current file

        printf ( "| - Name: %s\n", file->name );

        // Move to next file

        file = file->next;
    }

    // Return

    return;
}

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
