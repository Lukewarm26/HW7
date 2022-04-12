

#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <stdlib.h>
#include"socketfun.h"


int main(int argc, char **argv) {

	if(argc != 2)
	{
		puts("Error: must specify a hostname");
		return 1;
	}

    int sock;
    char *hostname = argv[1];
    int port = 51100;
    char message[4096] , server_reply[4096];
	int readSize;
    sock = request_connection(hostname, port);

    while(1)
	{
		printf("Enter message : ");
		if(fgets(message, 4096, stdin) == NULL)
        {
            puts("\nexiting");
            fflush(stdout);
            close(sock);
            exit(EXIT_SUCCESS);
        }
		
		//Send some data
		if(send(sock , message , strlen(message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		memset(message, 0, sizeof(message));
		//puts("awaiting response...");
		//Receive a reply from the server
		if((readSize = recv(sock , server_reply , 4096 , 0)) <= 0)
		{
            if(readSize == 0)
            {
                puts("Server disconnected");
                fflush(stdout);
				close(sock);
                exit(EXIT_SUCCESS);
            }
            else if(readSize == -1)
            {
                perror("recv failed");
                exit(EXIT_FAILURE);
            }
		}
		
		//puts("Server reply :");
		puts(server_reply);
		memset(server_reply, 0, sizeof(server_reply));
	}
	
	close(sock);
	return 0;
}