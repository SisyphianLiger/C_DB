#ifndef DATA_MEMBERS_H
#define DATA_MEMBERS_H

#define HEADER_MAGIC 0x4c4c4144

struct dbheader_t {
   unsigned int magic;
   unsigned short version;
   unsigned short count;
   unsigned int filesize;
};


struct employee_t {
   char name[256];
   char address[256];
   unsigned int hours;
};

int create_db_header(int fd, struct dbheader_t **headerOut);
int validate_db_header(int fd, struct dbheader_t **headerOut);
int endian_verifier(int fd, struct dbheader_t * header);
#endif // !DATA_MEMBERS_H
