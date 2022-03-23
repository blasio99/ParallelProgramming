#!/bin/bash 

# Spawns $1 instances of the program $2  

#instances=$1 

#program=$2 

#arg1=$3
#arg2=$4

time ./lab3 1 100000 &

time ./lab3 1 25000 &
time ./lab3 25001 50000 &
time ./lab3 50001 75000 &
time ./lab3 75001 100000 &

wait 