#include <stdio.h>
#include <stdlib.h>
#include <sys/_endian.h>
#include <time.h>
#include <unistd.h>
#include "data_members.h"
#include "error_success_val.h"



int create_db_header(int fd, struct dbheader_t **headerOut) {

    struct dbheader_t * header = calloc(1, sizeof(struct dbheader_t));
    if (header == NULL) {
        printf("Malloc failed to creadte db header\n");
        return STATUS_ERROR;
    }
    // Initialize with base values
    header->version = 0x1;
    header->count = 0;
    header->magic = HEADER_MAGIC;
    header->filesilze = sizeof(struct dbheader_t);    

    *headerOut = header;
    return STATUS_SUCESS;
}

int validate_db_header(int fd, struct dbheader_t **headerOut){
    if (fd < 0) {
        printf("Bad FD from User\n");
        return STATUS_ERROR;
    }

    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    
    if (header == NULL) {
        printf("Calloc Filed to create db header\n");
        return STATUS_ERROR;
    }

    if (read(fd, header, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t)){
        perror("read");
        free(header);
        return STATUS_ERROR;
    }


    if (endian_verifier(header) == STATUS_ERROR){
        return -1;
    }
}


int read_employees(int fd, struct dbheader_t **headerOut, struct employee_t **employeesOut) {

}



int endian_verifier(struct dbheader_t *header) {
    // Gonna Rewrite for Error Handling
    // Checking for little or big endianess
    if ((header->version = ntohs(header->version)) != 1) {
        printf("Header Version is incorrect: Version inserted is: %i\n", header->version);
        free(header);
        return STATUS_ERROR;
    }
    if ((header->count = ntohs(header->count)) != 1) {
        printf("Header Version is incorrect: Version inserted is: %i\n", header->version);
        free(header);
        return STATUS_ERROR;
    }
    if ((header->magic = ntohl(header->magic)) != 1) {
        printf("Header Version is incorrect: Version inserted is: %i\n", header->version);
        free(header);
        return STATUS_ERROR;
    }
    if ((header->filesilze = ntohl(header->filesilze)) != 1) {
        printf("Header Version is incorrect: Version inserted is: %i\n", header->version);
        free(header);
        return STATUS_ERROR;
    }
}
