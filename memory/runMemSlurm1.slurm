#!/bin/bash
k=1
for k in {1,2,3,4,5}
do
	sbatch confMemory$k.slurm
	k=$((k+1))
done
