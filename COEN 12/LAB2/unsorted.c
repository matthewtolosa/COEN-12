#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "set.h"


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

//O(n)
static int search(SET*sp, char*elt)
{
	int i;
	for(i=0; i< sp->count;i++)	//iterates through the strings in the data structure 
	{
		if(strcmp(sp->data[i],elt)==0)		//compares strings to entered element to see if they're the same 
		{
			return i;
		}
	}
	return -1;
		

}

//O(1)
//destroys the set 
void destroySet(SET *sp)
{
	int i;
	assert(sp!=NULL); //assert to make sure that the pointer isn't pointing to garbage
	for(i=0; i<sp-> count; i++)
	{
		free(sp->data[i]); //frees the actual strings at their addresses 
	}
	free(sp->data);//frees the data memory in the array 
	free(sp);//frees the pointer 
}

//O(n)
void addElement(SET *sp, char *elt)
{
	int i;
	if(sp->length<sp->count) //checks to make sure there is space to add an element 
	{
		return;
	}
	if(search(sp,elt)!=-1) //checks to make sure there are no duplicates 
	{
		return;
	}	
	else 
	{
		sp->data[sp->count] = strdup(elt); //adds the element if it passes the tests 
		sp -> count++; //increment count 
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
	int index = search(sp, elt);
	if(index == -1)
	{
		return;	//element wasn't found so it can't remove anything 
	}
	else
	{
		free(sp->data[index]);	//frees the string at that spot 
		sp->data[index] = sp->data[(sp->count)-1];	//moves string in the last spot of the array to the spot that was deleted 
		sp->count--;
	}
}

//O(n)
char *findElement(SET *sp, char *elt)
{
	int i = search(sp, elt);
	if(i != -1)
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









