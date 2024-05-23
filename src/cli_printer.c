#include <stdio.h>
#include "cli_printer.h"

void print_usage(char *argv[]) {
    printf("\n");
    printf("Usage: %s -n -f <database file>\n", argv[0]);
    printf("\n");
    printf("\t -n   -   create new database file\n");
    printf("\t -f   -   (required) patth to database file\n");
    printf("\n");
}
