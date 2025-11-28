#
# Makefile for Assignment 5 for 5613 C programming
# Use: make or make clean to compile 
#
# D. Sheridan
# V 1.0
# 28-Nov-2025
#

all: assignment5a

assignment5a: assignment5a.c file_io.o 
	gcc -Wall -Wextra -o assignment5a assignment5a.c file_io.o sort.o

file_io.o: file_io.c 
	gcc -Wall -Wextra -c file_io.c

.PHONY: all clean

clean:
	rm -f assignment5a file_io.o
