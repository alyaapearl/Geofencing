#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

int main()
{
	int sockCli,portNo,nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	//create UDP socket
	sockCli = socket(AF_INET,SOCK_DGRAM,0);

	//configure settings in address struct
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7004);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	//initialize size variable to be used later on
	addr_size = sizeof serverAddr;

	while(1)
	{
		printf("Message to server : \n");
		fgets(buffer,1024,stdin);
		printf("You typed :%s", buffer);

		nBytes = strlen(buffer) + 1;

		//send message to server
		sendto(sockCli,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);

		//receive message to server
			nBytes = recvfrom(sockCli,buffer,1024,0,NULL,NULL);

		printf("Received from server : %s\n", buffer);
	}
	return 0;
}
