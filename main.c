#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    List *a;
	int v = 10;
	int b;

    a = LIST_CreateNew(sizeof(int));
	if(0==a){
		printf("Create New list failed!\n");
		return 0;
	}
	
    v=0;
    LIST_Append(a,(void*)&v);
    v=1;
    LIST_Append(a,(void*)&v);
    v=2;
    LIST_Append(a,(void*)&v);
    v=3;
    LIST_Append(a,(void*)&v);
    v=4;
    LIST_Append(a,(void*)&v);
    v=5;
    LIST_Append(a,(void*)&v);
//    v=4;
//    LIST_PushBack(a,(void*)&v);
//    v=9;
//    LIST_PushFront(a,(void*)&v);
//    v=3;
//    LIST_Insert(a,(void*)&v,2);

//    LIST_RemoveAt(a,5);
//    LIST_RemoveFrist(a);
//    LIST_RemoveLast(a);

    LIST_RemoveAt(a,3);

    MListForeach(&b,a){
        printf("%d = %d\n",MList_g_num+1,b);
    }
    LIST_Delete(a);

    return 0;
}
