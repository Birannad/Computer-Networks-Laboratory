#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char message[] = "Hello, World!";
    int msg_len = strlen(message);

    /* Create socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    /* Bind socket */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(5005);
    bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    /* Send message */
    sendto(sockfd, message, msg_len, 0, (struct sockaddr *) &servaddr, sizeof(servaddr));

    /* Close socket */
    close(sockfd);

    return 0;
}
