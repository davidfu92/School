/*
 * sorted-list.c
 */

#include	<string.h>
#include    <stdio.h>
#include    <stdlib.h>
#include	"sorted-list.h"


enum TYPE{
    STRING,
    INT,
    DOUBLE
};

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}






/*
 *
 *  Helper functions
 *
 */
int populate_list(SortedListPtr s, int type, int len, int iargs[], double dargs[],char*sargs[]){
    
    int i;
    if(type == INT){
        for(i = 0; i < len; i++){
            if(SLInsert(s,&(iargs[i])) == 0){
                return 0;
            }
        }
    }else if (type == DOUBLE){
        for(i = 0; i < len; i++){
            if(SLInsert(s,&(dargs[i])) == 0){
                return 0;
            }
        }
    }else if(type==STRING){
        printf("STRINGS\n");
        for(i = 0; i < len; i++){
            printf("Inserting %s\n", sargs[i]);

            if(SLInsert(s,sargs[i]) == 0){
                return 0;
            }
        }
    }
    
    return 1;
    
}




void iterprint_all(SortedListPtr s, SortedListIteratorPtr iter, int type){
    void *item;
    while(1){
        item = SLNextItem(iter);
        if (item == NULL){
            break;
        }else{
            if(type == INT){
                printf("%d ", *((int*)item));
            }else if(type == DOUBLE){
                printf("%f ", *((double*)item));
            }
            else if(type==STRING){
                printf("%s ", ((char*)item));
            }
        }
    }
    printf("\n");
}

void iterprint_all_int(SortedListPtr s, SortedListIteratorPtr iter){
    iterprint_all(s,iter,INT);
}

void success(){
    char*passmessage = "Success";
    printf("%s\n",passmessage);
}

void failure(){
    char*failmessage = "Failure";
    printf("%s\n",failmessage);
}

/*
 *
 *
 *  Main
 *
 *  Don't use valgrind.  Things will leak.
 *
 *
 */

int main(int argc, char*argv[])
{
    int choice = atoi(argv[1]);

    
    printf("Choice: %d\n", choice);
    
    if(choice == 1){
        //1.  Normal SLInserts (@ beginning, middle, end of list)
        //a. integers
        SortedListPtr s = SLCreate(compareInts);
        int iarr[6] = {7,5,155,42,-1,6};
        if(populate_list(s,INT,sizeof(iarr)/sizeof(int),iarr,NULL,NULL) == 0){
            failure();
            return 1;
        }
        SortedListIteratorPtr iter = SLCreateIterator(s);
        iterprint_all(s,iter,INT); //prints 155 42 7 6 5 -1
        
        
    }else if(choice == 2){
        //b. doubles
        SortedListPtr s = SLCreate(compareDoubles);
        
        double darr[6] = {7.43,5.55,155.26,42.1,-1.5,6.7};
        if(populate_list(s,DOUBLE,sizeof(darr)/sizeof(double),NULL,darr,NULL) == 0){
            failure();
            return 1;
        }

        
        SortedListIteratorPtr iter = SLCreateIterator(s);
        iterprint_all(s,iter,DOUBLE); //prints 155.26 42.1 7.43 6.7 5.55 -1.5
        
        
    }else if(choice == 3){
        //c. strings
        SortedListPtr s = SLCreate(compareStrings);
        
        char *carr[6] = {"cat","dog","catamaran","apple","cormorant","zebra"};
        if(populate_list(s,STRING,6,0,0,carr) == 0){
            failure();
            return 1;
        }

        SortedListIteratorPtr iter = SLCreateIterator(s);
        iterprint_all(s,iter,STRING); //prints apple cat catamaran cormorant dog zebra
        
        
        
    }else if(choice == 4){
        //SLInsert on null list;
        int x = 5;
        if(SLInsert(NULL, &x) == 0){
            success();
        }else{
            failure();
        }
    }else if(choice == 5){
        //SLInsert null object
        SortedListPtr s = SLCreate(compareDoubles);

        if (SLInsert(s,NULL) == 0){
            success();
        }else{
            failure();
        }
    
    }else if(choice == 6){
        //SLRemove nonexistent element
        SortedListPtr s = SLCreate(compareInts);
        int iarr[6] = {7,5,155,42,-1,6};
        populate_list(s,INT,sizeof(iarr)/sizeof(int),iarr,0,0);

        int toremove = 54;
        if (SLRemove(s,&toremove) != 0) {
            failure();
        }else{
            success();
        }
    }else if(choice == 7){
        //SLRemove existing element (no duplicates; didn't handle them anyway)
        SortedListPtr s = SLCreate(compareInts);
        int iarr[6] = {7,5,155,42,-1,6};
        populate_list(s,INT,sizeof(iarr)/sizeof(int),iarr,0,0);


        int toremove = 5;
        
        if (SLRemove(s,&toremove) != 0) {
            SortedListIteratorPtr iter = SLCreateIterator(s);
            iterprint_all_int(s,iter); //prints 155 42 7 6 -1
        }else{
            failure();
        }
        
    }else if(choice == 8){
        //Iterate on empty list
        SortedListPtr s = SLCreate(compareInts);
        SortedListIteratorPtr iter = SLCreateIterator(s);
        iterprint_all_int(s,iter);
        //TODO: Separate into a) create iterator b) print empty list
    }else if(choice == 9){
        //Create new iterator on list, destroy old one mid-iteration
        SortedListPtr s = SLCreate(compareInts);
        int iarr[6] = {7,5,155,42,-1,6};
        populate_list(s,INT,sizeof(iarr)/sizeof(int),iarr,0,0);
        
        
        
        SortedListIteratorPtr olditer = SLCreateIterator(s);
        void *olditem = SLNextItem(olditer);
        olditem = SLNextItem(olditer);
        SortedListIteratorPtr iter = SLCreateIterator(s);
        SLDestroyIterator(olditer);
        
        iterprint_all_int(s,iter); //prints 155 42 7 6 5 -1
    }else if(choice == 10){ //TODO
        //Create multiple iterators on same list, interleave iterations.
        
        SortedListPtr s = SLCreate(compareInts);
        int iarr[6] = {7,5,155,42,-1,6};
        populate_list(s,INT,sizeof(iarr)/sizeof(int),iarr,0,0);
        
        SortedListIteratorPtr olditer = SLCreateIterator(s);
        
        SortedListIteratorPtr iter = SLCreateIterator(s);

        
        void *item;
        
        item = SLNextItem(olditer);
        printf("%d ", *((int*)item));
        item = SLNextItem(olditer);
        printf("%d ", *((int*)item));  //prints 155 42
        
        item = SLNextItem(iter);
        printf("%d ", *((int*)item));
        item = SLNextItem(iter);
        printf("%d ", *((int*)item));
        item = SLNextItem(iter);
        printf("%d ", *((int*)item)); //prints 155 42 7
        
        
        item = SLNextItem(iter);  //prints 6
        printf("%d ", *((int*)item));
        item = SLNextItem(olditer);
        printf("%d ", *((int*)item)); //prints 7
        
        
        iterprint_all_int(s,iter); //prints 5 -1
        
        iterprint_all_int(s,olditer); //prints 6 5 -1
        
    }else if(choice == 11){
        //SLRemove end element, iterator positioned on it
        
        SortedListPtr s = SLCreate(compareInts);
        int iarr[3] = {7,5,3};
        populate_list(s,INT,sizeof(iarr)/sizeof(int),iarr,0,0);

        
        SortedListIteratorPtr iter = SLCreateIterator(s);

        int x3 = 3;
        void *item = SLNextItem(iter);
        item = SLNextItem(iter);
        if(SLRemove(s,&x3) && SLNextItem(iter) == NULL){
            success();
        }else{
            failure();
        }
        
    }else if(choice == 12){ //TODO
        //SLRemove beginning element, iterator positioned on it
        
        SortedListPtr s = SLCreate(compareInts);
        int iarr[3] = {7,5,3};
        populate_list(s,INT,sizeof(iarr)/sizeof(int),iarr,0,0);
        
        SortedListIteratorPtr iter = SLCreateIterator(s);
        
        int x1 = 7;
        if(SLRemove(s,&x1) && *((int*)SLNextItem(iter)) == 5 &&
           *((int*)SLNextItem(iter)) == 3 &&
           ((int*)SLNextItem(iter)) == NULL){
            success();
        }else{
            failure();
        }
    }else if(choice == 13){ //TODO
        //SLRemove element in middle, iterator positioned on it
        SortedListPtr s = SLCreate(compareInts);
        int iarr[3] = {7,5,3};
        populate_list(s,INT,sizeof(iarr)/sizeof(int),iarr,0,0);
        
        SortedListIteratorPtr iter = SLCreateIterator(s);
        void *item = SLNextItem(iter);
        
        if (*((int*)item) != 7) {
            failure();
            return 1;
        }
        
        int x1 = 5;
        if(SLRemove(s,&x1) && *((int*)SLNextItem(iter)) == 3 &&
           ((int*)SLNextItem(iter)) == NULL){
            success();
        }else{
            failure();
        }
    }else if(choice == 14){
        //Add element after iterator
        SortedListPtr s = SLCreate(compareInts);
        int iarr[3] = {7,5,3};
        populate_list(s,INT,sizeof(iarr)/sizeof(int),iarr,0,0);
        
        SortedListIteratorPtr iter = SLCreateIterator(s);
        void *item = SLNextItem(iter);
        item = SLNextItem(iter);
        int x4 = 4;
        SLInsert(s,&x4); //prints 4 3
        
        iterprint_all_int(s,iter);
        
        
    }else if(choice == 15){
        //Remove element after iterator
        SortedListPtr s = SLCreate(compareInts);
        int iarr[4] = {7,5,3,4};
        populate_list(s,INT,sizeof(iarr)/sizeof(int),iarr,0,0);
        
        
        SortedListIteratorPtr iter = SLCreateIterator(s);
        void *item = SLNextItem(iter);
        item = SLNextItem(iter);
        int x4 = 4;
        if(SLRemove(s,&x4)){
            iterprint_all_int(s,iter); //prints 3
        }else{
            failure();
        }
    }else{
        printf("Bad input\n");
    }
    
    
    return 0;
    
}
