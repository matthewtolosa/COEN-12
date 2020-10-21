#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "dataset.h"

typedef struct student //create a student struct 
{
	int id;
	int age;
}STUDENT;

typedef struct info 
{
	int length;
	int count;
	STUDENT **stuArray;
}INFO;


INFO *createDataSet(int maxStudents)
{
	INFO *ip;
	ip = malloc(sizeof(INFO));
	assert(ip!=NULL);
	ip->length = maxStudents;
	ip->count = 0;
	ip->stuArray = malloc(sizeof(STUDENT*)*maxStudents);
	assert(ip->stuArray!=NULL);
	return ip;
}

void destroyDataSet(INFO *ip)
{
	assert(ip!=NULL);
	int i;
	for(i=0; i<ip->length; i++) //traverse through each index of the student array 
	{
		free(ip->stuArray[i]);
	}
	free(ip->stuArray); //free the array structure 
	free(ip); //free the student pointer 
}

int searchAge(INFO *ip, int age, bool *found) //return the idx of where you find the student with the given age 
{
	int low, high, mid; //its a sorted array, thus use binary search
	*found = false;
	printf("Searching for Student(s) with Age: %d\n",age);
	low = 0;
	high = ip->count -1;
	while(low <= high)
	{
		mid = (high + low)/2;
		if(age == ip->stuArray[mid]->age) //if found found is true and return the mid idx
		{
			*found = true;
			//printf("Student found!\n");
			return mid;
		}	
		else if (age < ip->stuArray[mid]->age) //if given age is less than the age at the mid idx than the high idx goes to mid -1
		{
			high = mid - 1;
		}
		else if (age > ip->stuArray[mid]->age) //if given age is more than the age at the mid idx than the low gets mid mid +1
		{
			low = mid + 1;
		}
	}
	//printf("Student not found with given age\n");
	return low; //if not found, then just return the low idx 
}


void insertion(INFO *ip,int id, int age)
{
	assert(ip!=NULL);
	bool found;
	int idx = searchAge(ip, age, &found); 
	int i;
	if(ip->length <= ip->count) //cant add if the length is less than the count(number of students in the array)
	{
		return;
	}
	else 
	{
		for(i=ip->count; i>idx; i--)
		{
			ip->stuArray[i] = malloc(sizeof(int));
			ip->stuArray[i]->age = ip->stuArray[i-1]->age;
			ip->stuArray[i]->id = ip->stuArray[i-1]->id;
		}	
		ip->stuArray[idx] = malloc(sizeof(int));
		ip->stuArray[idx]->age = age;
		ip->stuArray[idx]->id = id;
		ip->count++;
	//	printf("Student added\n");
		
	}
}

void deletion(INFO *ip, int age)
{
	assert(ip!=NULL);
	int idx, minIdx, maxIdx, i, deletions, initialCount, newCount;
	bool found;
	idx = searchAge(ip, age, &found);
	minIdx = idx;
	maxIdx = idx;
	initialCount = ip->count;
	deletions = 0;
	if(found == false)
	{	
		printf("Student not found\n");
		return;
	}
	else 
	{
		
		printf("Student found\n");
		printf("Student Being Deleted: Age: %d ID: %d\n",ip->stuArray[idx]->age,ip->stuArray[idx]->id);
		for(i=idx-1; i >= 0; i--)
		{
			if(ip->stuArray[i]->age == age)
				minIdx = i; 
			else
				break;	
		}
		for(i = idx+1; i<ip->count; i++)
		{
			if(ip->stuArray[i]->age == age)
				maxIdx = i;
			else
				break;
		}

		for(i = minIdx; i <=maxIdx; i++)
		{
			free(ip->stuArray[i]);
			deletions++;
		}
		for(i = 0; i<((ip->count-1)-maxIdx);i++)
		{
			ip->stuArray[i+minIdx] = ip->stuArray[i+(maxIdx+1)];
		}
		ip->count -= deletions;
		printf("Deletion(s) Done Successfully: %d\n",deletions);
		printf("Count After Deletion(s): %d\n",ip->count);
	}

			
}

/*This was a print function which prints out the id and age at each
 * index*/

/*void printArray(INFO *ip)
{
	int i;
	for(i=0; i<100; i++)
	{
		printf("[%d]: Age: %d ID: %d\n",i, ip->stuArray[i]->age,ip->stuArray[i]->id);
	}
}*/

int maxAgeGap(INFO *ip)
{
	int ageGap;
	ageGap = ((ip->stuArray[ip->count-1]->age) - (ip->stuArray[0]->age));
	printf("Current Max Age Gap: %d\n", ageGap);
	return ageGap;
}
