#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <string.h>

// 宏定义错误退出

// 更专业一点
#define ERR_EXIT(m) \
        do \
        {  \
            perror(m); \
            exit(EXIT_FAILURE); \
        }while(0)


int main(int argc, char *argv[]) {
    int fd;
    fd = open("hole.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        ERR_EXIT("open error");
    }

    write(fd, "ABCDE", 5);
    int ret = lseek(fd, 1024*1024*1024, SEEK_CUR);
    if (ret == -1) {
        ERR_EXIT("lseeek error");
    }

    write(fd, "hello", 5);
    close(fd);
    return 0;
}

