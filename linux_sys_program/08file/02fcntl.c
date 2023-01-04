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
    char buf[1024] = {0};
    int ret;

    int flags;

    flags = fcntl(0, F_GETFL, 0);
    if (flags == -1) {
        ERR_EXIT("fcntl get error");
    }
    ret = fcntl(0, F_SETFL, flags | O_NONBLOCK);        // 不更改原来的状态的设置新状态
    if (ret == -1) {
        ERR_EXIT("fctl set error");
    }


    flags = fcntl(0, F_GETFL, 0);
    if (flags == -1) {
        ERR_EXIT("fcntl get error");
    }
    ret = fcntl(0, F_SETFL, flags & ~O_NONBLOCK);        // 清除装填
    if (ret == -1) {
        ERR_EXIT("fctl set error");
    }

    ret = read(0, buf, 1024);        // 从标准输入读取, 阻塞读取
    if (ret == -1) {
        ERR_EXIT("read error");
    }

    printf("buf=%s\n", buf);

    return 0;
}

