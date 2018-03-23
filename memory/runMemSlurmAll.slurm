#! /bin/bash
k=1
for seek in {RWR,RWS}
do
	for block in {1000,1000000,10000000}
	do	
		for qw in {1,2,4}  
		do
			touch confMemory$k.slurm
			echo "#! /bin/bash " >> confMemory$k.slurm
			echo " " >> confMemory$k.slurm
			echo "#SBATCH --nodes=1" >> confMemory$k.slurm
			echo "#SBATCH --output=consoleOutput.out" >> confMemory$k.slurm
			echo "#SBATCH --wait-all-nodes=1" >> confMemory$k.slurm
			echo " " >> confMemory$k.slurm
			echo " echo \$SLURM_JOB_NODELIST" >> confMemory$k.slurm
			echo " " >> confMemory$k.slurm
			echo "./MyRAMBench /$(pwd)/memory-"$seek"-"$block"-"$qw"thread.dat /$(pwd)/output/memory-RWR-1-1thread.out.dat" >> confMemory$k.slurm
			k=$((k+1))
		done
	done		
done

