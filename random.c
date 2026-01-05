#include "random.h" 
#include <math.h>

#define PI 3.141593

void box_muller(double const u1, double const u2, double * n1, double * n2){
    if(u1 <= 0.0) { //Deal with log(0) inputs
        *n1 = 0.0; 
        *n2 = 0.0;
        return;
    }
    *n1 = (sqrt((-2)*log(u1))*cos(2*PI*u2));
    *n2 = (sqrt((-2)*log(u1))*sin(2*PI*u2));
}