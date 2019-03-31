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
	printf("\nThis is client:\n");
	int socket_;
	char buffer[MAX];
	struct sockaddr_in serverAddress;
	socklen_t addressSize = sizeof(serverAddress);

	socket_ = socket(PF_INET,SOCK_DGRAM,0);
	if(socket_ == -1)
	{
		printf("\nError! Socket for server not created");
		exit(1);
	}	

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddress.sin_zero,'\0',sizeof(serverAddress.sin_zero));


	while(strcmp(buffer,"end")!=0)
	{
		printf("\nClient: ");
		scanf("%s",buffer);
		
		if(sendto(socket_,(char*)buffer,sizeof(buffer)/sizeof(char),0,(const struct sockaddr *)&serverAddress,sizeof(serverAddress))==-1)
		{
			printf("\nError! Sending to client failed");
			exit(1);
		}

		if(recvfrom(socket_,(char*)buffer,sizeof(buffer)/sizeof(char),0,(struct sockaddr * )&serverAddress,&addressSize)==-1)
		{
			printf("\nError! Receiving from client failed");
			exit(1);	
		}
		printf("\nServer: %s",buffer);
	}
	
	return(0);
}
