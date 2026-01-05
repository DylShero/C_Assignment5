/**
 * @file assignment5a.c
 * @brief  Skeleton code for Assignment 5, 5613 C programming
 *          The student needs to modify or add code indicated by the three \\\ 
 *          and also "TODO" (which may or may not be highlighted in you IDE!)
 * @author R. Morrin
 * @version  1.0
 * @date 2025-11-28
 */

#include <stdio.h>
#include <stdlib.h>
#include "random.h"
#include "file_io.h"
#include "stats.h"


#define NUMRAN 1000000   /* Number of random numbers to generate */


int main(void)
{
    /* Allocate memory for uniformly distributed variables */
    double *u=malloc(NUMRAN*sizeof *u);
    if(u==NULL){
        perror("Error allocating memory for u");
        exit(EXIT_FAILURE);
    }
    /* Allocate memory for transformed normally distributed variables */
    double *v = malloc(NUMRAN * sizeof *v);
    if(v==NULL){
        perror("Error allocating memory for v");
        exit(EXIT_FAILURE);
    }

    /// TODO
    /// Replace the seed with the last 5 digits of your student number
    srand(30976);


    for (int i = 0; i < NUMRAN; i++) {
           u[i] = (double)rand()/RAND_MAX; //Cast to double to do as calculation as a double. Divide by RAND_MAX to get values with [0,1]
    }

    /// TODO
    /// Write code to call your box_muller function and use it to populate v[]
    ///
    for(int i = 0; i < NUMRAN; i+=2){
        box_muller(u[i], u[i+1], &v[i], &v[i+1]);
    }
    
    

  /// TODO:
  /// Reuse your write_vec_to_file function from file_io.c to write u to "uniform.txt"
  /// and to write v to "normal.txt". Use appropriate error checks


  /*
   * These lines call qsort on the two arrays. 
   * To check, you can write the sorted arrays to "uniform_sorted.txt"
   * and "normal_sorted.txt" respectively.
   * NOTE: You will need to write comp_doubles_asc yourself. See document
   */
    qsort(u, NUMRAN, sizeof(double), comp_doubles_asc);
    qsort(v, NUMRAN, sizeof(double), comp_doubles_asc);
    /*for(int i = 0; i < 100; i++){
        printf("%lf\n", u[i]);
    } */

    /*for(int i = 0; i < 100; i++){
        printf("%lf\n", v[i]);
    }*/

  

    /* 
     * The code below here will set up, and then call the functions to create
     * and then write to file, the histograms
     */
    int const numbins = 50;     /* You can just use a fixed number for this assignment */

    /// TODO 
    /// Allocate memory for arrays to hold the bincounts and bincentres. I.e arrays that hold
    /// numbins integers and doubles respectively.
    int * bincounts = calloc(numbins ,sizeof(*bincounts));
    if(bincounts == NULL){
        perror("Allocating memeory for bincounts array failed\n");
        exit(EXIT_FAILURE);
    }
    double * bincentres = calloc(numbins, sizeof(*bincentres));
    if(bincentres == NULL){
        perror("Failure allocating memory for bin centres\n");
        exit(EXIT_FAILURE);
    }
   


    /*
     * The below code will call the functions you write to create the histogram data
     * and then write it to file. These lines should work in your final version 
     * of your main without modification
     */
    histogram(u, NUMRAN, bincentres, bincounts, numbins);
    write_histogram_to_file("uniform_histogram.txt", bincentres, bincounts, numbins);
    
    for(int i = 0; i < numbins; i++){
        bincounts[i] = 0;
        bincentres[i] = 0.0;
    }

    histogram(v, NUMRAN, bincentres, bincounts, numbins);
    write_histogram_to_file("normal_histogram.txt", bincentres, bincounts, numbins); 
    
    /// TODO:
    /// Do any tidying up here
    return 0;
}

