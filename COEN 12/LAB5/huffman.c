#include <stdlib.h>
#include <stdio.h> 
#include <assert.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"


//Big O = O(1)
struct node *mknode(int data, struct node *left, struct node *right)
{	
	struct node *pNode = malloc(sizeof(struct node)); //allocate memory
	assert(pNode!=NULL);
	pNode->parent = NULL;//parent node initially needs to be NULL
	pNode->count = data;
	if(left !=NULL && right !=NULL)
	{
		left->parent = pNode;//make left and right point to parent
		right->parent = pNode;
	}	
	return pNode;
}

//Big O = O(1)
int depth(struct node *child)
{        
	int pCur;
	if(child->parent == NULL)//until the child doesnt have a parent return 
	{
		return 0; 
	}	
	return pCur = ( 1 + depth(child->parent));//keep adding 1 until you get to a node w/o a parent
}

//Big O = O(1)
int nodecmp(struct node *left, struct node *right)
{
	if( left->count < right->count) //comparing the left and right children
	{
		return -1;
	}
	if(right->count < left->count)
	{
		return 1;
	}
	return 0;
}



int main (int argc, char *argv[])
{
	assert(argc == 3);
	int frequency[257];
	int i, k, l, m;
	struct node *leafNodes[257];
	FILE *fp;
	//Big O = O(n)
	for(l=0; l <257; l++)
	{
		frequency[l] = 0;//initializes the frequencies to 0 
	} 
	
	fp = fopen(argv[1], "r");
	
	if(fp == NULL)
	{
		printf("File cannot be opened\n");
		return 0;
	}
	//Big O = O(n)
	while((m = getc(fp)) != EOF)//incrementing the frequencies of each character in the file 
	{
		frequency[m]++;	
	}
	
	fclose(fp);
	
	PQ *pq;
	pq = createQueue(nodecmp);
	//Big O = O(n)
	
	for(i=0; i<256;i++)//putting the frequencies into the tree
	{
		if(frequency[i] > 0)
		{
			leafNodes[i] = mknode(frequency[i], NULL, NULL);
			addEntry(pq, leafNodes[i]);
		}
		else 
		{
			leafNodes[i] = NULL;
		}
		
	}

	leafNodes[256] = mknode(0, NULL, NULL);
	addEntry(pq, leafNodes[256]);	


	
	//Big O = O(n)
	while(numEntries(pq) > 1)//Bringing together all the leaf nodes and combining them to make parent nodes
	{
		struct node *n1;
		struct node *n2;
		struct node *pNode;
		n1 = removeEntry(pq);
		n2 = removeEntry(pq);
		pNode = mknode(n1->count + n2->count,n1, n2);
		addEntry(pq, pNode);
	}
	//Big O = O(n)

	for(k=0; k<257; k++)
	{
		if(leafNodes[k] != NULL)
		{ 
			int data = depth(leafNodes[k]);
			int size =  data*frequency[k];
			(isprint(k) == 0) ? printf("%o",k) : printf("'%c'" ,k);
			printf(":%d x %d bits = %d bits\n", frequency[k],data,size);
		}
	}
	
	pack(argv[1], argv[2], leafNodes);
	return 0;
}

