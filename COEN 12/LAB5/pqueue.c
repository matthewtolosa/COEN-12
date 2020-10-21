#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h" 
#define p(x)((x-1)/2)
#define l(x)((2*x)+1)
#define r(x)((2*x)+2)




typedef struct pqueue 
{
	int count;
	int length;
	void **data;
	int (*compare)();
}PQ;


//Big O = O(1)
PQ *createQueue(int (*compare)()) //create queue
{
	PQ *pq; 
	pq = malloc(sizeof(PQ));
	assert(pq !=NULL);
	pq->count = 0;
	pq->length = 10;
	pq->compare = compare; 
	pq->data = malloc(sizeof(void*)*pq->length);
	assert(pq->data!=NULL);
	return pq;
}

//Big O = O(1)
void destroyQueue(PQ *pq) //destroy the data** and then free the pointer
{
	assert(pq!=NULL);
	free(pq->data);
	free(pq);
}

//Big O = O(1)
int numEntries (PQ *pq)//return the number of entries
{
	assert(pq!=NULL);
	return pq->count;
}

//Big O = O(logn)
void addEntry(PQ *pq, void *entry)
{
	if(pq->count == pq->length) //reallocate space of the array is full 
	{
		pq->data = realloc(pq->data, sizeof(void*)*(2*pq->length));
		assert(pq!=NULL);
		pq->length = pq->length*2;	
	}
	pq->data[pq->count] = entry; //insert new entry as a leaf 
	int idx = pq->count;
	pq->count++;
	void *temp;
	
	while((pq->data[p(idx)] >= 0 && (*pq->compare)(pq->data[idx] , pq->data[(p(idx))]) == -1)) //make comparisons 
	{
		temp = pq->data[idx];
		pq->data[idx] = pq->data[p(idx)];
		pq->data[p(idx)] = temp;
		idx = p(idx);
	}
}

//Big O = O(logn)
void *removeEntry(PQ *pq)
{
	assert(pq!=NULL);
	
	if(pq->count == 0)
	{
		return NULL;
	}

	void *temp;
	void *delItem = pq->data[0];
	pq->data[0] = pq->data[pq->count-1];
	int idx = 0;
	
	
	while(l(idx) < pq->count-1)
	{
		//check to see if you have a right child 
		if (r(idx) < pq->count)
		{
			if((*pq->compare)(pq->data[l(idx)], pq->data[r(idx)]) <= 0) //compare the left child since it's smaller 
			{
			//compare that the right child is smaller than the parent, then proceed swap if not smaller than break   
				if((*pq->compare)(pq->data[l(idx)], pq->data[idx]) < 0)
				{
					temp = pq->data[l(idx)];
                			pq->data[l(idx)] = pq->data[idx];
                			pq->data[idx] = temp;
                			idx = l(idx);
				}//break because the left isnt less than the parent 
				else
					break;
			}
			else if ((*pq->compare)(pq->data[l(idx)], pq->data[r(idx)]) > 0) //compare the right child since it's smaller
			{
			//compare that the left child is smaller than the parent, then proceed to swap if not smaller than break  
				if((*pq->compare)(pq->data[r(idx)], pq->data[idx]) < 0)
				{
					temp = pq->data[r(idx)];
                        		pq->data[r(idx)] = pq->data[idx];
                        		pq->data[idx] = temp;
                        		idx = r(idx);
				}//break because the right isnt less than the parent
				else 
					break;
			}
		}//only a left child, so compare the left child to its parent	 
		else if((*pq->compare)(pq->data[l(idx)],pq->data[idx]) < 0)
		{
			temp = pq->data[l(idx)];
                       	pq->data[l(idx)] = pq->data[idx];
                       	pq->data[idx] = temp;
                     	idx = l(idx);
		}
		else
			break;
	
	}
	pq->count--;
	return delItem;
}
