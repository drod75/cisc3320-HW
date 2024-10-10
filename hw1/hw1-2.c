#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    char* filepath;
    int returnval;

    // Check for command line input
    if (argc != 2) {
        printf("Usage: program <filename>\n");
        return 1; // Return an error code for incorrect usage
    }

    filepath = argv[1];

    // Check whether the calling process can access the file
    returnval = access(filepath, F_OK);
    if (returnval == 0) {
        printf("\n%s exists\n", filepath);
        
        // Check for read permissions
        returnval = access(filepath, R_OK);
        if (returnval == 0) {
            printf("%s has read permission\n", filepath);
        } else {
            if (errno == EACCES) {
                printf("%s does not have read permission\n", filepath);
            }
        }

        // Check for write permissions
        returnval = access(filepath, W_OK);
        if (returnval == 0) {
            printf("%s has write permission\n", filepath);
        } else {
            if (errno == EACCES) {
                printf("%s does not have write permission\n", filepath);
            }
        }
    } else {
        if (errno == ENOENT) {
            printf("\n%s does not exist\n", filepath);
        } else if (errno == EACCES) {
            printf("\nCannot access file %s\n", filepath);
        }
        return 0;
    }

    return 0;
}
