

#include <stdlib.h>
#include "matrix.h"

double **allocate_sq_matrix_contig(int const N) {
    // Check for invalid size
    if (N <= 0) {
        return NULL;
    }


    //This holds N pointers (rows[0], rows[1], etc.)
    double **rows = malloc(N * sizeof(double *));
    
    //Safety check for malloc failure
    if (rows == NULL) {
        return NULL;
    }

    //This holds N*N doubles in one solid block of memory
    double *data = malloc(N * N * sizeof(double));

    // Safety check for malloc failure. Free rows before returning
    if (data == NULL) {
        free(rows);
        return NULL;
    }

    //Link the row pointers to the specific offsets in the data block
    for (int i = 0; i < N; i++) {
        rows[i] = data + (i * N);
    }

    return rows;
}

void free_sq_matrix_contig(double **A) {
    //Error checking
    if (A == NULL) {
        return;
    }

    //Frees the entire block of data.
    if (A[0] != NULL) {
        free(A[0]);
    }

    //Frees the row pointers
    free(A);
}

void print_matrix(double **A, int const N) {
    //Error checking
    if (A == NULL) {
        return;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            //%10.4f prints a double with 4 decimal places, 
            printf("%10.4f", A[i][j]);
        }
        //newline at the end of every row
        printf("\n");
    }
}

void mvectsq(double **mat, double *v, double *res, int const N) {
    //Error checking
    if (mat == NULL || v == NULL || res == NULL) {
        return;
    }

    for (int i = 0; i < N; i++) {
        double sum = 0.0;
        
        //Iterate through matrix and vector and get ans.
        for (int j = 0; j < N; j++) {
            sum += mat[i][j] * v[j];
        }
        
        res[i] = sum;
    }
}