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
    int fd;
    fd = open("test.txt", O_WRONLY);
    if (fd == -1) {
        ERR_EXIT("open error");
    }

    close(1);       // 关闭标准输出
    //int newfd = dup(fd);        // 复制 fd 文件描述符, 意味着,  1-fd, 返回新的描述符, 和fd指向同一个; 返回的新的描述符刚好是1
    //printf("newfd=%d\n", newfd);    // newfd = 1, printf 打印到了文件 test2.txt
    
    if (fcntl(fd, F_DUPFD, 0) == -1) {          // 从0开始搜索, 搜索到1, 标准输出
        ERR_EXIT("fcntl error");
    }
    //fcntl();

    printf("hello\n");              // 打印到了test2.txt文件
    return 0;
}

