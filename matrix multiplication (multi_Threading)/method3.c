#include "header.h"

m1struct data;
int **matOut;
void *matMult3(void * pont);

void method3(void *maindata){
    data = *(m1struct *) maindata;
    //creating threads array
    pthread_t threads[data.rowA * data.colB];
    int threadsNum = 0;

    struct timeval stop, start;
    gettimeofday(&start, NULL); //start checking time

    int k = 0;
    matOut = malloc(sizeof(int *) * data.rowA);
    for(int i = 0; i < data.rowA; i++){
        matOut[i] = malloc(sizeof(int) * data.colB);
        for(int j = 0; j < data.colB; j++){
            element *pont = malloc(sizeof(element));
            pont->i = i; pont->j = j;
            // creating thread for every element in the output matrix
            if (pthread_create(&threads[k], NULL, matMult3, (void *) pont)){
                printf("ERROR!\n");
            }
            k++;
        }
    }
    k = 0;
    for(int i = 0; i < data.rowA; i++){
        for(int j = 0; j < data.colB; j++){
            // thread join
            pthread_join(threads[k], NULL);
            threadsNum++;
            k++;
        }
    }
    gettimeofday(&stop, NULL); //end checking time
    // printing on the file
    fprintf(data.out,"----------------------------------------------------------------------------\nMethod 3:\n-------------\n");
    for(int i = 0; i < data.rowA; i++){
        for(int j = 0; j < data.colB; j++){
            fprintf(data.out,"%d\t", matOut[i][j]);
        }
        fprintf(data.out,"\n");
    }
    fprintf(data.out,"Number of threads %d \n", threadsNum);
    fprintf(data.out,"Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    fprintf(data.out,"Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);
    // free the memory allocated
    for(int i = 0; i < data.rowA; i++){
        free(matOut[i]);
    }
    free(matOut);
}

//method that works on threads
void *matMult3(void *pont){
    element temp = *(element*) pont;
    int i = temp.i, j = temp.j;
    matOut[i][j] = 0;
    for(int k = 0; k < data.rowB; k++){
        matOut[i][j] += data.matA[i][k] * data.matB[k][j];
    }
    pthread_exit(NULL);
}
