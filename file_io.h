/*
Header file for file input and output

Reuses previously written read and write vector
to file functions.

*/

#include <stdio.h>


int 	read_vec_from_file(const char * filename, double v[const], const int n);
int 	write_vec_to_file(const char * filename, const double v[const], const int n);