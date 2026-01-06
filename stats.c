#include <stdlib.h>
#include <stdio.h>

int comp_doubles_asc(void const * const x, void const * const y){
    if(*(double*)x > *(double*)y) return 1; //Need to cast void pointer to type double
    else if (*(double*)x < *(double*)y) return (-1); //Need to cast void pointer to type double
    else return 0;
}

void histogram(double const * const in, int const numpoints, double * const bincentres, int * const bincounts, int const numbins){
    //Calculate min and max val cant assume [0,1] Function didnt work for normalised plot as it is from [-3,3]
    double min_val = in[0];
    double max_val = in[numpoints - 1];

    double bin_width = (max_val - min_val) / (double)numbins; 
    int currPoint = 0;
    double currBinCeiling;

    for(int i = 0; i < numbins; i++){
        currBinCeiling = min_val + (bin_width * (i + 1));

        //if this is the last bin
        if (i == numbins - 1) {
            while(currPoint < numpoints) {
                bincounts[i]++;
                currPoint++;
            }
        } else {
            //while the point is less than the ceiling
            while(currPoint < numpoints && in[currPoint] < currBinCeiling){
                bincounts[i]++;
                currPoint++;
            }
        }

        //Set Bin Centres
        bincentres[i] = min_val + (i * bin_width) + (bin_width / 2.0);
        //printf("Bin %d is placed at bin centre %lf =  with bincount of %d \n", i, bincentres[i], bincounts[i]);
    }
    
}

double expected_value(double * const v, int const N) {

    if (N <= 0) { //Check if zero data points
        return 0.0;
    }

    double sum = 0.0;
    
    // Sum all elements in the array
    for (int i = 0; i < N; i++) {
        sum += v[i];
    }
    
    return sum / N;
}

double variance(double * const v, int const N) {

    if (N <= 0) { //Check if zero data points
        return 0.0;
    }

    //Calculate expected value - E(X)
    double ex_val = expected_value(v, N);

    //Caculate E(X^2) sum the squares of the elements and divide by N
    double sum_sq = 0.0;
    for (int i = 0; i < N; i++) {
        sum_sq += (v[i] * v[i]);
    }
    double ex_val_sq = sum_sq / N;

    //Variance: E(X^2) - (E(X))^2
    return ex_val_sq - (ex_val * ex_val);
}