#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    int ret;
    ret = close(10);
    if (ret == -1) {
        perror("close error");
    }

    if (ret == -1) {
        fprintf(stderr, "close error with msg1:%s\n", strerror(errno));         // 将字符串给到stderrr
        printf("close error with msg2: %s\n", strerror(errno));                 // 直接打印字符串  ,  errno 是错误码, 全局变量, 在 #include <errno.h> 声明
    }
    printf("EINTR desc = %s\n", strerror(EINTR));                               // 打印错误码 EINTR
    return 0;
}

