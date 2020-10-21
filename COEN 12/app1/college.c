#include <stdlib.h>
#include <stdio.h>
#include "dataset.h"
#define MAXSTUDENTS 3000 
#include <time.h> 
#include <stdbool.h>


main(void)
{
	INFO *app1;
	srand(time(NULL));
//	printf("Before call to createDataSet in college.c\n\n");
	app1 = createDataSet(MAXSTUDENTS);
//	printf("After call to createDataSet in colleg .c\n\n");
	bool found;
	
	int prevId = 0; //set initial id to 0
	int studentRecord;	
	for (studentRecord = 0; studentRecord < 1000; studentRecord++)
	{
		int randAge  = (rand()%13) + 18;
		int oneOrTwo = (rand()%2)+ 1;
		prevId += oneOrTwo;
		insertion(app1,prevId,randAge);
	}

	int ageGenerated = (rand()%13) + 18;
	searchAge(app1,ageGenerated,&found);

	int ageDeleted = (rand()%13)+ 18;
	printf("Deletion Call In Main: %d\n",ageDeleted);
	deletion(app1, ageDeleted);
	
	maxAgeGap(app1);
	//printArray(app1);
	destroyDataSet(app1);
}
