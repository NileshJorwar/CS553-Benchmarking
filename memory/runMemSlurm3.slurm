#!/bin/bash
k=11
for k in {11,12,13,14,15}
do
	sbatch confMemory$k.slurm
	k=$((k+1))
done
