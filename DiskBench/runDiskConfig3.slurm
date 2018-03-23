#!/bin/bash
k=19
for k in {19,20,21,22,23,24,25,26,27}
do
	sbatch confDisk$k.slurm
	k=$((k+1))
done
