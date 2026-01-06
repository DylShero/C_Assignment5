/**
 * @file assignment5b.c
 * @brief Almost complete main function for 5613 Assignment 5
 *           You will use this main function in conjunction with the other
 *           functions you wrote. The final program should do a simple toy
 *           simulation which gives you an idea of the effect of correlation
 *           and diversification when constructing portfolios.
 * @author R. Morrin
 * @version 1.0
 * @date 2025-12-02
 */
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include "random.h"
#include "simulation.h"
#include "stats.h"
#include "file_io.h"

int const NUM_STOCKS =       3;
int const NUM_SIMS   = 1000000;

int main(void)
{

    double *uniform_rvs = malloc(NUM_SIMS * NUM_STOCKS *sizeof * uniform_rvs);
    if(uniform_rvs == NULL){
        perror("Error Allocating memory for uniform_rvs");
        exit(EXIT_FAILURE);
    }

    /// TODO: Replace seed with last 5 digits of your student number
    srand(30976); 
    for (int i = 0; i < NUM_SIMS*NUM_STOCKS; i++) {
        /// TODO: Populate uniform_rvs array the same as you did for assigment5a.c
        /// i.e. using rand()
        uniform_rvs[i] = (double)rand() / (double)RAND_MAX;
    }


    double *normal_rvs = malloc(NUM_SIMS * NUM_STOCKS *sizeof * uniform_rvs);
    if(normal_rvs == NULL){
        perror("Error Allocating memory for normal_rvs");
        exit(EXIT_FAILURE);
    }
    /// TODO:
    /// Call your box_muller to transform the uniform rvs in uniform_rvs and store the 
    /// transformed numbers in normal_rvs
    for (int i = 0; i < NUM_SIMS * NUM_STOCKS; i += 2) {
        box_muller(uniform_rvs[i], uniform_rvs[i+1], &normal_rvs[i], &normal_rvs[i+1]);
    }


    /*
     * First correlation Matrix
     {1.0, 0.75, 0.5}
     {0.75, 1.0, 0.6}
     {0.5, 0.6, 1.0}
     */
    double **corr1 = allocate_sq_matrix_contig(NUM_STOCKS);
    if(corr1==NULL){
        fprintf(stderr, "Error allocating memory for corr1");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_STOCKS; i++) {
        corr1[i][i] = 1.0 ;
    }
    corr1[0][1] = corr1[1][0] = 0.9;
    corr1[0][2] = corr1[2][0] = 0.7;
    corr1[1][2] = corr1[2][1] = 0.8;

    /*
     * Second correlation Matrix
     *
     * {1.0, -0.4, -0.6}
     * {-0.4, 1.0, -0.45}
     * {-0.6, -0.45, 1.0}
     */
    double **corr2 = allocate_sq_matrix_contig(NUM_STOCKS);
    if(corr2==NULL){
        fprintf(stderr, "Error allocating memory for corr2");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_STOCKS; i++) {
        corr2[i][i] = 1.0 ;
    }
    corr2[0][1] = corr2[1][0] = -0.4;
    corr2[0][2] = corr2[2][0] = -0.6;
    corr2[1][2] = corr2[2][1] = -0.45;


    /* 
     * Identity matrix (for independent simulation)
     */
    double **Identity = allocate_sq_matrix_contig(NUM_STOCKS);
    if(Identity==NULL){
        fprintf(stderr, "Error allocating memory for Identity");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < NUM_STOCKS; i++) {
        for (int j = 0; j < NUM_STOCKS; j++) {
            if(i==j){
                Identity[i][j] = 1.0;
            }
            else{
                Identity[i][j] = 0.0;
            }
        }
    }


    double * portfolio_values = malloc(NUM_SIMS * sizeof * portfolio_values);
    if(portfolio_values == NULL){
        perror("Error allocating memory for portfolio_values");
        exit(EXIT_FAILURE);
    }
    /*
     * FIRST SIMULATION
     */  
    int const numbins = 50;     /* Just pick 50 for no particular reason */
    int * bincounts = malloc(numbins * sizeof * bincounts);
    if(bincounts == NULL){
        perror("Error allocating memory for bincounts");
        exit(EXIT_FAILURE);
    }

    for (int k = 0; k < numbins; k++) { //Set all bincount values to zero.
        bincounts[k] = 0;
    }
    double * bincentres = malloc (numbins * sizeof * bincentres);
    if(bincentres == NULL){
        perror("Error allocating memory for bincentres");
        exit(EXIT_FAILURE);
    }
    printf("\nFirst Simulation\n");
    printf("Identity matrix:\n");
    print_matrix(Identity, NUM_STOCKS);
    /* Simulate portfolio */
    simulate_portfolio_normal(normal_rvs, portfolio_values, Identity, NUM_SIMS, NUM_STOCKS);
    /* call qsort to order values the same as for Part 1 of the assignment */
    qsort(portfolio_values, NUM_SIMS, sizeof(double), comp_doubles_asc);
    /* Create histogram of values and write to file */
    histogram(portfolio_values, NUM_SIMS, bincentres, bincounts, numbins);
    write_histogram_to_file("independent.txt", bincentres, bincounts, numbins);
    printf("Mean of Distribution = %lf\n", expected_value(portfolio_values,NUM_SIMS));
    printf("Variance of Distribution = %lf\n", variance(portfolio_values,NUM_SIMS));


    /*
     * SECOND SIMULATION
     */
    /* Matrix to hold Cholesky Decomposition */
    double **lower = allocate_sq_matrix_contig(NUM_STOCKS);
    if(lower==NULL){
        fprintf(stderr, "Error allocating memory for lower");
        exit(EXIT_FAILURE);
    }

    printf("\nSecond Simulation\n");
    printf("====== Corr1\n");
    print_matrix(corr1, NUM_STOCKS);
    printf("====== Cholesky Lower\n");
    cholesky(corr1, lower, NUM_STOCKS);
    print_matrix(lower, NUM_STOCKS);

    /* Do round trip check */
    double **upper = allocate_sq_matrix_contig(NUM_STOCKS);
    if(upper==NULL){
        fprintf(stderr, "Error allocating memory for upper");
        exit(EXIT_FAILURE);
    }
    /* Create upper as lower transposed */
    for (int i = 0; i < NUM_STOCKS; i++) {
        for (int j = 0; j < NUM_STOCKS; j++) {
            upper[i][j] = lower[j][i]; 
        }
    }
    double **roundtrip = allocate_sq_matrix_contig(NUM_STOCKS);
    if(roundtrip==NULL){
        fprintf(stderr, "Error allocating memory for upper");
        exit(EXIT_FAILURE);
    }
    printf("====== Roundtrip\n");
    mmult_sq(lower,upper,roundtrip, NUM_STOCKS);
    print_matrix(roundtrip, NUM_STOCKS);

    /* Now do simulation part */
    simulate_portfolio_normal(normal_rvs, portfolio_values, lower, NUM_SIMS, NUM_STOCKS);
    qsort(portfolio_values, NUM_SIMS, sizeof(double), comp_doubles_asc);
    histogram(portfolio_values, NUM_SIMS, bincentres, bincounts, numbins);
    write_histogram_to_file("first_correlation.txt", bincentres, bincounts, numbins);
    printf("Mean of Distribution = %lf\n", expected_value(portfolio_values,NUM_SIMS));
    printf("Variance of Distribution = %lf\n", variance(portfolio_values,NUM_SIMS));


    /*
     * THIRD SIMULATION
     */
    printf("\nThird Simulation\n");
    printf("====== Corr2\n");
    print_matrix(corr2, NUM_STOCKS);
    cholesky(corr2, lower, NUM_STOCKS);
    printf("====== Cholesky Lower\n");
    print_matrix(lower, NUM_STOCKS);
    /* Now do simulation part */
    simulate_portfolio_normal(normal_rvs, portfolio_values, lower, NUM_SIMS, NUM_STOCKS);
    qsort(portfolio_values, NUM_SIMS, sizeof(double), comp_doubles_asc);
    histogram(portfolio_values, NUM_SIMS, bincentres, bincounts, numbins);
    write_histogram_to_file("second_correlation.txt", bincentres, bincounts, numbins);
    printf("Mean of Distribution = %lf\n", expected_value(portfolio_values,NUM_SIMS));
    printf("Variance of Distribution = %lf\n", variance(portfolio_values,NUM_SIMS));


    /*
     * Free allocated memory
     * You could argue that this is a bit pointless here given the program is about to exit,
     * but it is a good idea to get into the habit of making sure that for every malloc, there
     * should be a corresponding free. This rule of thumb will be correct 99% of the time.
     */
    free(uniform_rvs);
    free(normal_rvs);
    free(portfolio_values);
    free(bincounts);
    free(bincentres);
    free_sq_matrix_contig(corr1);
    free_sq_matrix_contig(corr2);
    free_sq_matrix_contig(Identity);
    free_sq_matrix_contig(lower);
    free_sq_matrix_contig(upper);
    free_sq_matrix_contig(roundtrip);
    return 0;
}
