#!/bin/bash

#SBATCH -o multicore_test%j.out
#SBATCH -e multicore_test%j.err 
#SBATCH -p defq
#SBATCH -t 01:00:00
#SBATCH -J multicore_test%j
#SBATCH --mail-type=ALL
#SBATCH --mail-user=yangchuxuan@gmail.com

#matlab -nodesktop < test.m
srun -n 1 -o Multicore_test%t.out --multi-prog myrun.conf 


