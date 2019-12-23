#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <signal.h>

#define MAXLINE 4096

static int count;

static void recvfrom_int(int signo) {
    printf("\nreceived %d datagrams\n", count);
}


int main() {
    int sockfd;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(12600);

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    socklen_t client_len;
    char message[MAXLINE];
    count = 0;

    signal(SIGINT, recvfrom_int);

    struct sockaddr_in client_addr;
    client_len = sizeof(client_addr);
    for (;;) {
        int n = recvfrom(sockfd, message, MAXLINE, 0, (struct sockaddr *)&client_addr, &client_len);
        message[n] = '\0';
        printf("received %d bytes: %s\n", n, message);
        char send_line[MAXLINE];
        sprintf(send_line, "Hi, %s", message);
        sendto(sockfd, send_line, strlen(send_line), 0, (struct sockaddr *)&client_addr, client_len);
        count++;
    }

    return 0;
}