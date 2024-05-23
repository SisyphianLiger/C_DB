#include <stdio.h>
#include "cli_printer.h"

void print_usage(char *argv[]) {
    printf("\n");
    printf("\tUsage: %s -n -f <database file>\n", argv[0]);
    printf("\n");
    printf("\t -n   -   create new database file\n");
    printf("\t -f   -   (required) path to database file\n");
    printf("\t -h   -   Help Options - Listed\n");
    printf("\n");
}
