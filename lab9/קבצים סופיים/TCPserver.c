/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char* argv[]){
    int welcomeSocket, newSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    int num_part = atoi(argv[3]);
 
    /*Open a socket and set it’s properties;*/
   
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);  // define ip, stream data, default protocol- TCP

    
    /*Input: IP_address, port, num_parts;*/

    serverAddr.sin_family = AF_INET;   //Address family of the server = ipv4
   
    serverAddr.sin_port = htons(atoi(argv[2]));   //Set port number, using htons to use proper byte order
   
  
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);  //Set IP address to localhost 
    

    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits in buff to 0

    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));  //Bind the address struct to the socket

  
    /*Wait for a connection:*/

    if(listen(welcomeSocket,5)==0)    // have a queue of 5 for listen
        printf("Listening\n");
    else
        printf("Error\n");

    /* Accept call creates a new socket for the incoming connection*/

  
    addr_size = sizeof serverStorage;

    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);  // accept return a new FD to new soket.

    /*read from "alice" and send chunk of 1024 bytes over the socket*/
   
    FILE *file;
    unsigned long totalBytes = 0;

  
    file = fopen(argv[4], "r");

    if (file == NULL) {
        printf("Could not open file");
        return 1;
    }
	
    int i=0;
   printf("%d", num_part);
    while(i<=num_part){
        
	totalBytes += fread(buffer, sizeof(char), 1024, file);
	printf("chunk data (1024) read, total: %lu \n",totalBytes);
        i++ ;	
	send(newSocket,buffer,1024,0);               // send the buffer to client
    }
    printf("size byte sent: %lu\n", totalBytes);
    
    fclose(file);   // close file
    close(newSocket);   // close socket and free mem

    return 0;
}
