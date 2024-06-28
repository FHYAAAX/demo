#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12000
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *hello = "Hello from server";

    // 创建套接字文件描述符
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket 创建失败");
        exit(EXIT_FAILURE);
    }

    // 设置套接字选项，允许地址重用
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt 设置失败");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 将套接字绑定到指定端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind 绑定失败");
        exit(EXIT_FAILURE);
    }
    // 开始监听传入连接
    if (listen(server_fd, 3) < 0) {
        perror("listen 监听失败");
        exit(EXIT_FAILURE);
    }
    // 接受客户端连接
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept 接受连接失败");
        exit(EXIT_FAILURE);
    }
    // 从客户端读取数据
    valread = read(new_socket, buffer, BUFFER_SIZE);
    printf("接收到来自客户端的消息: %s\n", buffer);
    // 向客户端发送消息
    send(new_socket, hello, strlen(hello), 0);
    printf("已向客户端发送消息: %s\n", hello);
    return 0;
}

