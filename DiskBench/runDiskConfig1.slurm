#!/bin/bash
k=1
for k in {1,2,3,4,5,7,8,9}
do
	sbatch confDisk$k.slurm
	k=$((k+1))
done
