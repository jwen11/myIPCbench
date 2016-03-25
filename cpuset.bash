#!/bin/bash
#not stable!!
sudo mkdir /cpuset 
sudo mount -t cpuset none /cpuset/
cd /cpuset

sudo mkdir sys												# create sub-cpuset for system processes
sudo sh -c '/bin/echo 0-2 > sys/cpuset.cpus'				# assign cpus (cores) 0-2 to this set
															# adjust if you have more/less cores
sudo sh -c '/bin/echo 1 > sys/cpuset.cpu_exclusive'
sudo sh -c '/bin/echo 0 > sys/cpuset.mems'    

sudo mkdir rt                                    # create sub-cpuset for my process
sudo sh -c '/bin/echo 3-7 > rt/cpuset.cpus'              # assign cpu (core) 3-7 to this cpuset
        	                                            # adjust this to number of cores-1
sudo sh -c '/bin/echo 1 > rt/cpuset.cpu_exclusive'
sudo sh -c '/bin/echo 0 > rt/cpuset.mems'
sudo sh -c '/bin/echo 0 > rt/cpuset.sched_load_balance'
sudo sh -c '/bin/echo 1 > rt/cpuset.mem_hardwall'

# move all processes from the default cpuset to the sys-cpuset
for T in `cat tasks`; do echo "Moving " $T; sudo sh -c '/bin/echo $T > sys/tasks'; done
