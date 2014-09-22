#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>


int main() {
	int number[1048576] = {1};
	double time = 0;
	int n = 0;
	struct timeval start,end;
	int interval = 0;
	for(n = 1048575; n>-1; n--) { 
			number[n]++;
		}
	while(interval<1048576) {
		interval++;
		int c;
		gettimeofday(&start, NULL);
		for(c = 0; c<interval; c++) { 
			number[c]++;
		}
		gettimeofday(&end, NULL);
		double newtime = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
		if(newtime>time) {
			if(newtime-time>10)
			printf("Interval:%d Time Taken:%f Old Time: %f Estmated: %f\n", interval, newtime,time, newtime/(interval/1024));
			time = newtime;
		}
		n++;
	}
/*	int x,y;
	for(x = 0; x <10; x++) {
		for(y = 0; y<500000; y++) {
			number[y]+=x;
		}
	}
	gettimeofday(&start, NULL);
	number[750000]=1+2;
	gettimeofday(&end, NULL);
	double newtime = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
	printf("Interval:%d Time Taken:%f Old Time: %f\n", interval, newtime,time); */
	return 0;
}
