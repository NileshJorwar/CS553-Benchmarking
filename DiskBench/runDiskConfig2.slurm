#!/bin/bash
k=10
for k in {10,11,12,13,14,15,16,17,18}
do
	sbatch confDisk$k.slurm
	k=$((k+1))
done
