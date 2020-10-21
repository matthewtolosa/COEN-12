#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "set.h"
#include <stdbool.h>

//ask about malloc error 

typedef struct set
{
	char* flag;
	char** data;
	int length;
	int count; 
}SET;

//hash function
static unsigned strhash(char*s)
{
        unsigned hash = 0;
        while(*s!= '\0')
        {
                hash = (31 * hash + *s++);
        }
        return hash;
}


//O(1)
SET* createSet(int maxElts)
{
	int i;
	SET*sp;
	sp = malloc(sizeof(SET));	//allocates space for memory 
	assert(sp!=NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(char*)*maxElts);	
	assert(sp-> data!= NULL);
	sp->flag = malloc(sizeof(char)*maxElts);
	assert(sp->flag!=NULL);	
	sp->length = maxElts;
	for (i=0; i<sp->length; i++)
	{
		sp->flag[i] = 'E';
	}
	return sp;
}

//O(logn)
static int search(SET*sp, char*elt, bool*found)
{
	int i, start;
	*found = false; //not sure if this is the issue 
	int deletedidx = -1;
	start = strhash(elt)%sp->length;
	for(i= 0; i< sp->length; i++)
	{
		int idx = (start + i)%sp->length;
		if(sp->flag[idx] == 'F')
		{
			if(strcmp(sp->data[idx], elt)==0)
			{
				*found = true;
				return idx;
			}
		}
		else if (sp->flag[idx] == 'D')
		{
			if(deletedidx == -1)
			{
				deletedidx = idx;
			}
		}
		else if (sp->flag[idx] == 'E')
		{
			if(deletedidx != -1)
			{
				return deletedidx;
			}
			return idx;
		}
	}
	return deletedidx;//could be return deletedidx
}
                  

//O(n)
//destroys the set 
void destroySet(SET *sp)
{
	int i;
	assert(sp!=NULL); //assert to make sure that the pointer isn't pointing to garbage
	for(i=0; i<sp->length; i++)
	{
		free(sp->data[i]); //frees the actual strings at their addresses 
	}
	free(sp->data);//frees the data memory in the array 
	free(sp->flag);
	free(sp);//frees the pointer 
}

//O(n)
void addElement(SET *sp, char *elt)
{
	assert(sp!=NULL);
	bool found;
	int idx = search(sp, elt,&found);
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
		sp->data[idx] = strdup(elt); //adds the element if it passes the tests 
		sp->flag[idx] = 'F';
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
	if(found == true)
	{
		sp->flag[idx] = 'D';
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
	int i;
	char **elts;	//char ** temp pointer 
	elts = malloc(sizeof(char*)*sp->count);	//allocate memory space for this double pointer
	assert(elts!=NULL);
	for(i=0; i<sp->length;i++)
	{
		if(sp->flag[i] == 'F')
		{
			elts[i] = sp->data[i];
		}
	}
	return elts; 
}









