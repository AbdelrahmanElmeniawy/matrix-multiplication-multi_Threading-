#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

// data structure that contain the main data
typedef struct m1struct{
    int **matA, **matB;
    int rowA, colA, rowB, colB;
    FILE *out;
}m1struct;

typedef struct m3struct{
    int i, j;
}element;


void method1(void *maindata);
void method2(void *maindata);
void method3(void *maindata);
int **readMat(FILE* file, int *row, int *col);
