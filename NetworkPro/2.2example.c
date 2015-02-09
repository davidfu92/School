#include <stdio.h>

int main(char * arg1, char * arg2) {
	if(arg1 != NULL && arg2 != NULL)
	{
		fopen(arg1, "r");
		fopen(arg2, "w+");
		char buf[1];

		while(buf != EOF) {

			int *p = 0;
			printf(*p + "\n");

		}
	}
	return 0;
}
