#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "dataset.h"


typedef struct student
{
	int age;
	int id;
}STUDENT;

typedef struct info
{
	int length;
	int count;
	STUDENT **stuArray;
}INFO;

INFO *createDataSet(int maxStudents)
{
//	printf("Before CreateSet in app2\n");
	INFO *ip;
	ip = malloc(sizeof(INFO));
	assert(ip!=NULL);
	ip->count = 0;
	ip->length = maxStudents;
	ip->stuArray = malloc(sizeof(STUDENT*)*maxStudents);
	assert(ip->stuArray!=NULL);
//	printf("After CreateSet in app2\n");
	return ip;
}

void destroyDataSet(INFO *ip)
{
	int i;
	assert(ip!=NULL);
	for(i=0; i<ip->length; i++)
	{
		free(ip->stuArray[i]);
	}
	free(ip->stuArray);
	free(ip);
}


int searchID(INFO *ip, int id, bool *found)
{	
	int high, low, mid;
	*found = false;
	low = 0;
	high = ip->count-1;
	printf("Searching for Student(s) with ID: %d\n",id);
	while(low <= high)
	{
		mid = (high + low)/2;
		if(id == ip->stuArray[mid]->id)
		{
			*found = true;
			return mid;
		}
		else if (id < ip->stuArray[mid]->id)
		{
			high = mid -1;
		}		
		else if(id > ip->stuArray[mid]->id)
		{
			low = mid + 1;
		}
	}
	//printf("Student with that ID wasn't found\n");
	return low;
}

void insertion(INFO *ip, int id, int age)
{
	assert(ip!=NULL); 
	int i, idx;
	bool found;
	idx = searchID(ip,id,&found);
	if(ip->length <= ip->count)
		return;
	else
	{
		for(i=ip->count; i>idx; i--)
		{
			ip->stuArray[i] = malloc(sizeof(int));
			ip->stuArray[i]->age = ip->stuArray[i-1]->age;
			ip->stuArray[i]->id = ip->stuArray[i-1]->id;
		}
		ip->stuArray[i] = malloc(sizeof(int));
		ip->stuArray[idx]->age = age;
		ip->stuArray[idx]->id = id;
		ip->count++;
	}
}


void deletion(INFO *ip, int id)
{
	assert(ip!=NULL);
	int i, j, idx;
	bool found;
	idx = searchID(ip, id, &found);
	if (found == false)
	{
		printf("Student with that ID couldn't be found\n");
		return;
	}
	else
	{
		printf("Student Being Deleted: ID: %d Age: %d\n",ip->stuArray[idx]->id,ip->stuArray[idx]->age); 
		for(i=idx; i<(ip->count) -1; i++)
		{
			ip->stuArray[i]->id = ip->stuArray[i+1]->id;
		}
		ip->count--;
		printf("Deletion was done successfully!\n");
		printf("Count after deletion: %d\n", ip->count);
	}
}
