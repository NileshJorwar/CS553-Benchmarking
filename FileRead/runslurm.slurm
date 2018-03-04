#! /bin/bash
k=1
for seek in {QP,HP,SP,DP}
	do
		for qw in {1,2,4}  
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
				echo "./MyCPUBench /$(pwd)/cpu_"$seek"_"$qw"thread.dat /$(pwd)/output/cpu_SP_1thread.out.dat" >> config$k.slurm
				k=$((k+1))
			done		
	done

