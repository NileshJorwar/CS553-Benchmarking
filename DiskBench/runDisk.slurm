#! /bin/bash
k=1
for seek in {WS,RS,WR,RR}
do
	for block in {1000,10000,100000}
	do	
		for qw in {1,2,4}  
		do
			touch confDisk$k.slurm
			echo "#! /bin/bash " >> confDisk$k.slurm
			echo " " >> confDisk$k.slurm
			echo "#SBATCH --nodes=1" >> confDisk$k.slurm
			echo "#SBATCH --output=consoleOutputDisk.out" >> confDisk$k.slurm
			echo "#SBATCH --wait-all-nodes=1" >> confDisk$k.slurm
			echo " " >> confDisk$k.slurm
			echo " echo \$SLURM_JOB_NODELIST" >> confDisk$k.slurm
			echo " " >> confDisk$k.slurm
			echo "./MyDiskBench /$(pwd)/disk-"$seek"-"$block"-"$qw"thread.dat /$(pwd)/output/disk-RR-1-1thread.out.dat" >> confDisk$k.slurm
			k=$((k+1))
		done
	done		
done

