#!/bin/bash
k=16
for k in {16,17,18}
do
	sbatch confMemory$k.slurm
	k=$((k+1))
done
