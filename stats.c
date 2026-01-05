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
        printf("Bin %d is placed at bin centre %lf =  with bincount of %d \n", i, bincentres[i], bincounts[i]);
    }



    
}