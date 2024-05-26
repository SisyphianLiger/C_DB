#ifndef DATA_MEMBERS_H
#define DATA_MEMBERS_H

#define HEADER_MAGIC 0x4c4c4144

struct dbheader_t {
   unsigned int magic;
   unsigned short version;
   unsigned short count;
   unsigned int filesilze;
};


struct employee_t {
   char name[256];
   char address[256];
   unsigned int hours;
};

int create_db_header(int fd, struct dbheader_t **headerOut);
int validate_db_header(int fd, struct dbheader_t **headerOut);
int read_employees(int fd, struct dbheader_t **headerOut, struct employee_t **employeesOut);
int endian_verifier(struct dbheader_t *header);
#endif // !DATA_MEMBERS_H
