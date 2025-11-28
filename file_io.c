/*
Source file for file input and output

Reuses previously written read and write vector
to file functions.

*/


#include <stdio.h>
#include <math.h>
#include "file_io.h"

int read_vec_from_file(const char * filename, double v[const], const int n){
	FILE *fptr = NULL;
	fptr = fopen(filename, "r");
	if(fptr == NULL){ //Error checking if file cannot be accessed give error message
		char errmsg[128];
		sprintf(errmsg, "Error reading from %s on line %d in file %s", filename, __LINE__, __FILE__);
		perror(errmsg);
		return -1;
	}
	for(int i = 0; i<n; i++){
		if(fscanf(fptr, "%lf",&v[i])!= 1){
			char errmsg[128];
			sprintf(errmsg, "Error reading from %s on line %d in file %s", filename, __LINE__, __FILE__);
			perror(errmsg);
			return -1;
		}
	}
	fclose(fptr);
	return 0;
}

int write_vec_to_file(const char * filename, const double v[const], const int n){
	FILE *fptr = NULL;
	fptr = fopen(filename, "w");
	if(fptr == NULL){ //Error checking if file cannot be accessed give error message
		char errmsg[128];
		sprintf(errmsg, "Error reading from %s on line %d in file %s", filename, __LINE__, __FILE__);
		perror(errmsg);
		return -1;
	}
	for(int i = 0; i<n; i++){
		fprintf(fptr,"%lf ", v[i]);
	}

	fclose(fptr);
	return 0;
}