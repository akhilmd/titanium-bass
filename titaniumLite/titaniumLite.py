import socket
import pandas as pd

class titaniumLite:
	
	def __init__(self, host = '127.0.0.1', port = 8080):
		self.s = socket.socket()         
		
		self.host = host
		self.port = port               
		 
		self.s.connect((self.host, self.port))

	def __del__(self):
		self.s.close()

	def execute(self, query):
		self.s.send(query.encode())
		return self.dataframe(self.s.recv(1024))
	
	def dataframe(self, output):
		table = output
		return table.decode()

if __name__ == '__main__':
	t = titaniumLite()
	print(t.execute('use database db1;'))
	# t.execute('select * from stats;')
	del t
	