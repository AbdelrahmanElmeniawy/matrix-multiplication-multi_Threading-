#include "header.h"

int main(int argc, char *argv[])
{
    // get args and open files
    FILE *fileA, *fileB, *fileOut;
    if (argc == 4){
        fileA = fopen(argv[1], "r");
        fileB = fopen(argv[2], "r");
        fileOut = fopen(argv[3], "w");
    } else {
        fileA = fopen("a.txt", "r");
        fileB = fopen("b.txt", "r");
        fileOut = fopen("c.out", "w");
    }
    if(fileA == NULL || fileB == NULL || fileOut == NULL){
        printf("failed to open files!\n");
        return 0;
    }

    // read the input matrices from files
    int **matA, **matB;
    int rowA, colA, rowB, colB;
    matA = readMat(fileA, &rowA, &colA);
    matB = readMat(fileB, &rowB, &colB);

    // save the data in one data structure for easier using
    m1struct *maindata = malloc(sizeof(m1struct));
    maindata->matA = matA; maindata->matB = matB;
    maindata->rowA = rowA; maindata->rowB = rowB;
    maindata->colA = colA; maindata->colB = colB;
    maindata->out = fileOut;

    // apply the the 3 methods
    method1(maindata);
    method2(maindata);
    method3(maindata);

    // close files opened
    fclose(fileA);
    fclose(fileB);
    fclose(fileOut);

    // free memory allocated
    for(int i = 0; i < rowA; i++){
        free(matA[i]);
    }
    free(matA);
    for(int i = 0; i < rowB; i++){
        free(matB[i]);
    }
    free(matB);
    free(maindata);
    return 0;
}

int** readMat(FILE* file, int *row, int *col){
    // read matrix dimensions
    while(fgetc(file) != '='){}
    fscanf(file, "%d", row);
    while(fgetc(file) != '='){}
    fscanf(file, "%d", col);

    // read matrix elements
    int **mat = malloc(sizeof(int*) * (*row));
    for(int i = 0; i < *row; i++){
        mat[i] = malloc(sizeof(int) * (*col));
        for(int j = 0; j < *col; j++){
            fscanf(file, "%d", &mat[i][j]);
        }
    }
    return mat;
}

