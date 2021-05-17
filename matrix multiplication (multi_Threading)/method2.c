#include "header.h"

m1struct data;
int **matOut;
void *matMult2(void * index);

void method2(void *maindata){
    data = *(m1struct *) maindata;
    //creating threads array
    pthread_t threads[data.rowA];
    int threadsNum = 0;

    struct timeval stop, start;
    gettimeofday(&start, NULL); //start checking time
    matOut = malloc(sizeof(int *) * data.rowA);
    for(int i = 0; i < data.rowA; i++){
        int * temp = malloc(sizeof(int));
        *temp = i;
        //creating threads for each row
        if (pthread_create(&threads[i], NULL, matMult2, (void *) temp)){
            printf("ERROR!\n");
        }
    }
    for(int i = 0; i < data.rowA; i++){
        //thread join
        pthread_join(threads[i], NULL);
        threadsNum++;
    }
    gettimeofday(&stop, NULL); //end checking time

    // printing on the file
    fprintf(data.out,"----------------------------------------------------------------------------\nMethod 2:\n-------------\n");
    for(int i = 0; i < data.rowA; i++){
        for(int j = 0; j < data.colB; j++){
            fprintf(data.out,"%d\t", matOut[i][j]);
        }
        fprintf(data.out,"\n");
    }
    fprintf(data.out,"Number of threads %d \n", threadsNum);
    fprintf(data.out,"Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    fprintf(data.out,"Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);
    // free memory allocated
    for(int i = 0; i < data.rowA; i++){
        free(matOut[i]);
    }
    free(matOut);
}

// function that works on threads
void *matMult2(void *index){
    int i = *(int*)index;
    matOut[i] = malloc(sizeof(int) * data.colB);
    for(int j = 0; j < data.colB; j++){
        matOut[i][j] = 0;
        for(int k = 0; k < data.rowB; k++){
            matOut[i][j] += data.matA[i][k] * data.matB[k][j];
        }
    }
    pthread_exit(NULL);
}
