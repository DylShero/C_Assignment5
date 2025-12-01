#include <stdlib.h>

int comp_doubles_asc(void const * const x, void const * const y){
    if(x > y) return 1;
    else if (x < y) return (-1);
    else return 0;
}

void histogram(double const * const in, int const numpoints, double * const bincentres, int * const bincounts, int const numbins){
    
}