#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ "r"

//Print the supplied matrix
void printMatrix(int* matrix, int k) {
    for (int x = 0; x < k; x++) {
        for (int y = 0; y < k; y++) {
            if(y == k-1) printf("%d", *(matrix + x*k + y));
            else printf("%d ", *(matrix + x*k + y));
        }
        printf("\n");
    }
}

//Recursive matrix multiplication algorithm
int* mexp(int* matrix, int k, int n) {
    int x, y, z;
    if(n == -1) {
        for(x = 0; x < k; ++x) {
            for(y = 0; y < k; ++y) {
                if(x == y) *(matrix + x*k + y) = 1;
                else *(matrix + x*k + y) = 0;
            }
        }
        return matrix;
    }
    int* new;
    if(n == 0) {
        new = (int*)malloc(k * k * sizeof(int));
        memcpy(new, matrix, (k * k * sizeof(int)));
        return new;
    }
    
    new = mexp(matrix, k, n - 1);
    int *result = (int*)malloc(k * k * sizeof(int));
    
    for(x = 0; x < k; ++x) {
        for(y = 0; y < k; ++y) {
            *(result + x*k + y) = 0;
            for(z = 0; z < k; ++z) {
                *(result + x*k + y) += *(matrix + x*k + z) * *(new + z*k + y);
            }
        }
    }
    
    memcpy(new, result, (k * k * sizeof(int)));
    free(result);
    
    return new;
}

int main(int argc, const char * argv[]) {
    //Make sure the program has the correct amount of arguments
    if(argc != 2) {
        printf("USAGE: %s INPUTFILE.TXT\n", argv[0]);
        exit(0);
    }
    
    //Open the file stream in read mode
    FILE *fIn;
    fIn = fopen(argv[1], READ);
    
    //Read in the matrix size
    int k;
    fscanf(fIn, "%d", &k);
    
    //Allocate memory for the 2d array
    int *matrix = (int*)malloc(k * k * sizeof(int));
    
    //Read matrix input into 2d array
    int x, y;
    for (x = 0; x < k; x++) {
        for (y = 0; y < k; y++) {
            fscanf(fIn, "%d", matrix + x*k + y);
        }
    }
    
    //Read in the exponent value
    int n;
    fscanf(fIn, "%d", &n);
    
    //Calculate the matrix to the n power
    matrix = mexp(matrix, k, n - 1);
    
    //Print the resulting answer
    printMatrix(matrix, k);
    
    //Close the input file
    fclose(fIn);
    
    //Deallocate the allocated 2d array
    free(matrix);
    
    return 0;
}
