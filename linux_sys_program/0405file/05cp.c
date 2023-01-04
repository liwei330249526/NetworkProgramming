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
    int infd;
    int outfd;

    if (argc != 3) {
        fprintf(stderr, "Usage %s src dest\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    infd = open(argv[1], O_RDONLY);
    if(infd == -1) {
        ERR_EXIT("open src error");
    }

    outfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);      // 读写, 创建, 清空
    if(outfd == -1) {
        ERR_EXIT("open dest errro");
    }

    char buf[1024];
    int nread;
    while((nread = read(infd, buf, 1024)) > 0) {                // 遍历读取 infd, 写入outfd
        write(outfd, buf, nread);
    }
    close(infd);
    close(outfd);
    return 0;
}

