#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include "utils.h"
#include "log_utils.h"

#define BUFFER_SIZE 1024
#define EPOLL_SIZE 50

void start_server(int port) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    int str_len, i;
    char read_buffer[BUFFER_SIZE]; // 独立的读缓冲区
    char write_buffer[BUFFER_SIZE * 2]; // 独立的写缓冲区，足够容纳额外的回复消息

    struct epoll_event *ep_events;
    struct epoll_event event;
    int epfd, event_cnt;

    // 创建socket
    server_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket() error");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    // 设置socket选项，避免端口占用错误
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(int));

    // 绑定socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind() error");
        close(server_fd);
        exit(1);
    }

    // 监听socket
    if (listen(server_fd, 5) == -1) {
        perror("listen() error");
        close(server_fd);
        exit(1);
    }

    // 创建epoll对象
    epfd = epoll_create(EPOLL_SIZE);
    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);

    setnonblockingmode(server_fd);
    event.events = EPOLLIN;
    event.data.fd = server_fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &event);

    log_message("Server started");

    while (1) {
        // epoll等待
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if (event_cnt == -1) {
            perror("epoll_wait() error");
            continue; // 不退出程序，而是继续下一个循环
        }

        for (i = 0; i < event_cnt; i++) {
            if (ep_events[i].data.fd == server_fd) {
                // 接受连接
                addr_size = sizeof(client_addr);
                client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);
                if (client_fd == -1) {
                    perror("accept() error");
                    continue;
                }
                setnonblockingmode(client_fd);
                event.events = EPOLLIN | EPOLLET;
                event.data.fd = client_fd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &event);

                char log_msg[BUFFER_SIZE];
                snprintf(log_msg, sizeof(log_msg), "Connected client: %d", client_fd);
                log_message(log_msg);
            } else {
                // 处理数据接收
                str_len = read(ep_events[i].data.fd, read_buffer, BUFFER_SIZE - 1);
                if (str_len <= 0) {  // 如果读取错误或连接关闭
                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd);

                    char log_msg[BUFFER_SIZE];
                    snprintf(log_msg, sizeof(log_msg), "Closed client: %d", ep_events[i].data.fd);
                    log_message(log_msg);
                } else {
                    read_buffer[str_len] = 0; // 确保字符串正确终结
                    snprintf(write_buffer, sizeof(write_buffer), "你好，这里是望兮的回环测试服务器，你发送的消息是：\n%s", read_buffer);
                    write(ep_events[i].data.fd, write_buffer, strlen(write_buffer));

                    char log_msg[BUFFER_SIZE * 2];
                    snprintf(log_msg, sizeof(log_msg), "Received message from client %d: %s", ep_events[i].data.fd, read_buffer);
                    log_message(log_msg);
                }
            }
        }
    }

    // 清理和关闭操作
    close(server_fd);
    close(epfd);
    free(ep_events);
    log_message("Server stopped");
}

