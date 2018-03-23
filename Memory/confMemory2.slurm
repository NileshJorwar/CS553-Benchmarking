#! /bin/bash 
 
#SBATCH --nodes=1
#SBATCH --output=consoleOutput.out
#SBATCH --wait-all-nodes=1
 
 echo $SLURM_JOB_NODELIST
 
./MyRAMBench //exports/home/njorwar/CS553-PA1/memory/memory-RWR-1000-2thread.dat //exports/home/njorwar/CS553-PA1/memory/output/memory-RWR-1-1thread.out.dat
