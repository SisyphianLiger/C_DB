#include <fcntl.h>
#include <sys/fcntl.h>
#include "db_creator.h"


int create_db_file(char *fp) {
    int fd = open(fp,O_CREAT | O_RDWR, 0644);
    return fd;
}


