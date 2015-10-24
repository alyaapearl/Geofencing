import socket
import sys
 
try:
	sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)   #(internet, UDP)
except socket.error:
	print 'FAILED to create socket'
	sys.exit()

HOST = 'localhost'
PORT = 5010

try:
		#set string 
		s = sock.sendto('CONNECTED',(HOST, PORT))
 
		#receive data from client (data, addr)
		data, addr = sock.recvfrom(1024)
		print "RECEIVED MESSAGE : ",data
finally:
	sock.close()
