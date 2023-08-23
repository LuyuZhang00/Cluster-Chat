#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // ... bind, listen 等操作 ...

    int epollfd = epoll_create1(0);
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev);

    struct epoll_event events[10];
    while (true) {
        int nfds = epoll_wait(epollfd, events, 10, -1);
        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == sockfd) {
                // accept 新的连接或处理数据 ...
            }
        }
    }
    close(sockfd);
    close(epollfd);
    return 0;
}
