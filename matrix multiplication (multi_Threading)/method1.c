#include "header.h"

m1struct data;
int **matOut;
void *matMult1();

void method1(void *maindata){
    data = *(m1struct *) maindata;
    pthread_t thread;
    int threadsNum = 1;
    struct timeval stop, start;
    gettimeofday(&start, NULL); //start checking time
    //creating thread
    if (pthread_create(&thread, NULL, matMult1, NULL)){
        printf("ERROR!\n");
    }
    //thread join
    pthread_join(thread, NULL);
    gettimeofday(&stop, NULL); //end checking time

    //printing in the file
    fprintf(data.out,"Method 1:\n-------------\n");
    for(int i = 0; i < data.rowA; i++){
        for(int j = 0; j < data.colB; j++){
            fprintf(data.out,"%d\t", matOut[i][j]);
        }
        fprintf(data.out,"\n");
    }
    fprintf(data.out,"Number of threads %d \n", threadsNum);
    fprintf(data.out,"Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    fprintf(data.out,"Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);
    //free memory allocated
    for(int i = 0; i < data.rowA; i++){
        free(matOut[i]);
    }
    free(matOut);
}

//function that works on threads
void *matMult1(){
    matOut = malloc(sizeof(int *) * data.rowA);
    for(int i = 0; i < data.rowA; i++){
        matOut[i] = malloc(sizeof(int) * data.colB);
        for(int j = 0; j < data.colB; j++){
            matOut[i][j] = 0;
            for(int k = 0; k < data.rowB; k++){
                matOut[i][j] += data.matA[i][k] * data.matB[k][j];
            }
        }
    }
    pthread_exit(NULL);
}
