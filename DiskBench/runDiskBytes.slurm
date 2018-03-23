#! /bin/bash
k=1
block=1
for seek in {WR,RR}
do

		
		for qw in {1,2,4,8,16,32,64,128}  
		do
			touch confDiskByte$k.slurm
			echo "#! /bin/bash " >> confDiskByte$k.slurm
			echo " " >> confDiskByte$k.slurm
			echo "#SBATCH --nodes=1" >> confDiskByte$k.slurm
			echo "#SBATCH --output=consoleOutputDiskByte.out" >> confDiskByte$k.slurm
			echo "#SBATCH --wait-all-nodes=1" >> confDiskByte$k.slurm
			echo " " >> confDiskByte$k.slurm
			echo " echo \$SLURM_JOB_NODELIST" >> confDiskByte$k.slurm
			echo " " >> confDiskByte$k.slurm
			echo "./MyDiskBench /$(pwd)/disk-"$seek"-"$block"-"$qw"thread.dat /$(pwd)/output/disk-RR_WR-1thread.out.dat" >> confDiskByte$k.slurm
			k=$((k+1))
		done
			
done

