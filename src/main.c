#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "cli_printer.h"
#include "data_members.h"
#include "db_creator.h"
#include "error_success_val.h"


#define NEW_FILE -1

int main (int argc, char* argv[]) {
    
    char *filepath = NULL;
    char *addstr = NULL;
    bool new_file = false;
    int db_fd = NEW_FILE;
    
    struct dbheader_t * header = NULL;
    struct employee_t * employees = NULL;
    int cur_flag;

    while((cur_flag = getopt(argc, argv, "nf:a:h")) != -1) {
        switch (cur_flag) {
            case 'n':
                new_file = true;
                break;
            case 'f':
                filepath = optarg;
                break;
            case 'a':
                addstr = optarg;
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
        db_fd = create_db_file(filepath);
        if (db_fd == STATUS_ERROR){
            printf("Unable to create db file");
            return -1;
        }

        if (create_db_header(db_fd, &header) == STATUS_ERROR) {
            printf("Failed to create database header\n");
            return -1;
        }

    } else {
        db_fd = open_db_file(filepath);
        if (db_fd == STATUS_ERROR) {
            printf("Unable to open database");
            return -1;
        }
        if (validate_db_header(db_fd, &header) == STATUS_ERROR){
            printf("No Header found, Incorrect File Read\n");
            return -1;
        }
    }

    if (read_employees(db_fd, header, &employees) != STATUS_SUCESS){
        printf("Failed to read employees");
        return -1;
    }

    if (addstr)  {
        header->count++; 
        if (realloc(employees, header->count*(sizeof(struct employee_t))) == NULL){
            printf("Database is Full, Cannot Add more Employees");
            return -1;
        }
        printf("Hit added employees\n");
        add_employees(header, employees, addstr);

    }

    output_file(db_fd, header, employees);

    return 0;
}


