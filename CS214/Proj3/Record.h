#ifndef RECORD_H
#define RECORD_H
#include <stdlib.h>
#include <string.h>
/*
 *  Defining the struct Record
 */
struct Record
{
	char *word;
	int count;
};

typedef struct *Record RecordPtr;

/*Compare two Record*/

int compareRec(RecordPtr r1, RecordPtr r2);

/*Convert a Record to String*/

char *toString(RecordPtr r);
#endif
