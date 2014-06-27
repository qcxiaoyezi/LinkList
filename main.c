#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    List *a;
    int v;
    List_Foreach_Variable;

    a = List_CreateNew(4);
	if(0==a){
		printf("Create New list failed!\n");
		return 0;
	}
	
    v=0;
    List_PushBack(a,(void*)&v);
    v=1;
    List_PushBack(a,(void*)&v);
    v=2;
    List_PushBack(a,(void*)&v);
    v=3;
    List_PushBack(a,(void*)&v);
    v=4;
    List_PushBack(a,(void*)&v);
    v=5;
    List_PushBack(a,(void*)&v);
    List_PushBack(a,(void*)&v);

    int val;

    List_Foreach(a){
        val = *(int*)List_Foreach_Value;
        if(2==val){
            List_Foreach_RmCurNode;
            continue;
        }
        printf("%d----------\n",val);
    }

    val = 2;

    printf("size of list %d\n",List_Count(a));
    printf("value size of list %d\n",List_ValueCount(a,(void*)&val));
    printf("index of \'%d\' is %d\n",val,List_Indexof(a,&val));

    List_Clear(a);

    return 0;
}
