#include <stdatomic.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include "cli_printer.h"


int main (int argc, char* argv[]) {
    
    char *filepath = NULL;
    bool newfile = false;
    
    int cur_flag;

    while((cur_flag = getopt(argc, argv, "n:f:h")) != -1) {
        switch (cur_flag) {
            case 'n':
                newfile = true;
                break;
            case 'f':
                filepath = optarg;
                break;
            case 'h':
                printf("\n");
                printf("This will be help\n");
                printf("\n");
                break;
            case '?':
                printf("Uknown option -%c\n", cur_flag);
                break;
            default:
                return -1; 
        }

    }

    if (filepath == NULL) {
        printf("Filepath is a required arguement\n");
        print_usage(argv);
        return -1;
    }

    printf("Newfile: %d\n", newfile);
    printf("filepath: %s\n", filepath);

    return 0;
}


