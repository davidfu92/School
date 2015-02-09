#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

int main() {

	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in addr;
	
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(54321);

	bind(sfd, &addr, sizeof(addr));

	listen(sfd, 5);

	int cfd = accept(sfd, NULL, 0);


	char response[] = "First Socket Test Program\n";
	write(cfd, response, strlen(response));

	return 0;

}
