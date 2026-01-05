#ifndef MATRIX_H_DMCR5GO9
#define MATRIX_H_DMCR5GO9

void print_matrix(double **A, int const N);
double** allocate_sq_matrix_contig(int const N);
void free_sq_matrix_contig(double **A);
void mmult_sq(double **x, double**y, double **z, int const N);
void mvect_sq(double **mat, double *v, double *res, int const N);
void cholesky(double **in, double **out, int const N);

#endif /* end of include guard: SIMULATION_H_DMCR5GO9 */
