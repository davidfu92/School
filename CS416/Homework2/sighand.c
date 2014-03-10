#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>


int time = 0;
struct timeval start, end;
int excute = 0;
void output()
{
	double n = (double)time;
	double d = (double)excute;
	double r = n/d;
	printf("total time %d, run %d\n, average time %f\n",time,excute,r);
}
void sig_handler(int sig)
{
	if (sig == SIGINT) {
		excute+=1;
	}
	if (sig == SIGTSTP)
		output();
}

int main()
{
	int pid = getpid();	
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("\n\ncan't catch SIGINT\n");
	if (signal(SIGTSTP, sig_handler) == SIG_ERR)
		printf("\n\ncan't catch SIGTSTP\n");
	gettimeofday(&start, NULL);
	int t = 0;
	for(t=0;t<10000000;t++) {
		kill(pid,SIGINT);
	}
	time = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
	kill(pid,SIGTSTP);
	gettimeofday(&end, NULL);
	return 0;
}
