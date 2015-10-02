#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define DATA "ASSALAMULAIKUM..YOU ARE WELCOME TO MY SOCKET.."

int main(int argc, char *argv[])
{
	int sock_des;
	struct sockaddr_in server;
	struct hostent *hp;
	char buff[1024];

	sock_des = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_des < 0)
	{
		perror("SOCKET FAILED !");
		exit(1);
	}

	server.sin_family = AF_INET;

	hp = gethostbyname(argv[1]);
	if(hp == 0)
	{
		perror("gethostbyname FAILED !");
		close(sock_des);
		exit(1);
	}

	memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
	server.sin_port = htons(3190);

	if(connect(sock_des, (struct sockaddr *) &server, sizeof(server)) < 0)
	{
		perror("CONNECTION FAILED");
		close(sock_des);
		exit(1);
	}
	
	if(send(sock_des, DATA, sizeof(DATA), 0) <0)
	{
		perror("SEND FAILED");
		close(sock_des);
		exit(1);
	}

	printf("SENT %s\n", DATA);
	close(sock_des);

	return 0;
}
