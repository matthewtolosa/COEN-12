#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "set.h"
#include "list.h"


//O(1)


typedef struct set {
    int count;
    int length;
    LIST **lists;
    int (*compare)();
    unsigned (*hash)();
}SET;



//O(n)
extern SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) 
{
    SET *sp;
    int i;
    assert(compare!=NULL && hash!=NULL);
    sp=malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count=0;
    sp->compare=compare;
    sp->length=maxElts/20;
    sp->hash=hash;
    sp->lists = malloc (sizeof(LIST*)*(sp->length));
    assert(sp->lists!=NULL);
	for(i=0;i<sp->length;i++)
    	{
 		sp->lists[i] = createList(compare);
	}

    return sp;
}

//O(n)
void destroySet(SET *sp) 
{
    assert(sp!=NULL);
    int i;
    for(i=0;i<sp->length;i++) 
    {
        destroyList(sp->lists[i]);
    }
    free(sp->lists);
    free(sp);
}

//O(1)
int numElements(SET *sp) 
{
    assert(sp!=NULL);
    return sp->count;
}

//O(1)
void *findElement(SET *sp, void *elt) 
{
    assert(sp!=NULL);
    unsigned key = (*sp->hash)(elt);
    assert(key >= 0);
    int idx= key%(sp->length);
    return findItem(sp->lists[idx], elt);
}

//O(1)
void addElement(SET *sp, void *elt) 
{
    assert(sp!=NULL);
    assert(sp->lists!=NULL);
    unsigned key = (*sp->hash)(elt);
    int idx = key%(sp->length); 
    void *found = findItem(sp->lists[idx], elt);
    if(found==NULL) 
    {
        addLast(sp->lists[idx], elt);
        sp->count++;
    }
}

//O(1)
void removeElement(SET *sp, void* elt) 
{
    assert(sp!=NULL); 
    assert(sp->lists!=NULL);
    unsigned key = (*sp->hash)(elt);
    int idx = key%sp->length;
    void *found = findItem(sp->lists[idx], elt);
    if(found!=NULL) 
    {
        removeItem(sp->lists[idx], elt);
        sp->count--;
    }
}

//O(1)
void *getElements(SET *sp) 
{
	assert(sp!=NULL);
	void **item;
 	void **elts;
	int i;
	int j = 0;
	elts = malloc(sizeof(void*)*sp->count);
	assert(elts!=NULL);
	for(i=0; i<sp->length;i++)
	{
		item = getItems(sp->lists[i]);
		 memcpy(elts +j, item, sizeof(void*)*numItems(sp->lists[i]));
		j = j+ numItems(sp->lists[i]);
	}
	return elts;
}	   






