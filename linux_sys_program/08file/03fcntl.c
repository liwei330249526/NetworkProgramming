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
// 错误吗
// 返回
#define ERR_EXIT(m) \
        do \
        {  \
            perror(m); \                    
            exit(EXIT_FAILURE); \
        }while(0)



int main(int argc, char *argv[]) {
    int fd;
    fd = open("test2.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd == -1) {
        ERR_EXIT("open error");
    }

    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;         // 排它锁
    lock.l_whence = SEEK_SET;       // 从文件头
    lock.l_start = 0;               // 偏移0
    lock.l_len = 0;                 // 锁整个文件

    //if(fcntl(fd, F_SETLKW, &lock) == 0) {   // F_SETLKW 如果别的进程获取了锁, 则我阻塞
    if(fcntl(fd, F_SETLK, &lock) == 0) {        // 对文件加锁
        printf("lock success\n");
        printf("press any key to unlock\n");

        getchar();                              // 读取任意键

        lock.l_type = F_UNLCK;
        if(fcntl(fd, F_SETLK, &lock) == 0) {    // 解锁
            printf("unlock success\n");
        } else {
            ERR_EXIT("unlcock error");          // 解锁失败
        }


    } else {
        ERR_EXIT("lock error");                 // 加锁失败
    }
    return 0;
}

