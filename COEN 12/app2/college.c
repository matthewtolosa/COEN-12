#include <stdlib.h> 
#include <stdio.h>
#include "dataset.h"
#include <time.h>
#define MAXSTUDENTS 3000

int main(void)
{

	INFO *app2;
	app2 = createDataSet(MAXSTUDENTS);
	srand(time(NULL));	
	int studentRecord;
	bool found;
	
	int prevId = 0;
	for(studentRecord=0; studentRecord<1000;studentRecord++)
	{ 
		int randAge = (rand()%13) +18;
		int oneOrTwo = (rand()%2) + 1;
		prevId += oneOrTwo;
		insertion(app2, prevId, randAge);
	}


	int randId = (rand()%2000) +1;
	searchID(app2,randId, &found);//do I need to put an '&' here? 
	
	int deletedId = (rand()%2000) +1;
	printf("Deletion call: Student Being Deleted With ID: %d\n", deletedId);	
	deletion(app2, deletedId);
	
	//destroyDataSet(app2);
}
