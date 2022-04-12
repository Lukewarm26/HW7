
#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include"socketfun.h"

int main()
{

    int sock;
    char *hostname = "lucas-MS-7C02";
    int port = 51100;

    sock = serve_socket(hostname, port);

    int clientSock;
    clientSock = accept_connection(clientSock);

    int read_size;
	char client_message[2000];
    	//Receive a message from client
	while((read_size = recv(clientSock , client_message , 2000 , 0)) > 0)
	{
		
		if(read_size < 0) break;
		puts(client_message);
		char message[1000];
		
		//printf("Enter message : ");
		//scanf("%s" , message);
		
		//Send the message back to client
		if( send(clientSock , client_message , strlen(client_message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		puts("here");
		memset(client_message, 0, sizeof(client_message));
		//puts("clear");
		//write(clientSock , client_message , strlen(client_message));
	}
	
	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
}