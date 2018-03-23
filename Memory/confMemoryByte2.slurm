#! /bin/bash 
 
#SBATCH --nodes=1
#SBATCH --output=consoleOutputByte.out
#SBATCH --wait-all-nodes=1
 
 echo $SLURM_JOB_NODELIST
 
./MyRAMBench //exports/home/njorwar/CS553-PA1/memory/memory-RWR-1-2thread.dat //exports/home/njorwar/CS553-PA1/memory/output/memory-RWR_RWS_Latency-1thread.out.dat
