#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


int main()
{

	int file = open("testfile", O_WRONLY|O_CREAT);
	char * output = "Hello World Program For Network Centric Programming Class\n";
//	write(STDOUT_FILENO, output,strlen(output));
	write(file, output, strlen(output));
	close(file);
	return(0);
}
