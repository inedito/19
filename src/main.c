/*

 * main.c
 * Prepare environment and execute application.
 *
 * inedito

 */

// Headers

#include <stdio.h>
#include <unistd.h>

#include "header/bucket.h"
#include "header/configuration.h"

// Function

int main ( int argc, char **argv ) {

    // Manage input arguments

    char *file_name;
    int option;

    while ( ( option = getopt ( argc, argv, "f:" ) ) != -1 )
        switch ( option ) {

            case 'f':

                // Store file name

                file_name = optarg;
                break;

            default:

                break;
        }

    // Check stored argument

    if ( file_name == NULL ) {

        // Print argument syntax

        printf ( "usage: 19 -f[file]\n" );
        return 1;
    }

    // Read file

    char *file_content;
    int status;

    status = configuration_read ( file_name, &file_content );
    if ( status != 0 ) return status;

    // Parse and validate configuration

    struct configuration_structure configuration;

    status = configuration_parse ( file_content, &configuration );
    if ( status != 0 ) return status;

    status = configuration_validate ( &configuration );
    if ( status != 0 ) return status;

    // Monitor bucket

    while ( 1 )
        if ( ( status = bucket_monitor ( configuration ) ) != 0 ) break;

    // Return status code

    return status;
}
