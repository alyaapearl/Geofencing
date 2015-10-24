import socket
import sys
import errno
import os

HOST = 'localhost'
PORT = 5010

#datagram(udp) socket
try:
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	print 'Socket READY !!!'
except socket.error, msg:
	print 'FAILED to create socket. Error code : '+str(msg[0])+'Message'+msg[1]
	sys.exit()

server_address = (HOST,PORT)
print>>sys.stderr, 'START UP ON %s PORT %s' % server_address
#bind socket to local host and port
try:
	sock.bind((HOST, PORT))
except socket.error, msg:
	print 'Bind FAILED. Error code : '+str(msg[0])+' Message\n'+msg[1]
	sys.exit()

print 'Socket bind complete !!'

#talking with the client
while True:
	print>>sys.stderr,'\nSTILL WAITING...FOR THE MESSAGE.. (-_-)'
	#receive data from client (data,addr)
	data, addr = sock.recvfrom(1024)
	print>>sys.stderr,'RECEIVED %s BYTES FROM %s' %(len(data),addr)
	print>>sys.stderr,data

	if data:
		s = sock.sendto(data, addr)
		print>>sys.stderr, 'SENT %s BYTES BACK TO %s'%(s,addr)

	get = sock.getsockopt(socket.SOL_SOCKET,socket.SO_KEEPALIVE)
	print "Get SO_KEEPALIVE : ", get
#pitfall 1
	if get >0:
		print "ALREADY get SO_KEEPALIVE!!"
	elif get <0:
		print "ERROR DETECTED", errno.EINPROGRESS
		print "DESCRIPTION : ", os.strerror(errno.EINPROGRESS)
#pitfall 2
		sock.close()

	
	set = sock.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE,1)
	print "Set SO_KEEPALIVE : ", sock.getsockopt(socket.SOL_SOCKET, socket.
SO_KEEPALIVE)
	
	break
sock.close()


