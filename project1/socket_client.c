#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define MASSAGE_SIZE 102400

void send_data(int sockfd) {
    char *query;
    query = malloc(MASSAGE_SIZE + 1);
    for (int i = 0; i < MASSAGE_SIZE; ++i) {
        query[i] = 'a';
    }
    query[MASSAGE_SIZE] = '\0';

    const char *cp;
    cp = query;
    size_t remaining = strlen(query);

    while (remaining) {
        int n_written = send(sockfd, cp, remaining, 0);
        fprintf(stdout, "send into buffer %ld \n", n_written);
        if (n_written < 0) {
            error(1, errno, "send failed");
            return;
        }
        remaining -= n_written;
        cp += n_written;
    }
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12400);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    int connect_rt = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (connect_rt < 0) {
        error(1, errno, "connect failed");
    }
    send_data(sockfd);
    exit(0);
}