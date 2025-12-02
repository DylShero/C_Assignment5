#include <stdlib.h>
#include <stdio.h>

int comp_doubles_asc(void const * const x, void const * const y){
    if(*(double*)x > *(double*)y) return 1; //Need to cast void pointer to type double
    else if (*(double*)x < *(double*)y) return (-1); //Need to cast void pointer to type double
    else return 0;
}

void histogram(double const * const in, int const numpoints, double * const bincentres, int * const bincounts, int const numbins){
    double binRange = 1.0/numbins; //Mistakenly put just 1. Was doing integer division and then converting to double so would constantly be 0.0
    double currBinCeiling = binRange;
    int currPoint = 0;
    for(int i = 0; i < numbins; i++){
        //double binAvg = 0;

        while(in[currPoint] < (currBinCeiling + (currBinCeiling * i)) && currPoint < numpoints ){
            //binAvg += in[currPoint];
            bincounts[i]++;
            currPoint++;
        }
        //binAvg = binAvg/bincounts[i];
        bincentres[i] = (i*binRange)+(binRange/2);
        printf("Bin %d is placed at bin centre %lf =  with bincount of %d \n", i, bincentres[i], bincounts[i]);
    }



    
}