#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include "db_creator.h"
#include "error_success_val.h"



int create_db_file(char *fp) {

    int fd = open(fp, O_RDONLY);
    if( fd != -1) {
        close(fd);
        printf("File already exists\n");
        return STATUS_ERROR;
    };

    fd = open(fp,O_CREAT | O_RDWR, 0644);

    if (fd == -1) {
        perror("open");
        return STATUS_ERROR;
    }
    return fd;
}



int open_db_file( char *fp) {
   
    int fd = open(fp,O_CREAT | O_RDWR, 0644);

    if (fd == -1) {
        perror("open");
        return STATUS_ERROR;
    }
    return fd;

}


