/* David Fu
 * Network Centric Programming Warm-Up
 * Feb 8, 2015
 */


//Including all the necessary C library

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


//Parses the Input to look for --systemcalls if exist return its location
int parse_input(int num_arg, char * input[]) {

	char * syscall = "--systemcalls";
	int init;
	//loop through all the arguments to find syscall
	for(init = 1; init < num_arg; init++) {
		if(strcasecmp(input[init], syscall) == 0)
			return init;
	}	
	return 0;

}

//function to count occurence of substring using stdio
int count_substring(FILE * sorc, char * sub) {
	char c = ' ';
	int numc = 0;
	//loop while not end of file
	while((c = fgetc(sorc)) != EOF) {
		//compare ignoring cases
		if(tolower(c) == tolower(sub[0])) {
			int ssize;
			for(ssize = 1; ssize < strlen(sub); ssize++) {
				c = fgetc(sorc);
				if(tolower(c) != tolower(sub[ssize])) {
					//jump back to inital since it no longer matches
					fseek(sorc, -1*ssize, SEEK_CUR);
					break;
				}
			}
			if(ssize == strlen(sub)) {
				//increase count by once since whole string match and jumps back so bbb counts as 2 for bb
				numc++;
				fseek(sorc, -1*(ssize-1), SEEK_CUR);
			}


		}
	}
	//prints out count to stdout
	fprintf(stdout, "%d\n", numc);
	//goes back to beginning of file
	fseek(sorc, 0, SEEK_SET);

}

//none system count of occurences
int count_occurrence(int nword, char * fname, char * str[]) {
	FILE * file_pointer;
	//opens file if issue print error
	if((file_pointer = fopen(fname, "r")) == NULL) {
		perror("Error");
		exit(1);
	}
	//loops through all possible word
	int count;
	for(count = 2; count < nword; count++) {
		count_substring(file_pointer, str[count]);
	}
	//close file when done
	fclose(file_pointer);
	return 0;
}

//similar to count_substring except system call version
int count_substring_sys(int file_des, char * sub) {
	char c = ' ';
	int numc = 0;
	while(read(file_des, &c, 1) != 0) {
		if(tolower(c) == tolower(sub[0])) {
			int ssize;
			for(ssize = 1; ssize < strlen(sub); ssize++) {
				read(file_des, &c, 1);
				if(tolower(c) != tolower(sub[ssize])) {
					lseek(file_des, -1*ssize, SEEK_CUR);
					break;
				}
			}
			if(ssize == strlen(sub)) {
				lseek(file_des, -1*(ssize-1), SEEK_CUR);
				numc++;
			}
		}
	}
	fprintf(stdout, "%d\n", numc);
	lseek(file_des, 0, SEEK_SET);
}

//same as count occurence except uses file descriptor instead of file pointer
int sys_count_occurrence(int nword, char * fname, char * str[]) {
	int file_des = 0;
	if((file_des = open(fname, O_RDONLY)) == -1) {
		perror("Error");
		exit(1);
	}
	int count;
	for(count = 3; count < nword; count++) {
		count_substring_sys(file_des, str[count]);
	}

	close(file_des);
	return 0;
}



//Main function
int main(int argc, char * argv[]) {
	int sys = 0;
	if(argc <3)
		return 1;
	if((sys = parse_input(argc, argv)) == 0 )
		count_occurrence(argc, argv[1], argv);
	else
		sys_count_occurrence(argc, argv[2], argv);
	return 0;
}