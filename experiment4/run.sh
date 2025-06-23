#!/bin/bash
cd "$(dirname "$0")"
ulimit -s unlimited

g++ -O2 -std=c++23 -o Test Test.cpp

LOGFILE="output.log"
: > "$LOGFILE"

./Test correctness >> "$LOGFILE"

TIMEOUT=1200

N=(600 700 800 900 1000 1100 1200 1300 1400 1500)
for n in "${N[@]}"; do
    timeout "$TIMEOUT" ./Test "efficiency" "Basic" "$((n-99))" "$n" "$((n-99))" "$n" >> "$LOGFILE"
    EXIT_CODE=$?
    if [ $EXIT_CODE -eq 124 ]; then
        echo "TLE" >> "$LOGFILE"
    elif [ $EXIT_CODE -ne 0 ]; then
        echo "RE" >> "$LOGFILE"
    fi
done

N=(6000 7000 8000 9000 10000 11000 12000 13000 14000 15000)
for n in "${N[@]}"; do
    timeout "$TIMEOUT" ./Test "efficiency" "Basic_Limit" "$((n-999))" "$n" >> "$LOGFILE"
    EXIT_CODE=$?
    if [ $EXIT_CODE -eq 124 ]; then
        echo "TLE" >> "$LOGFILE"
    elif [ $EXIT_CODE -ne 0 ]; then
        echo "RE" >> "$LOGFILE"
    fi
done

N=(200000 300000 400000 500000 600000 700000 800000 900000 1000000)
for n in "${N[@]}"; do
    timeout "$TIMEOUT" ./Test "efficiency" "Basic_Limit_BinarySearch" "$((n-99999))" "$n" >> "$LOGFILE"
    EXIT_CODE=$?
    if [ $EXIT_CODE -eq 124 ]; then
        echo "TLE" >> "$LOGFILE"
    elif [ $EXIT_CODE -ne 0 ]; then
        echo "RE" >> "$LOGFILE"
    fi
done

N=(2000000000000000000 3000000000000000000 4000000000000000000 5000000000000000000 6000000000000000000 7000000000000000000 8000000000000000000 9000000000000000000)
K=(2 3)
for k in "${K[@]}"; do
    for n in "${N[@]}"; do
        timeout "$TIMEOUT" ./Test "efficiency" "NewDP" "$((n-999999999999999999))" "$n" "$k" "$k" >> "$LOGFILE"
        EXIT_CODE=$?
        if [ $EXIT_CODE -eq 124 ]; then
            echo "TLE" >> "$LOGFILE"
        elif [ $EXIT_CODE -ne 0 ]; then
            echo "RE" >> "$LOGFILE"
        fi
    done
done

rm Test