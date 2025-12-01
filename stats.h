#ifndef STATS_H
#define STATS_H

int comp_doubles_asc(void const * const x, void const * const y);
void histogram(double const * const in, int const numpoints, double * const bincentres, int * const bincounts, int const numbins);

#endif