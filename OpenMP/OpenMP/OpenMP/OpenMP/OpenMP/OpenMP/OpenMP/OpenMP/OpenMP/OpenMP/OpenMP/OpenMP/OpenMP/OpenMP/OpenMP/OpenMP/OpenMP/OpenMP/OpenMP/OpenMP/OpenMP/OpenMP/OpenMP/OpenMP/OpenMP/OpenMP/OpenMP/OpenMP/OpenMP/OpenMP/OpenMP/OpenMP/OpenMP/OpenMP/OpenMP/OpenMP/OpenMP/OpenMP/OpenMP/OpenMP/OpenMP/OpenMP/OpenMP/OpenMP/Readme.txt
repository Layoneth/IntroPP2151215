QUAD2D, a C program which estimates an integral over a 2D region by using an product quadrature rule.

This program is intended as a starting point; both MPI and OpenMP can be used to make a parallel version.

This folder has 4 files, one modified code with openMP "omp_quad2d.c", a file in .sbatch "quad2d.sbatch" and an outuput 
file named "output_quad2d.txt"

gcc version 4.8.5
Red Hat 4.8.5-39

for execution, file "omp_quad2d.c" is compiled with the command
gcc -fopenmp omp_quad2d.c -o quad2d 

once this command is done, proceed to run the executable named quad2d 
with "sbatch quad2d.sbatch"

Finally, this command generates the output file "output_quad2d.txt".