#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024];
    int num_part= atoi(argv[3]);      // num part = 10

    /* Create socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    /* Bind socket */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(atoi(argv[2]));          // port 5005
    bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    FILE *file;
    file = fopen(argv[4], "r");
    unsigned long totalBytes = 0;

    if (file == NULL) {
        printf("Could not open file");
        return 1;
    }
	
    int i=0;
    while(i<=num_part){
        
	totalBytes += fread(buffer, sizeof(char), 1024, file);
	printf("chunk data (1024) read, total: %lu \n",totalBytes);
        i++ ;	
	/* Send message */
    	sendto(sockfd, buffer, 1024, 0, (struct sockaddr *) &servaddr, sizeof(servaddr));
    }
    printf("size byte sent: %lu\n", totalBytes);
    
    fclose(file);   // close file
    close(sockfd);   // close socket and free mem

    return 0;
}
