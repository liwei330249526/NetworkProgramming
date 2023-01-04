#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <string.h>

// 宏定义错误退出
#define ERR_EXIT(m) (perror(m), exit(EXIT_FAILURE))

// 更专业一点
#define ERR_EXIT2(m) \
        do \
        {  \
            perror(m); \
            exit(EXIT_FAILURE); \
        }while(0)


int main(void) {
    int fd;
    umask(0);
    fd = open("test.txt", O_RDONLY | O_CREAT, 0666);    // 如果文件不存在, 则创建文件
    if (fd == -1) {
        fprintf(stderr, "open error with errno=%d, %s\n", errno, strerror(errno));  // open error with errno=2, No such file or directory
        //exit(EXIT_FAILURE);
    }

    if (fd == -1) {
        perror("open error");
        //exit(EXIT_FAILURE);
    }

    if (fd == -1) {
        ERR_EXIT2("open error");
    }
    printf("open success\n");




    fd = open("test.txt", O_RDONLY | O_CREAT | O_EXCL, 0666);   // 如果文件存在, 则打开失败
    if (fd == -1) {
        ERR_EXIT2("open error");
    }
    printf("open success\n");

    close(fd);
    return 0;
}

