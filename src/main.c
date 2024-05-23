#include <stdatomic.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include "cli_printer.h"
#include "db_creator.h"


#define NEW_FILE -1

int main (int argc, char* argv[]) {
    
    char *filepath = NULL;
    bool new_file = false;
    
    int cur_flag;

    while((cur_flag = getopt(argc, argv, "nf:h")) != -1) {
        switch (cur_flag) {
            case 'n':
                new_file = true;
                break;
            case 'f':
                filepath = optarg;
                break;
            case 'h':
                printf("\n");
                print_usage(argv);
                printf("\n");
                break;
            case '?':
                printf("Uknown option -%c\n", cur_flag);
                break;
            default:
                return -1; 
        }

    }


    // Check for actual File path

    if (filepath == NULL) {
        printf("Filepath is a required arguement\n");
        printf("Run: <File> -h for help options\n");
        return -1;
    }

    // Check if New File is Created
    if (new_file){
        int db_created = create_db_file(filepath);
    }


    printf("Newfile: %d\n", new_file);
    printf("filepath: %s\n", filepath);

    return 0;
}


