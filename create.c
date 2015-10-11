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
	int op_val,route;
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
			printf("I'VE GOT THE MESSAGE \n", rval);
			getsockopt(socket_desc, SOL_SOCKET, SO_DONTROUTE, &op_val, &route);
			if(op_val != 0)
			{
				printf("UNABLE TO GET\n");

			}
			printf("Get SO_DONTROUTE : %d\n",op_val);
			op_val = 1;
			setsockopt(socket_desc, SOL_SOCKET, SO_DONTROUTE, &op_val, sizeof 1);
				printf("ALREADY SET \n");
			getsockopt(socket_desc, SOL_SOCKET, SO_DONTROUTE, &op_val, &route);
			if(op_val == 0)
				printf("UNABLE TO GET \n");
			else
				printf("Get New SO_DONTROUTE : %d\n",op_val);

		close(sock1);
		exit(1);
		}
	} while (1);
	return 0;

}
