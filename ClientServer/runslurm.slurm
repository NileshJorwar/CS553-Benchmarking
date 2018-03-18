#! /bin/bash
k=1
for seek in {1,1000,32000}
	do
		for qw in {1,2,4,8}  
			do
				touch config$k.slurm
				echo "#! /bin/bash " >> config$k.slurm
				echo " " >> config$k.slurm
				echo "#SBATCH --nodes=1" >> config$k.slurm
				echo "#SBATCH --output=consoleOutput.out" >> config$k.slurm
				echo "#SBATCH --wait-all-nodes=1" >> config$k.slurm
				echo " " >> config$k.slurm
				echo " echo \$SLURM_JOB_NODELIST" >> config$k.slurm
				echo " " >> config$k.slurm
				echo "./MyNETBench-TCP /$(pwd)/network-TCP-"$seek"-"$qw"thread.dat /$(pwd)/output/network-TCP-1-1thread.out.dat" >> config$k.slurm
				k=$((k+1))
			done		
	done

