/*

 * configuration.c
 * Defines header declarations.
 *
 * inedito

 */

// Headers

#include "header/configuration.h"

// Functions

int configuration_error ( char *message ) {

    // Check message

    if ( message == NULL ) return CONFIGURATION_CODE_ERROR_NULL;

    // Write message to STDERR

    fprintf ( stderr, "ERROR: %s\n", message );

    // Return error code

    return CONFIGURATION_CODE_ERROR_GENERIC;
}

int configuration_parse ( char *content, struct configuration_structure *configuration ) {

    // Check content

    if ( content == NULL ) return configuration_error ( "Content empty" );

    // Initialize configuration structure

    configuration->bucket = NULL;
    free ( configuration->entries );

    // Loop on tokenized content

    char *token = strtok ( content, CONFIGURATION_SEPARATORS );
    struct configuration_entry_structure *last;

    while ( token != NULL ) {

        // Check bucket

        if ( configuration->bucket == NULL ) {

            // Store bucket

            token = strtok ( NULL, CONFIGURATION_SEPARATORS );
            configuration->bucket = token;
        }

        // Check entry

        else {

            // Prepare entry

            struct configuration_entry_structure *entry = calloc ( CONFIGURATION_MEMORY_SIZE_MIN, sizeof ( struct configuration_entry_structure ) );
            if ( entry == NULL ) return configuration_error ( "Memory allocation" );

            // Fill entry

            entry->name = token;
            entry->pattern = strtok ( NULL, CONFIGURATION_SEPARATORS );
            entry->bucket = strtok ( NULL, CONFIGURATION_SEPARATORS );

            entry->next = NULL;

            // Align entries list

            if ( configuration->entries == NULL ) {

                // Update entries head list

                configuration->entries = entry;
                last = configuration->entries;
            }

            else {

                // Update last entry in list

                last->next = entry;
                last = last->next;
            }
        }

        // Move to next token

        token = strtok ( NULL, CONFIGURATION_SEPARATORS );
    }

    // Release token memory

    free ( token );

    // Return status code

    return CONFIGURATION_CODE_SUCCESS;
}

int configuration_read ( char *file_name, char **file_content ) {

    // Open file

    int file_descriptor = open ( file_name, O_RDONLY );
    if ( file_descriptor == -1 ) return configuration_error ( "File opening" );

    // Prepare variable for file content

    *file_content = calloc ( CONFIGURATION_MEMORY_SIZE_MIN, sizeof ( char ) );
    if ( *file_content == NULL ) return configuration_error ( "Memory allocation" );

    while ( 1 ) {

        // Prepare buffer for file reading

        char *buffer_content = calloc ( CONFIGURATION_MEMORY_SIZE_MAX, sizeof ( char ) );
        if ( buffer_content == NULL ) return configuration_error ( "Memory allocation" );

        // Read file content

        int buffer_length = read ( file_descriptor, buffer_content, CONFIGURATION_MEMORY_SIZE_MAX - 1 );
        if ( buffer_length < 0 ) return configuration_error ( "File reading" );

        // Reallocate memory for buffer including

        *file_content = realloc ( *file_content, ( strlen ( *file_content ) + buffer_length ) * sizeof ( char ) );
		if ( *file_content == NULL ) return configuration_error ( "Memory reallocation" );

        // Contatenate buffer to content

		strcat ( *file_content, buffer_content );

        // Realease buffer memory

		free ( buffer_content );

        // Break loop at the end of file

		if ( buffer_length < CONFIGURATION_MEMORY_SIZE_MAX - 1 ) break;
	}

    // Return status code

	return CONFIGURATION_CODE_SUCCESS;
}

void configuration_representation ( struct configuration_structure *configuration ) {

    // Validate configuration structure

    if ( configuration_validate ( configuration ) != CONFIGURATION_CODE_SUCCESS ) {

        // Configuration structure is not valid

        printf ( "Configuration structure is not valid\n" );
        return;
    }

    // Print configuration bucket

    printf ( "BUCKET\n| - Directory: %s\n\n", configuration->bucket );

    // Loop on configuration entries

    struct configuration_entry_structure *entry = configuration->entries;

    printf ( "ENTRIES\n" );

    while ( entry != NULL ) {

        // Print current entry

        printf ( "+\n| - Name: %s\n| - Pattern: %s\n| - Bucket: %s\n", entry->name, entry->pattern, entry->bucket );

        // Move to next entry

        entry = entry->next;
    }

    // Return

    return;
}

int configuration_validate ( struct configuration_structure *configuration ) {

    // Check bucket

    if ( configuration->bucket == NULL ) return configuration_error ( "Bucket not valid" );

    // Check entries

    struct configuration_entry_structure *entry = configuration->entries;
    if ( entry == NULL ) return configuration_error ( "No valid entries" );

    while ( entry != NULL ) {

        // Checks entry fields

        if ( entry->bucket == NULL ) return configuration_error ( "Entry bucket not valid" );
        if ( entry->name == NULL ) return configuration_error ( "Entry name not valid" );
        if ( entry->pattern == NULL ) return configuration_error ( "Entry pattern not valid" );

        // Move to next entry

        entry = entry->next;
    }

    // Return status code

    return CONFIGURATION_CODE_SUCCESS;
}
