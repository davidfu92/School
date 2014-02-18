#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	int number[100000] = {0};
	int interval = 2;
	double time = 0;
	int n = 0;
	struct timeval start,end;
	while(interval<100000) {
		interval++;
		int c;
		gettimeofday(&start, NULL);
		for(c = 0; c<interval; c++) { 
			number[c]++;
		}
		gettimeofday(&end, NULL);
		double newtime = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
		if(newtime>time) {
			if(newtime-time>5)
			printf("Interval:%d Time Taken:%f Old Time: %f\n", interval, newtime,time);
			time = newtime;
		}
		n++;
	}
	return 0;
}
