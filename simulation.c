#include <stdlib.h>
#include <stdio.h>
#include "simulation.h"
#include "matrix.h"

void simulate_portfolio_normal(double *rv_normal, double *portfolio_values, 
                               double **lower_chol, int const num_sims, 
                               int const num_stocks) {
    
    //Error checking
    if (rv_normal == NULL || portfolio_values == NULL || lower_chol == NULL) {
        return;
    }

    //Allocate temporary memory to hold the correlated variables for a simulation
    double *correlated_rvs = malloc(num_stocks * sizeof(double));
    
    if (correlated_rvs == NULL) {
        printf("Temporary malloc allocation failed \n");
        return;
    }

    for (int i = 0; i < num_sims; i++) {
        
        //Calculate the offset for the current batch of independent variables
        double *current_independent_batch = rv_normal + (i * num_stocks);

        //Transform independent -> correlated
        mvect_sq(lower_chol, current_independent_batch, correlated_rvs, num_stocks);

        //Sum the correlated variables to get the "Portfolio Value"
        double sum = 0.0;
        for (int j = 0; j < num_stocks; j++) {
            sum += correlated_rvs[j];
        }

        portfolio_values[i] = sum;
    }

    free(correlated_rvs);
}