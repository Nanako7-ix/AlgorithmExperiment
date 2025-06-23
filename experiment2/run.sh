#!/bin/zsh
cd "$(dirname "$0")"
ulimit -s unlimited

g++ -O2 -std=c++23 -o Test Test.cpp

N=(100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000)
algos=("BurteForce" "Divide" "ScanningSet")

LOGFILE="output.log"
: > "$LOGFILE"

TIMEOUT=1200

for n in "${N[@]}"; do
    for algo in "${algos[@]}"; do
        echo "n = $n algo = $algo"
        echo "$n $algo" >> "$LOGFILE"
        timeout "$TIMEOUT" ./Test "$n" "$algo" >> "$LOGFILE" 2>&1
        EXIT_CODE=$?
        if [ $EXIT_CODE -eq 124 ]; then
            echo "TLE" >> "$LOGFILE"
        elif [ $EXIT_CODE -ne 0 ]; then
            echo "RE" >> "$LOGFILE"
        fi
    done
    echo "" >> "$LOGFILE"
    echo ""
done

rm Test