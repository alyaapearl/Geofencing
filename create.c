#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc, char *argv[])
{ 
	int socket_desc;
	int sock1;
	int rval;
	struct sockaddr_in server;
	char buff[1024];

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc < 0)
	{
		perror("Could not create socket\n");
		exit(1);
	}

	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(3190);

	//Connect to remote server
	if(bind(socket_desc,(struct sockaddr *)&server, sizeof(server)))
	{
		perror("Bind Error\n");
		exit(1);
	}

 	//Listen for connection
	listen(socket_desc, 5);

	//Accept connection
	do
	{
		sock1 = accept(socket_desc, (struct sockaddr *) 0, 0);
		if(sock1 == -1)
		{
			perror("CONNECTION FAILED !");
		}
		else
		{
			memset(buff, 0, sizeof(buff));
			if((rval = recv(sock1, buff, sizeof(buff), 0)) < 0)
				perror("MESSAGE ERROR !");
			else if(rval == 0)
				printf("END CONNECTION\n");
			else
				printf("MSG: %s\n",buff);
			printf("I'VE GOT THE MESSAGE (rval = $d)\n", rval);
			close(sock1);
		}
	} while (1);
	return 0;

}
