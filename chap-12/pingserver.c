#include "lib/common.h"
#include "message_object.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        error(1, 0, "usage: tcpserver <sleepingtime>");
    }

    int sleepingtime = atoi(argv[1]);

    int listenfd;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    

    // int listenfd, connfd;
    // socklen_t clilen;
    // struct sockaddr_in cliaddr, servaddr;

    // listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // bzero(&servaddr, sizeof(servaddr));
    // servaddr.sin_family = AF_INET;
    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servaddr.sin_port = htons(12400);

    // bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    // // listen 的 backlog 为 1024
    // listen(listenfd, 1024);

    // for (;;) {
    //     clilen = sizeof(cliaddr);
    //     connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
    //     read_data(connfd);
    //     fprintf(stdout, "read finish\n");
    //     close(connfd);
    // }

    return 0;
}