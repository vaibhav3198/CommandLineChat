#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define PORT 7891
#define MAX 1024

int main()
{
	printf("\nThis is server:\n");
	int _socket;
	char buffer[MAX];
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	socklen_t addressSize = sizeof(serverAddress);

	socket_ = socket(PF_INET,SOCK_DGRAM,0);
	if(socket_ < 0)
	{
		printf("\nError! Socket for server not created");
		exit(1);
	}	

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddress.sin_zero,'\0',sizeof(serverAddress.sin_zero));

	if(bind(socket_,(const struct sockaddr *)&serverAddress,sizeof(serverAddress))==-1)
	{
		printf("\nError! Binding of server socket failed");
		exit(1);	
	}

	while(strcmp(buffer,"end")!=0)
	{
		if(recvfrom(socket_,(char*)buffer,sizeof(buffer)/sizeof(char),0,(struct sockaddr * )&clientAddress,&addressSize)==-1)
		{
			printf("\nError! Receiving from client failed");
			exit(1);	
		}
		printf("\nClient: %s",buffer);
		printf("\nServer: ");
		scanf("%s",buffer);
		if(sendto(socket_,(char*)buffer,sizeof(buffer)/sizeof(char),0,(const struct sockaddr *)&clientAddress,sizeof(clientAddress))==-1)
		{
			printf("\nError! Sending to client failed");
			exit(1);
		}
	}
	
	return(0);
}
