#!/bin/bash
k=6
for k in {6,7,8,9,10,11,12}
do
	sbatch config$k.slurm
	k=$((k+1))
done
