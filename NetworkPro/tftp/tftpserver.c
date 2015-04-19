#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 1024
/*
 * error - wrapper for perror
 */
void error(char *msg) {
	perror(msg);
	exit(1);
}

void parsePackage(char * input, int size) {
	char path[500];
	int count = 2;
	if(input[1] == 1)
		printf("RRQ ");
	else
		printf("WRQ ");
	while (input[count] != 0) {
		printf("%c", input[count]);
		count ++;
		path[count-2] = input[count]
	}
	path[count-2] = '\0';
	count++;
	printf(" ");
	while (input[count] != 0) {
		printf("%c", input[count]);
		count ++;
	}
	printf(" from ");
}

int parseRead(char * file, int size) {
	FILE * ropen = fopen(file, "r");

	if(ropen == NULL) {
		
		return -1;	
		
	} else {


	}

}

int parseWrite(char * file, int size) {
	FILE * wopen = fopen(file, "w+");
}


void sendACK(int sockfd, struct sockaddr_in clientaddr, int clientlen) {
		char ACKmsg[500];
		ACKmsg[0] = 0;
		ACKmsg[1] = 4;
		ACKmsg[2] = 0;
		n = sendto(sockfd, ACKmsg, 100, 0, (struct sockaddr *) &clientaddr, clientlen);
		if (n < 0) 
			error("ERROR in sendto");


}


int main(int argc, char **argv) {
	int sockfd; /* socket */
	int portno; /* port to listen on */
	int clientlen; /* byte size of client's address */
	struct sockaddr_in serveraddr; /* server's addr */
	struct sockaddr_in clientaddr; /* client addr */
	struct hostent *hostp; /* client host info */
	char buf[BUFSIZE]; /* message buf */
	char *hostaddrp; /* dotted decimal host addr string */
	int optval; /* flag value for setsockopt */
	int n; /* message byte size */
	char defmsg[BUFSIZE];
	/* 
	 * check command line arguments 
	 */
	if (argc != 2) {
		fprintf(stdout, "WARNING: Without Input Port Number DEFAULT Set to 69 Will Not Work Without ROOT Access!! USAGE %s <PORT>\n\n", argv[0]);
		portno = 69;
	} else {
		portno = atoi(argv[1]);
	}
	/* 
	 *    * socket: create the parent socket 
	 *       */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");

	/* setsockopt: Handy debugging trick that lets 
	 *    * us rerun the server immediately after we kill it; 
	 *       * otherwise we have to wait about 20 secs. 
	 *          * Eliminates "ERROR on binding: Address already in use" error. 
	 *             */
	optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 
			(const void *)&optval , sizeof(int));

	/*
	 *    * build the server's Internet address
	 *       */
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)portno);

	/* 
	 *    * bind: associate the parent socket with a port 
	 *       */
	if (bind(sockfd, (struct sockaddr *) &serveraddr, 
				sizeof(serveraddr)) < 0) 
		error("ERROR on binding");

	/* 
	 *    * main loop: wait for a datagram, then echo it
	 *       */
	clientlen = sizeof(clientaddr);
	while (1) {

		/*
		 *      * recvfrom: receive a UDP datagram from a client
		 *           */
		bzero(defmsg, BUFSIZE);
		bzero(buf, BUFSIZE);
		n = recvfrom(sockfd, buf, BUFSIZE, MSG_WAITALL, (struct sockaddr *) &clientaddr, &clientlen);
		parsePackage(buf, n);
		if (n < 0)
			error("ERROR in getting package");

		/* 
		 *      * gethostbyaddr: determine who sent the datagram
		 *           */
		hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
				sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		if (hostp == NULL)
			error("ERROR on Getting Host Name");
		hostaddrp = inet_ntoa(clientaddr.sin_addr);
		if (hostaddrp == NULL)
			error("ERROR on Getting Clinet IP\n");
		printf("%s:%d\n", hostaddrp, (unsigned short)&clientaddr.sin_port);

		/* 
		 *      * sendto: echo the input back to the client 
		 *           */
		defmsg[0] = 0;
		defmsg[1] = 5;
		defmsg[2] = 1;
		strcpy((char *)&(defmsg[3]), "FILE NOT FOUND");
		defmsg[17] = 0;
		n = sendto(sockfd, defmsg, 100, 0, (struct sockaddr *) &clientaddr, clientlen);
		if (n < 0) 
			error("ERROR in sendto");
	}
}
