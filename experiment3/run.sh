#!/bin/bash

g++ -O2 -std=c++23 -o Test Test.cpp

algorithms=("BurteForce" "Selective" "DegreeOpt" "ForwardCheck" "MRV" "ColorPolling")
maps=("sample_4a" "le450_5a" "le450_15b" "le450_25a")

TIME_LIMIT=60
mkdir -p logs
> output.log

for algo in "${algorithms[@]}"; do
    for map in "${maps[@]}"; do
        echo "Running $algo on $map..."

        OUTPUT="logs/${algo}_${map}.out"

        timeout $TIME_LIMIT ./Test "$map" "$algo" > "$OUTPUT"
        STATUS=$?

        if [ $STATUS -eq 124 ]; then
            echo "$algo $map TLE" >> output.log
        elif [ $STATUS -ne 0 ]; then
            echo "$algo $map RE" >> output.log
        else
            LAST_LINE=$(tail -n 1 "$OUTPUT")
            echo "$algo $map $LAST_LINE" >> output.log
        fi
    done
done