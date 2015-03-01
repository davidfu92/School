/*
 * proxy.c - A Simple Sequential Web proxy
 *
 * Course Name: 14:332:456-Network Centric Programming
 * Assignment 2
 * Student Name: David Fu_
 * 
 * IMPORTANT: Give a high level description of your code here. You
 * must also provide a header comment at the beginning of each
 * function that describes what that function does.
 */ 

#include "csapp.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


/*
 * Function prototypes
 */
void format_log_entry(char *logstring, struct sockaddr_in *sockaddr, char *uri, int size);

void print_error() {
	perror("Server Error: ");
	exit(1);
}


int create_server(int port_num) {
	int server_sock, optval;
	struct sockaddr_in proxy_addr;
	if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		print_error();
	}
	if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) < 0) {
		print_error();
	}
	memset(&proxy_addr, 0, sizeof(proxy_addr));
	proxy_addr.sin_family = AF_INET;
	proxy_addr.sin_port = htonl(port_num);
	proxy_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(server_sock, (struct sockaddr*)&proxy_addr, sizeof(proxy_addr)) != 0) {
		print_error();
	}
	if (listen(server_sock, 5) < 0) {
		print_error();
	}
	return server_sock;
}




/* 
 * main - Main routine for the proxy program 
 */
int main(int argc, char **argv)
{

	/* Check arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
		exit(0);
	}
	int server = create_server(atoi(argv[1]));




	while(1){
		int clientfd;
		if((clientfd = accept(server, 0, 0)) < 0)
			print_error();


		char buffer[1000];
		int bytesread=read(clientfd, buffer, sizeof(buffer)-1);
		buffer[bytesread]=0;

		printf("%s", buffer);

		//	if(strncmp(buffer,"GET",3) == 0)
		//		sscanf(buffer,"%s %s", str1, str2)          

		char filename[500] = "test.html";


		char filebuffer[10000];

		FILE* f = fopen(filename, "r");
		int filelen=fread(filebuffer, 1, sizeof(filebuffer), f);


		char msg[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
		char htmlresponse[1000000];
		strcpy(htmlresponse, msg);
		strcat(htmlresponse, filebuffer);
		write( clientfd, htmlresponse, strlen(htmlresponse));

		close(clientfd);
	} exit(0);
}

/*
 * format_log_entry - Create a formatted log entry in logstring. 
 * 
 * The inputs are the socket address of the requesting client
 * (sockaddr), the URI from the request (uri), and the size in bytes
 * of the response from the server (size).
 */
void format_log_entry(char *logstring, struct sockaddr_in *sockaddr, 
		char *uri, int size)
{
	time_t now;
	char time_str[MAXLINE];
	unsigned long host;
	unsigned char a, b, c, d;

	/* Get a formatted time string */
	now = time(NULL);
	strftime(time_str, MAXLINE, "%a %d %b %Y %H:%M:%S %Z", localtime(&now));

	/* 
	 * Convert the IP address in network byte order to dotted decimal
	 * form. Note that we could have used inet_ntoa, but chose not to
	 * because inet_ntoa is a Class 3 thread unsafe function that
	 * returns a pointer to a static variable (Ch 13, CS:APP).
	 */
	host = ntohl(sockaddr->sin_addr.s_addr);
	a = host >> 24;
	b = (host >> 16) & 0xff;
	c = (host >> 8) & 0xff;
	d = host & 0xff;


	/* Return the formatted log entry string */
	sprintf(logstring, "%s: %d.%d.%d.%d %s", time_str, a, b, c, d, uri);
}


