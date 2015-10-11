
import socket
from socket import * 
server_socket = socket(AF_INET,SOCK_STREAM)
server_name = 'localhost'
server_port = 3190
server_socket.bind((server_name, server_port))
server_socket.listen(5)
get = ''
while True:
	c , address = server_socket.accept()
	print "WE GOT CONNECTION FROM ", address
	c.send("ASSALAMUALAIKUM..WELCOME..(^_^)")
	get = server_socket.getsockopt(SOL_SOCKET,SO_KEEPALIVE)
	print "Get SO_KEEPALIVE : ",get
	set = server_socket.setsockopt(SOL_SOCKET,SO_KEEPALIVE,1)
	print "Set SO_KEEPALIVE : ",server_socket.getsockopt(SOL_SOCKET,SO_KEEPALIVE)

	c.close()
	break;
