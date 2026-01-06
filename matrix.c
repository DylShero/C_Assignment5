#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

void mvect_sq(double **mat, double *v, double *res, int const N) {
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

void mmult_sq(double **x, double **y, double **z, int const N) {
    //Error checking
    if (x == NULL || y == NULL || z == NULL) {
        return;
    }

    //Iterate through rows of Matrix X
    for (int i = 0; i < N; i++) {
        //Iterate through columns of Matrix Y
        for (int j = 0; j < N; j++) {
            
            double sum = 0.0;
            //Calculate the dot product of row i from X and column j from Y
            for (int k = 0; k < N; k++) {
                sum += x[i][k] * y[k][j];
            }

            z[i][j] = sum;
        }
    }
}

void cholesky(double **in, double **out, int const N) {
    //Error checking
    if (in == NULL || out == NULL) {
        return;
    }

    //Initialise matrix as all zeroes
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            out[i][j] = 0.0;
        }
    }

    //Cholesky Decomposition
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            
            double sum = 0.0;

            // Summation corresponds to sum(L[i][k] * L[j][k]) for k = 0 to j-1
            for (int k = 0; k < j; k++) {
                sum += out[i][k] * out[j][k];
            }

            if (i == j) {
                double val = in[i][i] - sum;
                if (val > 0) { //Check for negative values
                    out[i][j] = sqrt(val); 
                } else {
                    out[i][j] = 0.0; 
                }
            } 
            else {
                //Off-Diagonal Element (Lower Triangle)
                // Formula: (1 / L[j][j]) * (A[i][j] - sum)
                if (out[j][j] != 0) {
                     out[i][j] = (1.0 / out[j][j]) * (in[i][j] - sum);
                } else {
                    out[i][j] = 0.0; // Prevent divide by zero
                }
            }
        }
    }
}