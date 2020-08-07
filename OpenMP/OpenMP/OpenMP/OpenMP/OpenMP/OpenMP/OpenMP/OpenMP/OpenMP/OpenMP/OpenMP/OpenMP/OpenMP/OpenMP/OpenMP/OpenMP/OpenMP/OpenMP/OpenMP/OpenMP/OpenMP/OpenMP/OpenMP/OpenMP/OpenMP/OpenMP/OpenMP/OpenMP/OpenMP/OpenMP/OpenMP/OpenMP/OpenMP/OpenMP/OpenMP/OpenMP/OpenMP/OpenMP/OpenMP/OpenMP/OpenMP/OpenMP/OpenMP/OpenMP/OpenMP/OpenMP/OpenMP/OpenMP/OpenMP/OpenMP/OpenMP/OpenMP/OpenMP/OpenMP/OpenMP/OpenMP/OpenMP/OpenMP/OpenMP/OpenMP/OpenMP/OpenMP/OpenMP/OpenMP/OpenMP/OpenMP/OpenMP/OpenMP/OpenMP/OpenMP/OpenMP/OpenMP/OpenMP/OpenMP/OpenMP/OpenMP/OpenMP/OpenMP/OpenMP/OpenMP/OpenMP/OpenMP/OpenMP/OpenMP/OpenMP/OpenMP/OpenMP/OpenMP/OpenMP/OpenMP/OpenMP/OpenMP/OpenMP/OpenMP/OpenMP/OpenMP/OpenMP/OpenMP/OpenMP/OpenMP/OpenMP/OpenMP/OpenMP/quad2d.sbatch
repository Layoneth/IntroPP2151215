#!/bin/bash

export OMP_NUM_TREADS=4
#SBATCH -w guane01
gcc -fopenmp openmp_quad2d.c -o omp
./omp > output_quad2d.txt

