#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

/*FILE *openDir(DIR *dir) {
  while ((in_file = readdir(FD))) 
  {
  if (!strcmp (in_file->d_name, "."))
  continue;
  if (!strcmp (in_file->d_name, ".."))    
  continue;
  entry_file = fopen(in_file->d_name, "rw");
  if (entry_file == NULL)
  {
  fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));
  fclose(common_file);

  return 1;
  }

  Doing some struf with entry_file : 
  For example use fgets 
  while (fgets(buffer, 500, entry_file) != NULL)
  {
  Use fprintf or fwrite to write some stuff into common_file
  }

  When you finish with the file, close it
  fclose(entry_file);
  }

  Don't forget to close common file before leaving 
  fclose(common_file);

  return 0;
  }
  */
/*
   struct stat s;
   int err = stat(argv[2], &s);
   if(-1 == err) {
   if(ENOENT == errno) {
   printf("DIRECTORY/FILE Does Not Exist\n");
   } else {
   perror("stat");
   exit(1);
   }
   } else {
   if(S_ISDIR(s.st_mode)) {

   } else {
   FILE *input = fopen(argv[2], "r");
   }
   }
   fclose(index);
   fclose(input);
   */

int main(int argc, char **argv) {	
	if(argc != 3){
		fprintf(stderr,"Error: invalid number of arguments\n");
		return -1;
	}
	struct dirent* dir_file;
	DIR *dir = NULL;
	FILE *index = fopen(argv[1], "r");
	if(index != NULL) {
		printf("FILE Already exist do you want to overwrite it y/n: ");
		char ch;
		scanf("%c", &ch);
		printf("\n");
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
	if(dir != NULL) 
	{
	} else if(input != NULL) {

	} else {
		fprintf(stderr, "Erorr invalid FILE or DIRECTORY\n");
	}
	if(index != NULL)
	fclose(index);
	if(input != NULL)
	fclose(input);
	return 0;
}

