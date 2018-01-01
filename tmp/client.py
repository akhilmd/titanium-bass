# Import socket module
import socket               
 
# Create a socket object
s = socket.socket()         
 
# Define the port on which you want to connect
port = 8080               
 
# connect to the server on local computer
s.connect(('127.0.0.1', port))

while(True):
	line = input()
	if(line == "1"): break
	s.send(line.encode())
	print (s.recv(1024))
	
s.close()  
exit()
	