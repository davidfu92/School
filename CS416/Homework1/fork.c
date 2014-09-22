#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
int main(int argc, char* argv[]) {
	int size = atoi(argv[1])*256;
	int *arr = malloc(sizeof(int)*size);
	struct timeval start,end;
	int id= getpid();
	int c, kid;
	gettimeofday(&start, NULL);
	for(c = 0; c<1000; c ++) {
		kid = fork();
		if(getpid() == kid)
			exit(0);
	}
	gettimeofday(&end, NULL);
	double avetime = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec))/1000;
	if(getpid() == id)
	printf("Average fork cost for %dMB is %f\n", size/256, avetime);
	free(arr);
}
