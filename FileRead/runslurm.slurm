#! /bin/bash
k=1
for seek in {QP,HP,SP,DP}
	do
		for qw in {1,2,4}  
			do
				touch confCPU$k.slurm
				echo "#! /bin/bash " >> confCPU$k.slurm
				echo " " >> confCPU$k.slurm
				echo "#SBATCH --nodes=1" >> confCPU$k.slurm
				echo "#SBATCH --output=consoleOutputCPU.out" >> confCPU$k.slurm
				echo "#SBATCH --wait-all-nodes=1" >> confCPU$k.slurm
				echo " " >> confCPU$k.slurm
				echo " echo \$SLURM_JOB_NODELIST" >> confCPU$k.slurm
				echo " " >> confCPU$k.slurm
				echo "./MyCPUBench /$(pwd)/cpu_"$seek"_"$qw"thread.dat /$(pwd)/output/cpu_SP_1thread.out.dat" >> confCPU$k.slurm
				k=$((k+1))
			done		
	done

