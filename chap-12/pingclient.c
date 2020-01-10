#include "lib/common.h"
#include "message_object.h"

#define MAXLINE               4096
#define KEEP_ALIVE_TIME       10
#define KEEP_ALIVE_INTERVAL   3
#define KEEP_ALIVE_PROBETIMES 3

int main(int argc, char **argv) {
    if (argc != 2) {
        error(1, 0, "usage: tcpclient <IPaddress>");
    }
    
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12402);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    int connect_rt = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (connect_rt < 0) {
        error(1, errno, "connect failed");
    }
    
    char recv_line[MAXLINE + 1];
    int n;

    fd_set readmask;
    fd_set allreads;

    struct timeval tv;
    int heartbeats = 0;

    tv.tv_sec = KEEP_ALIVE_TIME;
    tv.tv_usec = 0;

    messageObject messageObj;

    FD_ZERO(&allreads);
    FD_SET(sockfd, &allreads);
    for (;;) {
        readmask = allreads;
        int rc = select(sockfd+1, &readmask, NULL, NULL, &tv);
        if (rc < 0) {
            error(1, errno, "select failed");
        }
        if (rc == 0) {
            if (++heartbeats > KEEP_ALIVE_PROBETIMES) {
                error(1, 0, "connection dead\n");
            }
            printf("sending heartbeat #%d\n", heartbeats);
            messageObj.type = htonl(MSG_PING);
            rc = send(sockfd, (char *)&messageObj, sizeof(messageObj), 0);
            if (rc < 0) {
                error(1, errno, "send failed");
            }
            tv.tv_sec = KEEP_ALIVE_INTERVAL;
            continue;
        }
        if (FD_ISSET(sockfd, &readmask)) {
            n = read(sockfd, recv_line, MAXLINE);
            if (n < 0) {
                error(1, errno, "read error");
            } else if (n == 0) {
                error(1, 0, "server terminated \n");
            }
            printf("received heartbeat, make heartbeats to 0 \n");
            heartbeats = 0;
            tv.tv_sec = KEEP_ALIVE_TIME;
        }
    }
}