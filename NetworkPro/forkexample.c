#include<stdio.h>
#include<unistd.h>

int main() {
	printf("Befor Fork\n");
	fork();
	printf("Hello World\n");
	return 0;
}
