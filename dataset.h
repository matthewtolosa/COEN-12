//This file contains the public function and type declarations for a dataSet abstract
//for student pointers. 


# ifndef DATASET_H 
# define DATASET_H

#include <stdbool.h>


typedef struct student STUDENT;

typedef struct info INFO;

INFO *createDataSet(int maxStudents);

void destroyDataSet(INFO *ip);

int searchAge(INFO *ip, int age, bool *found);

void insertion(INFO *ip, int id, int age);

void deletion(INFO *ip, int age);

int maxAgeGap(INFO *ip);

//void printArray(INFO *ip);

# endif /* DATASET_H */
