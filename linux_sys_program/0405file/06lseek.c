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
    fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        ERR_EXIT("open_error");
    }

    char buf[1024] = {0};
    int ret = read(fd, buf, 5);
    if (ret == -1) {
        ERR_EXIT("read error");
    }
    printf("buf=%s\n", buf);


    ret = lseek(fd, 0, SEEK_CUR); // 从当前位置偏移0; 偏移位置
    if (ret == -1) {
        ERR_EXIT("lseek error");
    }
    printf("cur offset = %d\n", ret);

 
    return 0;
}

