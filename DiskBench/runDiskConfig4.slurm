#!/bin/bash
k=28
for k in {28,29,30,31,32,33,34,35,36}
do
	sbatch confDisk$k.slurm
	k=$((k+1))
done
