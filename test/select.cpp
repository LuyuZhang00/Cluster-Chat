#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // ... bind, listen 等操作 ...

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);

    while (true) {
        fd_set tempfds = readfds;
        int ret = select(sockfd + 1, &tempfds, NULL, NULL, NULL);
        if (ret == -1) {
            perror("select");
            break;
        }
        if (FD_ISSET(sockfd, &tempfds)) {
            // accept 新的连接或处理数据 ...
        }
    }
    close(sockfd);
    return 0;
}
