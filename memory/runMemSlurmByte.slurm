#! /bin/bash
k=1
block=1
for seek in {RWR,RWS}
do
	
		
		for qw in {1,2,4}  
		do
			touch confMemoryByte$k.slurm
			echo "#! /bin/bash " >> confMemoryByte$k.slurm
			echo " " >> confMemoryByte$k.slurm
			echo "#SBATCH --nodes=1" >> confMemoryByte$k.slurm
			echo "#SBATCH --output=consoleOutputByte.out" >> confMemoryByte$k.slurm
			echo "#SBATCH --wait-all-nodes=1" >> confMemoryByte$k.slurm
			echo " " >> confMemoryByte$k.slurm
			echo " echo \$SLURM_JOB_NODELIST" >> confMemoryByte$k.slurm
			echo " " >> confMemoryByte$k.slurm
			echo "./MyRAMBench /$(pwd)/memory-"$seek"-"$block"-"$qw"thread.dat /$(pwd)/output/memory-RWR_RWS_Latency-1thread.out.dat" >> confMemoryByte$k.slurm
			k=$((k+1))
		done
			
done

