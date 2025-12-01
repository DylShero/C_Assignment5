#include <stdlib.h>

int comp_doubles_asc(void const * const x, void const * const y){
    if(*(double*)x > *(double*)y) return 1; //Need to cast void pointer to type double
    else if (*(double*)x < *(double*)y) return (-1); //Need to cast void pointer to type double
    else return 0;
}

void histogram(double const * const in, int const numpoints, double * const bincentres, int * const bincounts, int const numbins){

}