#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>

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
    DIR *dir = opendir(".");
    struct dirent *de;
    while((de = readdir(dir)) != NULL) {
        if (strncmp(de->d_name, ".", 1) == 0) {
            continue;
        }
        printf("%s\n", de->d_name);
    }
    closedir(dir);
    //return 0;
    exit(EXIT_SUCCESS);
}

