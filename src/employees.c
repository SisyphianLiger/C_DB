#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/_endian.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "data_members.h"
#include "error_success_val.h"
#include "employees.h"


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

    ftruncate(fd, sizeof(struct dbheader_t) + (sizeof(struct employee_t) * employee_count));
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

void list_employees(struct dbheader_t *header, struct employee_t *employees) {
    
    for (int i = 0; i < (header->count); i++) 
        printf("\nEmployee ID: %i\nName:  %s\nAddress: %s\nHours Worked:%i\n", i,employees[i].name, employees[i].address, employees[i].hours); 
}


int remove_employee_by_name(struct dbheader_t * header, struct employee_t * employees, char * name){
   
    // Double check to make sure we can remove something
    if (header -> count < 1) {
        printf("Invalid Command: No Employees in the DB\n");
        return STATUS_ERROR;
    }
    
    int index_of_employee = -1;
    int i = 1; 
    
    for (i = 0; i < (header->count); i++) {
        if (strcmp(employees[i].name, name) == 0){
            index_of_employee = i;
            break;
        }
    }
    
    if (index_of_employee < 0){
        printf("Employee: %s  Not Found in DB\n", name);
        return STATUS_ERROR;
    }

    for (int i = index_of_employee; i < (header->count - 1); i++) 
        employees[i] = employees[i+1]; 
    

    return STATUS_SUCESS;
}
