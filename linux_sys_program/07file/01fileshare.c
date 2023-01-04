#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>

#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>



// 宏定义错误退出

// 更专业一点
#define ERR_EXIT(m) \
        do \
        {  \
            perror(m); \
            exit(EXIT_FAILURE); \
        }while(0)



int main(int argc, char *argv[]) {
    int fd1;
    int fd2;

    char buf1[1024] = {0};
    char buf2[1024] = {0};
    fd1 = open("test.txt", O_RDONLY);
    if (fd1 == -1) {
        ERR_EXIT("open error");
    }
    read(fd1, buf1, 5);
    printf("fd1=%d, buf1=%s\n", fd1,buf1);

    fd2 = open("test.txt", O_RDWR);         // 每个打开文件表都有自己的偏移量
    if (fd2 == -1) {
        ERR_EXIT("open error");
    }
    read(fd2, buf2, 5);
    printf("fd2=%d, buf2=%s\n", fd2, buf2);

    write(fd2, "AAAAA", 5);

    memset(buf1, 0, sizeof(buf1));          // 追加了 AAAAA 5个字符
    read(fd1, buf1, 6);                     // 再次读取, 从A开始读取
    printf("buf1=%s\n", buf1);

    close(fd1);
    close(fd2);
    return 0;
}

