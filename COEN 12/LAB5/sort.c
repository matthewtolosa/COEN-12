/*
 * File:	sort.c
 *
 * Copyright:	2017, Darren C. Atkinson
 *
 * Description:	Read in a sequence of integers from the standard input and
 *		write them in sorted order on the standard output.  The
 *		application works by inserting each integer into a priority
 *		queue ADT and then repeatedly removing the smallest value
 *		from the queue and printing it.
 */

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>
# include "pqueue.h"

/*
 * Function:	intcmp
 *
 * Description:	Given pointers to two integers, compare them as in strcmp.
 */
static int intcmp(int *i1, int *i2)
{
//    printf("Before compare\n");
    return (*i1 < *i2) ? -1 : (*i1 > *i2);

//    printf("After compare\n");
}


/*
 *
 * Description:	Driver function for the sort application.
 */

int main(void)
{
	PQ *pq;
	int *p, x;
	pq = createQueue(intcmp);
		
    
//    printf("Before first while\n");
    while (scanf("%d", &x) == 1) {
	p = malloc(sizeof(int));
	assert(p != NULL);

	*p = x;
	addEntry(pq, p);
    }

//    printf("After first while\n");
 
//    printf("Before second while\n");
    while (numEntries(pq) > 0) {
	p = removeEntry(pq);
	printf("%d\n", *p);
	free(p);
    }

//    printf("After second while\n");    
//    printf("Before destroy\n");
    destroyQueue(pq);

//    printf("After destroy\n");
    exit(EXIT_SUCCESS);

}
