//
// Created by jxq on 19-7-17.
//
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using namespace std;

#define ERR_EXIT(m) \
        do  \
        {   \
            perror(m);  \
            exit(EXIT_FAILURE); \
        } while(0);

int main(int argc, char** argv) {
    // 1. 创建套接字
    int listenfd;
    if ((listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        ERR_EXIT("socket");
    }

    // 2. 分配套接字地址
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // inet_aton("127.0.0.1", &servaddr.sin_addr);

    int on = 1;
    // 确保time_wait状态下同一端口仍可使用
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on) < 0)
    {
        ERR_EXIT("setsockopt");
    }

    // 3. 绑定套接字地址
    if (bind(listenfd, (struct sockaddr*) &servaddr, sizeof servaddr) < 0) {
        ERR_EXIT("bind");
    }
    // 4. 等待连接请求状态
    if (listen(listenfd, SOMAXCONN) < 0) {
        ERR_EXIT("listen");
    }
    // 5. 允许连接
    struct sockaddr_in peeraddr;
    socklen_t peerlen = sizeof peeraddr;
    int connfd;                             // 返回值
    if ((connfd = accept(listenfd, (struct sockaddr *) &peeraddr, &peerlen)) < 0) {
        ERR_EXIT("accept");
    }

    printf("id = %s, ", inet_ntoa(peeraddr.sin_addr));
    printf("port = %d\n", ntohs(peeraddr.sin_port));

    // 6. 数据交换
    char recvbuf[1024];
    while (1)
    {
        memset(recvbuf, 0, sizeof recvbuf);
        int ret = read(connfd, recvbuf, sizeof recvbuf);
        if (ret == 0)
        {
            printf("ret = 0\n");                // 对边主动断开连接, 我这里主动读取一次connfd的话, 则ret == 0;
            break;
        } else
        {
            printf("ret != 0\n");
        }
        fputs(recvbuf, stdout);
        write(connfd, recvbuf, ret);
    }

    // 7. 断开连接
    close(connfd);
    close(listenfd);



    return 0;
}












