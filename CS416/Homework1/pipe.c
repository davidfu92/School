#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]) {
	int size = atoi(argv[1])*256;
	char *passage = malloc(sizeof(char)*size);

	int arr[2];
	char *buffer = malloc(sizeof(char)*size*2);
	int message;
	struct timeval start,end;
	int id= getpid();
	int c, kid,passes;
	pipe(arr);
	gettimeofday(&start, NULL);
	kid = fork();

	if(getpid() == kid) {
		for(passes = 0; passes<500; passes++) {
			close(arr[0]);
			write(arr[1], passage, (strlen(passage)+1));
			open(arr[0]);
		}
		for(passes = 0; passes<500; passes++) {
			close(arr[1]);
			message = read(arr[0], buffer, sizeof(buffer));
			open(arr[1]);
		}

	} else {
		for(passes = 0; passes<500; passes++) {
			close(arr[1]);
			message = read(arr[0], buffer, sizeof(buffer));
			open(arr[1]);
		}
		for(passes = 0; passes<500; passes++) {
			close(arr[0]);
			write(arr[1], passage, (strlen(passage)+1));
			open(arr[0]);
		}
	}
	gettimeofday(&end, NULL);
	double avetime = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	if(getpid() == id)
		printf("Average pipe cost of %dMB of data is %.5f\n",size/256, avetime/1000);
	free(buffer);
	free(passage);
}
