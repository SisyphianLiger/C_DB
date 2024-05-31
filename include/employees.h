#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "data_members.h"

int output_file(int fd, struct dbheader_t *t, struct employee_t * employees);
int read_employees(int fd, struct dbheader_t * headerOut, struct employee_t **employeesOut);
int add_employees(struct dbheader_t * header,  struct employee_t *employeeAdd, char* addstr);
void list_employees(struct dbheader_t * header, struct employee_t * employees);
int remove_employee_by_name(struct dbheader_t * header, struct employee_t * employees, char * name);
#endif // !EMPLOYEES_H
