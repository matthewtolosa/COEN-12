//This file contains the public function and type declarations for a student abstract data
//type for student sturct pointers. 

# ifndef DATASET_H
# define DATASET_H
#include <stdbool.h>

typedef struct student STUDENT;

typedef struct info INFO;

INFO *createDataSet(int maxStudents);

void destroyDataSet(INFO *ip);

int searchID(INFO *ip, int id, bool *found);

void insertion(INFO *ip, int id, int age);

void deletion(INFO *ip, int id);

# endif /* DATASET_H */
