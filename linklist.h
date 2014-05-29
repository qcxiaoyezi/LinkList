#ifndef LINKLIST_H
#define LINKLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#define LIST_FREE(P) if(0!=P){free(P); P=0;}

typedef struct ListNode{
    struct ListNode *next;
    struct ListNode *previous;
    void *data;
}ListNode;

typedef struct List{
    int size;
    ListNode *head;
    ListNode *tail;
}List;

/*constructs a empty list*/
List* LIST_CreateNew(int size);
/*delete a list*/
void LIST_Delete(List *list);
/*remove all item from the list*/
void LIST_Clear(List *list);
/*create new listnode*/
ListNode* LIST_CreateNewNode();
/*delete a list node*/
void LIST_DeleteNode(ListNode*);

inline void LIST_AddNode(List* list, ListNode* pNode, ListNode* node);
inline void LIST_removeNode(List* list, ListNode* node);

/*inserts 'value' at index position 'index' in the list*/
int LIST_Insert(List *list, void *value ,int index);
/*same as 'LIST_PushBack'*/
int LIST_Append(List *list, void *value);
/*Inserts 'value' at the beginning of the list*/
int LIST_PushFront(List *list, void *value);
/*inserts 'value' at the end of the list*/
int LIST_PushBack(List *list, void *value);


/*remvoe the item at 'index' position*/
int LIST_RemoveAt(List *list,int index);
/*remove the frist item in the list*/
int LIST_RemoveFrist(List *list);
/*remove the last item in the list*/
int LIST_RemoveLast(List *list);



/*remove the item at index position 'index' and return it*/
int LIST_TakeAt(List *list, void *buff, int index);
/*remove the frist itme in the list and return it*/
int LIST_TakeFrist(List *list, void *buff);
/*remove the last imte in the list and return it*/
int LIST_TakeLast(List *list, void *buff);
/*same as 'MListTakeFrist'*/
int LIST_PopFront(List *list, void *buff);
/*same as 'MListTakeLast'*/
int LIST_PopBack(List *list, void *buff);


/*replaces the item at index position 'index' with 'value'*/
int LIST_Replace(List *list, void *value, int index);

/*return the node at index postion 'index'*/
inline ListNode *LIST_NodeAt(List *list, int index);
/*return the item at 'index' position*/
void* LIST_At(List *list,int index);
/*return the frist item in the list*/
void* LIST_Frist(List *list);
/*return the last item in the list*/
void *LIST_Last(List *list);


/*return 1 is list is empty*/
int LIST_IsEmpty(List *list);
/*return the number of items in the list*/
int LIST_Count(List *list);
/*return the number of occurrences of 'value' in the list*/
int LIST_ValueCount(List *list, void *value);
/*return the index position of the frist occurrence of 'value' in the list*/
int LIST_Indexof(List *list, void *value);

/*search Str*/
void* MListSearchStr(List *list, char *value ,int offset);
/*search Int*/
void* MListSearchInt(List *list, int value ,int offset);

/*iterate over all the items*/
extern ListNode *MList_g_pointer;
extern int MList_g_num;
#define MListForeach(node,list)  \
     MList_g_pointer = list->head; \
     MList_g_num = -1; \
    while(MList_g_pointer==0?0:(memcpy(node,MList_g_pointer->data,list->size),MList_g_pointer=MList_g_pointer->next,MList_g_num++,1))

/*watch value*/
#define WatchInt(x) printf("int %s's value is %d\n",#x,x)
#define WatchFloat(x) printf("float %s's value is %lf\n",#x,x)
#define WatchString(x) printf("str %s's value is %s\n",#x,x)
#define WatchPointer(x) printf("pointer %s's value is %p\n",#x,x)
#define Mark(x) printf("\nmark: %s\n",#x);

#ifdef __cplusplus
}
#endif

#endif
