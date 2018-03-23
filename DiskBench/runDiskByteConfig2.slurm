#!/bin/bash
k=10
for k in {10,11,12,13,14,15,16}
do
	sbatch confDiskByte$k.slurm
	k=$((k+1))
done
