// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <readline/readline.h>
#define PORT 8080

int sock_create() {
	struct sockaddr_in address;
    int sock = 0;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
	
	return sock;
}

int main(int argc, char const *argv[])
{
	char *hello = "Hello from client";
    char buffer[1024] = {0};
    int sock = sock_create();
	
	while(1) {
		
		char *line = readline(">>>");
		if(!strcmp(line, "1")) break;
		send(sock , line, strlen(line) , 0);
		int valread = read( sock , buffer, 1024);
		printf("%s\n", buffer);
	}
    return 0;
}