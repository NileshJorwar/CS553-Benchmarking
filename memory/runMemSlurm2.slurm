#!/bin/bash
k=6
for k in {6,7,8,9,10}
do
	sbatch confMemory$k.slurm
	k=$((k+1))
done
