#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "Hashmap.c"

void openDir(DIR *dir,Map tokens,char *path) {
	struct dirent* dir_loop;
	FILE *allf;
	while ((dir_loop = readdir (dir)) != NULL) {
		if(strcmp(dir_loop->d_name, ".") != 0 || strcmp(dir_loop->d_name, ".") !=  0) {
			char *loc = malloc(sizeof(char)*100);
			strcat(strcat(strcat(loc , path), "/"), dir_loop->d_name);
			printf ("%s\n", loc);
			allf = fopen(loc, "r");
			if(allf != NULL) {
				char c = fgetc(allf);
				char *w=calloc(100, sizeof(char));
				int spot = 0;
				while(c != EOF) {
					if(isalpha(c) || isdigit(c)) {
						w[spot]= c;
						spot++;
						//printf("%c", c);
					} else {
						if(spot>0) {
							w = realloc(w, sizeof(char)*(++spot));
							w[spot] = '\0';
							spot =0;
							printf("word: %s\n", w);
							hashmapInsert(tokens,dir_loop->d_name,w,hash(w));
							w = calloc(100, sizeof(char));
						}
					}
					c = fgetc(allf);
				}
				if(spot>0) {
					w = realloc(w, sizeof(char)*(++spot));
					w[spot] = '\0';
					spot =0;
					printf("word: %s\n", w);
					hashmapInsert(tokens,dir_loop->d_name,w,hash(w));
				}
			} else {
				perror("");
			}
			if(allf != NULL)
				fclose(allf);
		}
	}
}
int main(int argc, char **argv) {	
	if(argc != 3){
		fprintf(stderr,"Error: invalid number of arguments\n");
		return -1;
	}
	Map tokens = hashmapCreate(7919);
	struct dirent* dir_file;
	DIR *dir = NULL;
	FILE *index = fopen(argv[1], "r");
	if(index != NULL) {
		printf("FILE Already exist do you want to overwrite it y/n: ");
		char ch;
		scanf("%c", &ch);
		if(ch == 'y') {
			index = fopen(argv[1], "w");
		} else {
			printf("You choose to not overwite file\n");
		}
	} else {
		index = fopen(argv[1], "w");
	}
	FILE *input = NULL;
	dir = opendir(argv[2]);
	input= fopen(argv[2], "r");
	if(dir != NULL) {
		openDir(dir, tokens,argv[2]);
		//	while ((dir_file = readdir (dir)) != NULL) {
		//		printf ("%s\n", dir_file->d_name);
		//	}
	} else if(input != NULL) {
		char c = fgetc(input);
		char *w=calloc(100, sizeof(char));
		int spot = 0;
		while(c != EOF) {
			if(isalpha(c) || isdigit(c)) {
				w[spot]= c;
				spot++;
				//printf("%c", c);
			} else {
				if(spot>0) {
					w = realloc(w, sizeof(char)*(++spot));
					w[spot] = '\0';
					spot =0;
					printf("word: %s\n", w);
					hashmapInsert(tokens,argv[2],w,hash(w));
					w = calloc(100, sizeof(char));
				}
			}
			c = fgetc(input);
		}
		if(spot>0) {
			w = realloc(w, sizeof(char)*(++spot));
			w[spot] = '\0';
			spot =0;
			printf("word: %s\n", w);
			hashmapInsert(tokens,argv[2],w,hash(w));
		}
	} else {
		fprintf(stderr, "Erorr invalid FILE or DIRECTORY\n");
	}
	if(index != NULL)
		fclose(index);
	if(input != NULL)
		fclose(input);
	if(dir != NULL)
		closedir(dir);
	int s =0;
	for(s; s<tokens->size; s++) {
		//printf("one");
		if(tokens->table[s].key != 0) {
			struct Record *r = (tokens->table[s].rList)->list;
			while(r != NULL) {
				printf("hash word: %s file : %s number : %d\n", (tokens->table[s].rList)->word,r->file,r->count);
				r = r->next;
			}
		}
	}

	return 0;
}

