#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "data_members.h"

int output_file(int, struct dbheader_t *, struct employee_t *);
int read_employees(int, struct dbheader_t *, struct employee_t **);
int add_employees(struct dbheader_t *,  struct employee_t *, char*);
void list_employees(struct dbheader_t *, struct employee_t *);
int remove_employee_by_name(struct dbheader_t *, struct employee_t *, char *);
int update_employee_hours(struct dbheader_t *, struct employee_t *, char *, char *);
#endif // !EMPLOYEES_H
