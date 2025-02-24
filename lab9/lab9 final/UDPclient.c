#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024];
    int n;
    socklen_t len;

    /* Create socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    /* Bind socket */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.5.1"); //INADDR_ANY
    servaddr.sin_port = htons(54445);
    

    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = inet_addr("192.5.2.1"); //INADDR_ANY
    cliaddr.sin_port = htons(54445);
    bind(sockfd, (struct sockaddr *) &cliaddr, sizeof(servaddr));
    

    /* Wait for data */
    len = sizeof(cliaddr);
    n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &servaddr, &len);
    buffer[n] = '\0';
    printf("Received: %s\n", buffer);

    /* Close socket */
    close(sockfd);

    return 0;
}
