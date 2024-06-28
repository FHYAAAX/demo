#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12000
#define BUFFER_SIZE 1024

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[BUFFER_SIZE] = {0};

    // 创建套接字
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("套接字创建失败");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 将IPv4地址从点分十进制转换为二进制格式
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        perror("无效的地址/地址不支持");
        return -1;
    }

    // 连接服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("连接失败");
        return -1;
    }
    // 向服务器发送消息
    send(sock, hello, strlen(hello), 0);
    printf("已向服务器发送消息: %s\n", hello);
    // 从服务器接收回复
    valread = read(sock, buffer, BUFFER_SIZE);
    printf("来自服务器的回复: %s\n",buffer );
    return 0;
}

