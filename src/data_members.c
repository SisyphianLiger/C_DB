#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/_endian.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
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
    header->filesize = sizeof(struct dbheader_t);    

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


    if (endian_verifier(fd, header) == STATUS_ERROR)
        return -1;    
    
    *headerOut = header;
    return fd;
}


int endian_verifier(int fd, struct dbheader_t *header) {
    // Checking for little or big endianess in networks
    if ((header->version = ntohs(header->version)) != 1) {
        printf("Header Version is incorrect: Version inserted is: %i\n", header->version);
        free(header);
        return STATUS_ERROR;
    }

    if ((header->magic = ntohl(header->magic)) != HEADER_MAGIC) {
        printf("Improper Header Magic");
        free(header);
        return STATUS_ERROR;
    }

    struct stat db_stat = {0};
    fstat(fd, &db_stat);

    if ((header-> filesize = ntohl(header->filesize) != db_stat.st_size)) {
        printf("Filesize does not match: Corrupted File\n");
        free(header);
        return STATUS_ERROR;
    }
    return STATUS_SUCESS;
}


int output_file(int fd, struct dbheader_t *db_header, struct employee_t * employees){
    
    if (fd < 0) {
        printf("Bad File Number from User \n");
        return STATUS_ERROR;
    }

    int employee_count = db_header->count;

    db_header -> magic = htonl(db_header->magic);
    db_header -> filesize = htonl(sizeof(struct dbheader_t) + (sizeof(struct employee_t) * employee_count));
    db_header -> count = htons(db_header->count);
    db_header -> version = htons(db_header->version);
 
    // Points to spot in memeory to write
    lseek(fd, 0, SEEK_SET);
    write(fd, db_header, sizeof(struct dbheader_t));

    for (int i = 0; i < employee_count; i++) {
        employees[i].hours = htonl(employees[i].hours);
        write(fd, &employees[i], sizeof(struct employee_t));
    }

    return STATUS_SUCESS;
}


int read_employees(int fd, struct dbheader_t * headerOut, struct employee_t **employeesOut) {
     
    if (fd < 0) {
        printf("Bad File Number from User \n");
        return STATUS_ERROR;
    }

    int count = headerOut -> count; 

    struct employee_t * employes = calloc(count, sizeof(struct employee_t)); 

    if (employes == NULL) {
        printf("Malloc Failed \n");
        return STATUS_ERROR;
    }
    
    read(fd, employes, count*sizeof(struct employee_t));

    for (int i = 0; i < count; i++) 
        employes[i].hours = ntohl(employes[i].hours);
    
    *employeesOut = employes;

    return STATUS_SUCESS;
}


int add_employees(struct dbheader_t * header, struct employee_t *employeeAdd, char * addstr) {

    char * name  = strtok(addstr, ",");
    char * addr  = strtok(NULL, ",");
    char * hours = strtok(NULL, ",");

    strncpy(employeeAdd[header->count-1].name, name, sizeof(employeeAdd[header->count-1].name));
    strncpy(employeeAdd[header->count-1].address, addr, sizeof((employeeAdd[header->count-1].address)));
    employeeAdd[header-> count-1].hours = atoi(hours); 
    

    return STATUS_SUCESS;
}
