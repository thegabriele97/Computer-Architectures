#!/bin/bash

output=""
cat $1 | ( while read line; do

    arr=($line)
    if [ "${arr[0]}" == "sim_ticks" -o "${arr[0]}" == "sim_insts" -o "${arr[0]}" == "system.cpu.numCycles" -o\
         "${arr[0]}" == "system.cpu.cpi" -o "${arr[0]}" == "system.cpu.committedInsts" -o "${arr[0]}" == "host_seconds" -o\
         "${arr[0]}" == "system.cpu.branchPred.BTBHits" -o "${arr[0]}" == "system.cpu.iq.FU_type_0::$2" ]; then
        
        output="$output${arr[0]} "," ${arr[1]}\n"
    
    elif [ "${arr[0]}" == "system.cpu.branchPred.condIncorrect" ]; then
        a=${arr[1]}
    elif [ "${arr[0]}" == "system.cpu.branchPred.condPredicted" ]; then
        output="$output$(printf 'Prediction ratio,%.4f' $(echo ${arr[1]}/$a | bc -l))\n"
    fi

done

echo -e $output | column -s ',' -t )