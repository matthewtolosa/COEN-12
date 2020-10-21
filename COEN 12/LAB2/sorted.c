#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "set.h"
#include <stdbool.h>

typedef struct set
{
	char** data;
	int length;
	int count; 
}SET;


//O(1)
SET* createSet(int maxElts)
{
	SET*sp;
	sp = malloc(sizeof(SET));	//allocates space for memory 
	assert(sp!=NULL);
	sp -> count = 0;
	sp -> length = maxElts;
	sp -> data = malloc(sizeof(char*)*maxElts);	
	assert(sp -> data!= NULL);
	sp->length = maxElts;
	return sp;
}

//O(logn)
static int search(SET*sp, char*elt, bool*found)
{
	int low = 0;
	int high = sp -> count-1;
	int  mid;
	*found = false; 
	while (low <= high)
	{
		mid = (high + low)/2;
		if(strcmp(sp->data[mid],elt) == 0)
		{
			*found = true;
			return mid; 
		}
		else if(strcmp(sp->data[mid], elt) < 0)
		{
			low = mid + 1;
		}
		else if (strcmp(sp->data[mid], elt) > 0)
		{
			high = mid - 1;
		}

	}
	return low;
		
}

//O(n)
//destroys the set 
void destroySet(SET *sp)
{
	int i;
	assert(sp!=NULL); //assert to make sure that the pointer isn't pointing to garbage
	for(i=0; i<sp->count; i++)
	{
		free(sp->data[i]); //frees the actual strings at their addresses 
	}
	free(sp->data);//frees the data memory in the array 
	free(sp);//frees the pointer 
}

//O(n)
void addElement(SET *sp, char *elt)
{
	assert(sp!=NULL);
	bool found;
	int idx = search(sp, elt,&found);
	int i;
	if(sp->length<=sp->count) //checks to make sure there is space to add an element 
	{
		return;
	}
	if(found == true) //checks to make sure there are no duplicates 
	{
		return;
	}	
	else 
	{
		for (i=sp->count; i>idx; i--)
		{
			sp->data[i] = sp->data[i-1];
		}
		sp->data[idx] = strdup(elt); //adds the element if it passes the tests 
		sp->count++; //increment count 
	}
} 	

//O(1)
int numElements(SET *sp)
{
	return sp->count; //return count, number of strings in the data structure 
}

//O(n)
void removeElement(SET *sp, char *elt)
{
	assert(sp!=NULL);
	bool found;
	int idx = search(sp, elt, &found);
	int i;
	if(found == true)
	{
		free(sp->data[idx]);	//frees the string at that spot 
		for(i = idx+1; i<sp->count;i++)
		{
			sp->data[i-1] = sp->data[i];
		}
		sp->data[sp->count-1] = NULL; 
		sp->count--;
	}
}

//O(logn)
char *findElement(SET *sp, char *elt)
{
	bool found;
	int i = search(sp, elt, &found);
	if(found == true)
	{
		return sp->data[i];	//returns element at that spot when found 
	}
	return NULL; 
}

//O(1)
char **getElements(SET *sp)
{
	char **sppointer;	//char ** temp pointer 
	sppointer = malloc(sizeof(char**)*sp->count);	//allocate memory space for this double pointer 
	return memcpy(sppointer, sp->data,sizeof(char**)*sp->count);	//copies memory from data pointer to temp pointer 
}









