/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char* argv[]){
  int clientSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*Open a socket and set it’s properties;*/

  clientSocket = socket(PF_INET, SOCK_STREAM, 0); //  define ip, stream data, default protocol- TCP
  
  
  /*Input: IP_address, port, num_parts;*/

  serverAddr.sin_family = AF_INET;    //Address family of the server = ipv4
  
  serverAddr.sin_port = htons(atoi(argv[2])); //Set port number, using htons to use proper byte order

  serverAddr.sin_addr.s_addr = inet_addr(argv[1]); //Set IP address to localhost


 
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  //Set all bits in buff to 0

  /*Connect to server;*/
  
  addr_size = sizeof serverAddr;    // the struct contain ip and port num
  
  if (connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) == -1){
	printf("errorrrrr\n");
}

 // connct to server: client sok, pointer to add server, add size
  
  
  /*Read the message from the server into the buffer*/
  int i=0;
  while (i<atoi(argv[3])) {
    int n = recv(clientSocket, buffer, 1024, 0);  // n= num bytes read, write ti buffer, until 1024 byte each time 
    if (n == 0) break;
    i++;
    printf("%.*s", n, buffer);  //Print the received message
    }
    
    close(clientSocket);   // close socket and free mem
   
  return 0;
}
