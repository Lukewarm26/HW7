
#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <stdlib.h>
#include"socketfun.h"

int main()
{

    int sock;
    char *hostname = "hive2.cs.uwyo.edu";
    int port = 51100;

    sock = serve_socket(hostname, port);

    int clientSock;
    clientSock = accept_connection(sock);

    int readSize;
	char clientMessage[4096], message[4096];
    	//Receive a message from client
        
    while(1)
    {
        //puts("awaitning response...");
        memset(clientMessage, 0, sizeof(clientMessage));
        readSize = recv(clientSock , clientMessage , 4096 , 0);

        if(readSize == 0)
        {
            puts("Client disconnected");
            fflush(stdout);
            close(clientSock);
            close(sock);
            exit(EXIT_SUCCESS);
        }
        else if(readSize == -1)
        {
            perror("recv failed");
            exit(EXIT_FAILURE);
        }
		
        puts(clientMessage);

        memset(message, 0, sizeof(message));
        printf("Enter message : ");
        if(fgets(message, 4096, stdin) == NULL)
        {
            puts("\nexiting");
            fflush(stdout);
            close(clientSock);
            close(sock);
            exit(EXIT_SUCCESS);
        }

        if(send(clientSock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            close(clientSock);
            close(sock);
            exit(EXIT_FAILURE);
        }


            
        if(readSize < 0) break;
    }

    close(clientSock);
    close(sock);

    exit(EXIT_SUCCESS);
}