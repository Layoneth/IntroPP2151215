#!/bin/bash
#SBATCH --job-name=quad2d_MPI
#SBATCH --output=output_quad2d.txt
#SBATCH --error=output_quad2d.err
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=8
#SBATCH --partition=guane_24_cores
#SBATCH -w guane01


# Load the default OpenMPI module.
module load devtools/mpi/openmpi/3.1.4


# Set OMP_NUM_THREADS to the number of CPUs per task we asked for.
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Run the process with mpirun. Note that the -n option is not required
# in this case; mpirun will automatically determine how many processes
# to run from the Slurm settings.
mpirun -np 2 ./mpi_quad2d
