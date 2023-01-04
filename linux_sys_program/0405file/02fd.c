#include <stdlib.h>
#include <stdio.h>

int main(void) {
    printf("fileno(stdin)=%d\n", fileno(stdin));        // fileno 将文件指针转换为文件描述符
    return 0;
}

