#ifndef STATS_H
#define STATS_H

int comp_doubles_asc(void const * const x, void const * const y);
void histogram(double const * const in, int const numpoints, double * const bincentres, int * const bincounts, int const numbins);
double expected_value(double * const v, int const N);
double variance(double * const v, int const N);


#endif