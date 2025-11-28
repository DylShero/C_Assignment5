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
    srand(12345);

    /// TODO
    /// Populate the initial array of doubles between 0 and 1 
    /// Remember that rand() returns values on [0, RAND_MAX] 
    for (int i = 0; i < NUMRAN; i++) {
           u[i] = random();
    }

    /// TODO
    /// Write code to call your box_muller function and use it to populate v[]
    ///
    

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

  

    /* 
     * The code below here will set up, and then call the functions to create
     * and then write to file, the histograms
     */
    int const numbins = 50;     /* You can just use a fixed number for this assignment */

    /// TODO 
    /// Allocate memory for arrays to hold the bincounts and bincentres. I.e arrays that hold
    /// numbins integers and doubles respectively.
    //int * bincounts = 
    ////double * bincentres =
   


    /*
     * The below code will call the functions you write to create the histogram data
     * and then write it to file. These lines should work in your final version 
     * of your main without modification
     */
    histogram(u, NUMRAN, bincentres, bincounts, numbins);
    write_histogram_to_file("uniform_histogram.txt", bincentres, bincounts, numbins);
    histogram(v, NUMRAN, bincentres, bincounts, numbins);
    write_histogram_to_file("normal_histogram.txt", bincentres, bincounts, numbins);
    
    /// TODO:
    /// Do any tidying up here
    return 0;
}

