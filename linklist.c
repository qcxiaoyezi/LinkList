#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListNode *MList_g_pointer;
int MList_g_num;

/*constructs a empty list*/
List* LIST_CreateNew(int size)
{
    List *link;

    link = (List*)malloc(sizeof(List));
    if(0!=link){
        link->size = size;
        link->head = 0;
        link->tail = 0;
    }
    return link;
}

/*delete a list*/
void LIST_Delete(List *list)
{
    if(0==list) return;
    LIST_Clear(list);
    LIST_FREE(list);
}

/*remove all item from the list*/
void LIST_Clear(List *list)
{
    ListNode *p;
    ListNode *q;

    if(0==list || 0==list->head) return;

    p = list->head;
    while(p){
        q = p;
        p = p->next;
        LIST_DeleteNode(q);
    }
    list->head = 0;
}

/*create new list node*/
ListNode* LIST_CreateNewNode(List *list, void *value)
{
    ListNode* node;
    if(0==list || 0==value) return 0;
    node = (ListNode*)malloc(sizeof(ListNode));
    if(0==node) return 0;
    node->data = malloc(list->size);
    if(0==node->data){
        LIST_FREE(node);
        return 0;
    }
    memcpy(node->data,value,list->size);
    node->next = 0;
    node->previous = 0;
    return node;
}
/*delete list node*/
void LIST_DeleteNode(ListNode *node)
{
    if(0==node) return;
    LIST_FREE(node->data);
    LIST_FREE(node);
}

inline void LIST_AddNode(List* list, ListNode* pNode, ListNode* node)
{
    ListNode* nNode;
    if(0==list || 0==node) return;
    nNode = (0==pNode) ? list->head : pNode->next;
    node->previous = pNode;
    node->next = nNode;
    if(0==nNode){
        list->tail = node;
    }else{
        nNode->previous = node;
    }
    if(0==pNode){
        list->head = node;
    }else{
        pNode->next = node;
    }
}

inline void LIST_removeNode(List* list, ListNode* node)
{
    if(0==list || 0==node) return;
    if(0!=node->next){
        node->next->previous = node->previous;
    }
    if(0!=node->previous){
        node->previous->next = node->next;
    }
    if(list->head == node){
        list->head = node->next;
    }
    if(list->tail == node){
        list->tail = node->previous;
    }
    LIST_DeleteNode(node);
}


/*inserts 'value' at index position 'index' in the list*/
int LIST_Insert(List *list, void *value ,int index)
{
    ListNode *node;
    ListNode *pNode;

    if(0==list || 0==value || 0>index) return -1;

    pNode = LIST_NodeAt(list,index-1);
    /*constructs a new node*/
    node = LIST_CreateNewNode(list,value);
    if(0==node) return -1;
    LIST_AddNode(list,pNode,node);

    return 0;
}

/*inserts 'value' at the end of the list*/
int LIST_Append(List *list, void *value)
{
    return LIST_PushBack(list,value);
}

/*Inserts 'value' at the beginning of the list*/
int LIST_PushFront(List *list, void *value)
{
    return LIST_Insert(list,value,0);
}

/*inserts 'value' at the end of the list*/
int LIST_PushBack(List *list, void *value)
{
    ListNode *node;

    if(0==list || 0==value) return -1;
    /*constructs a new node*/
    node = LIST_CreateNewNode(list,value);
    if(0==node) return -1;

    LIST_AddNode(list,list->tail,node);
    return 0;
}

/*remvoe the item at 'index' position*/
int LIST_RemoveAt(List *list,int index)
{
    ListNode *node;
    if(0==list || 0==list->head || 0>index) return -1;

    node = LIST_NodeAt(list,index);
    LIST_removeNode(list,node);
    return 0;
}

/*remove the frist item in the list*/
int LIST_RemoveFrist(List *list)
{
    if(0==list) return -1;
    LIST_removeNode(list,list->head);
    return 0;
}

/*remove the last item in the list*/
int LIST_RemoveLast(List *list)
{
    if(0==list) return -1;
    LIST_removeNode(list,list->tail);
    return 0;
}

/*remove the item at index position 'index' and return it*/
int LIST_TakeAt(List *list, void *buff, int index)
{
    void *p;

    p = LIST_At(list,index);
    if(0==p) return -1;
    memcpy(buff,p,list->size);
    LIST_RemoveAt(list,index);
    return 0;
}

/*remove the frist itme in the list and return it*/
int LIST_TakeFrist(List *list, void *buff)
{
    return LIST_TakeAt(list,buff,0);
}

/*remove the last imte in the list and return it*/
int LIST_TakeLast(List *list, void *buff)
{
    return LIST_TakeAt(list,buff,LIST_Count(list)-1);
}

/*remove the frist itme in the list and return it*/
int LIST_PopFront(List *list, void *buff)
{
    return LIST_TakeAt(list,buff,0);
}

/*remove the last imte in the list and return it*/
int LIST_PopBack(List *list, void *buff)
{
    return LIST_TakeAt(list,buff,LIST_Count(list)-1);
}

/*replaces the item at index position index with value*/
int LIST_Replace(List *list, void *value, int index)
{
    int result;

    result = LIST_RemoveAt(list,index);
    if(0!=result) return -1;
    LIST_Insert(list,value,index);
    return 0;
}

inline ListNode *LIST_NodeAt(List *list, int index)
{
    int n;
    ListNode * node;

    if(0==list || 0>index) return 0;
    node = list->head;
    for(n=0;n<index;n++){
        if(0==node) break;
        node = node->next;
    }
    return node;
}

/*return the item at 'index' position index*/
void* LIST_At(List *list,int index)
{
    ListNode *node;
    node = LIST_NodeAt(list,index);
    return ((0==node)?0:node->data);
}

/*return the frist item in the list*/
void* LIST_Frist(List *list)
{
    return LIST_At(list,0);
}

/*return the last item in the list*/
void *LIST_Last(List *list)
{
    if(0==list) return 0;
    return ((0==list->tail)?0:list->tail->data);
}

/*return 1 is list is empty*/
int LIST_IsEmpty(List *list)
{
    if(0==list || 0==list->head) return 0;
    else return 1;
}

/*return the number of items in the list*/
int LIST_Count(List *list)
{
    int num;
    ListNode *p;

    if(0==list) return -1;

    num = 0;
    p = list->head;
    while(p){
        p = p->next;
        num++;
    }
    return num;
}

/*return the number of occurrences of 'value' in the list*/
int LIST_ValueCount(List *list, void *value)
{
    int num;
    ListNode *p;

    if(0==list) return -1;

    num = 0;
    p = list->head;
    while(p){
        if(0==memcmp(value,p->data,list->size)) num++;
        p = p->next;
    }
    return num;
}

/*return the index position of the frist occurrence of 'value' in the list*/
int MIST_Indexof(List *list, void *value)
{
    int num;
    ListNode *p;

    if(0==list) return -1;

    num = 0;
    p = list->head;
    while(p){
        if(0==memcmp(value,p->data,list->size)) return num;
        p = p->next;
        num++;
    }
    return -1;
}

/*search Str*/
void* MListSearchStr(List *list, char *value ,int offset)
{
    ListNode *p;
    char *str;

    if(0==list || 0==list->head || 0==value || 0>offset) return 0;

    p = list->head;
    while(p){
        str = p->data;
        str += offset;
        str = *(char**)str;
        if(0==strcmp(str,value)) return p->data;
        p = p->next;
    }

    return 0;
}

/*search int*/
void* MListSearchInt(List *list, int value ,int offset)
{
    ListNode *p;
    char *cp;

    if(0==list || 0==list->head || 0==value || 0>offset) return 0;

    p = list->head;
    while(p){
        cp = p->data;
        cp += offset;

        if(*(int*)cp == value) return p->data;
        p = p->next;
    }

    return 0;
}
