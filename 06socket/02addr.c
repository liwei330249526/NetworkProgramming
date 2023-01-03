#include <stdio.h>
#include <arpa/inet.h>

int main(void) {
    unsigned long_addr = inet_addr("192.168.0.100");      // 点分10进制字符串转换为整数
    printf("long_addr=%u\n", ntohl(long_addr));


    in_addr_t inaddr = inet_addr("192.168.0.100");   // in_addr_t 一般为32位的unsigned int.
    printf("long_addr=%u\n", ntohl(inaddr));


    struct in_addr ipaddr;                          // ip地址结构
    ipaddr.s_addr = long_addr;                      // 设置整数
    printf("in_addr--%s\n", inet_ntoa(ipaddr));    // 将ip地址的结构转换为点分十进制字符串


    struct in_addr ipaddr2;                         // ip地址结构
    ipaddr2.s_addr = inaddr;                        // 设置 in_addr_t
    printf("in_addr--%s\n", inet_ntoa(ipaddr2)); 


    struct in_addr ipaddrout;                       // ip 地址结构
    char *cp = "192.168.0.100";
    inet_aton(cp, &ipaddrout);                      // 点分10进制字符串, 输出转换为ip地址结构
    printf("%u\n",ntohl(ipaddrout.s_addr));         // printf 的时候要转换为本机字节序

    return 0;
}
