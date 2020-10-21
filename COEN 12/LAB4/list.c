#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"
#include "set.h"



typedef struct list
{
	int count;
	struct node *head;
	int(*compare)();
	
}LIST;

typedef struct node 
{
	struct node *next;
	struct node *prev;
	void* data;
}NODE;


//O(1)
extern LIST *createList(int (*compare)())
{
	struct list *lp;
	lp = malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->count = 0;
	lp->compare = compare;
	lp->head = malloc(sizeof(NODE));
	assert(lp->head!= NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;
}

           
//O(n)
//destroys the set 
extern void destroyList(LIST *lp)
{
	assert(lp!=NULL); //assert to make sure that the pointer isn't pointing to garbage
	NODE *pDel = lp->head->prev;
	NODE *pPrev;
	while(pDel!= lp->head) //start deleting from last element/node until you reach the head
	{
		pPrev = pDel->prev; //make sure that you keep track of the rest of the list 
		free(pDel);
		pDel = pPrev;	//update pDel to get what pPrev has 
	}
	free(pDel); //deletes the head 
	free(lp);
}

//O(n)
extern void addFirst(LIST *lp, void *item)
{
	NODE *pNew = malloc(sizeof(NODE));
	assert(pNew!=NULL);
	pNew->data = item;
	pNew->next = lp->head->next;
	pNew->prev = lp->head;
	lp->head->next = pNew;
	pNew->next->prev = pNew;
	lp->count++; 
}

 	

//O(1)
extern int numItems(LIST *lp)
{
	return lp->count; //return count, number of strings in the data structure 
}

//O(n)
extern void addLast(LIST *lp, void *item)
{
	assert(lp!=NULL);
	NODE *pNew = malloc(sizeof(NODE));
	assert(pNew!=NULL);
	pNew->data = item;
	pNew->prev = lp->head->prev;
	pNew->next = lp->head;
	lp->head->prev->next = pNew;
	lp->head->prev = pNew;
	lp->count++;
}

extern void *removeFirst(LIST *lp)
{
	assert(lp!=NULL);
	NODE *pDel;
	pDel = lp->head->next; 
	pDel->next->prev = lp->head; 
	lp->head->next = pDel->next;
	free(pDel);
	lp->count--;
	return pDel->data;		
}

extern void *removeLast(LIST *lp)
{
	assert(lp!=NULL);
	NODE *pDel;
	NODE *pPrev;
	pPrev = lp->head->prev->prev;
	pDel = lp->head->prev;
	pPrev->next = lp->head;
	lp->head->prev = pPrev;
	free(pDel);
	lp->count--;
	return pDel->data;
}
	
extern void *getFirst(LIST *lp)
{
	assert(lp!=NULL);
	NODE *pCur;
	pCur =  lp->head->next;
	return pCur->data;
}

extern void *getLast(LIST *lp)
{
	assert(lp!=NULL);
	NODE *pCur;
	pCur = lp->head->prev;
	return pCur->data; 
}

extern void removeItem(LIST *lp, void *item)
{
	assert(lp!= NULL);
	NODE *pCur = lp->head->next;
	bool found = false;
	while(pCur!= lp->head)
	{
		if((*lp->compare)(item,pCur->data)==0)

		{
			found = true; 
			break;
		}
		pCur = pCur->next;
	}
	
	if (found==false)
	{
		return;
	}
	pCur->next->prev = pCur->prev;
	pCur->prev->next = pCur->next;
	free(pCur);
	lp->count--;
}

extern void *findItem(LIST *lp, void *item)
{
	assert(lp!=NULL);
	NODE *pCur = lp->head->next;
	while(pCur != lp->head)
	{
		if((*lp->compare)(item, pCur->data)==0)
		{
			return pCur->data;	
		}
		pCur = pCur->next; 
	}
		
	return NULL;
}

extern void *getItems(LIST *lp)
{
	assert(lp!=NULL);
	int i = 0;
	NODE *pCur = lp->head->next;
        void **items;    						  //void ** temp pointer
        items = malloc(sizeof(void*)*lp->count); //allocate memory space for this double pointer
        assert(items!=NULL);
//        printf("Before\n");
	while (pCur != lp->head)
	{
		items[i] = pCur->data;
		i++;	
		pCur = pCur->next;
	}
//	printf("After\n");
        return items;	
}
























