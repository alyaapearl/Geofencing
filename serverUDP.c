#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int sockUDP, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr, clientAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size, client_addr_size;
	int i;
	
	//Create UDP socket
	sockUDP = socket(AF_INET, SOCK_DGRAM, 0);

	//configure settings in address struct
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7004);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	//bind socket with address struct
	bind(sockUDP, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	//initialize size  variable to be used later on
	addr_size = sizeof serverStorage;

	while(1)
	{
	/*Try to receive any incoming UDp datagram.Address and port of 
	requesting client will be stored on serverStorage variable*/
		nBytes = recvfrom(sockUDP,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
	
	//convert message received to uppercase
		for(i=0;i<nBytes-1;i++)
			buffer[i] = toupper(buffer[i]);

	//send uppercase message back to client,using serverStorage as the address
		sendto(sockUDP,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
	}
	return 0;
}
