#include <sys/poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // ... bind, listen 等操作 ...

    struct pollfd fds[1];
    fds[0].fd = sockfd;
    fds[0].events = POLLIN;

    while (true) {
        int ret = poll(fds, 1, -1);
        if (ret == -1) {
            perror("poll");
            break;
        }
        if (fds[0].revents & POLLIN) {
            // accept 新的连接或处理数据 ...
        }
    }
    close(sockfd);
    return 0;
}
