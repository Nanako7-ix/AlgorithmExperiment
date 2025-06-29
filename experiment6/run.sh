#!/bin/bash
cd "$(dirname "$0")"
ulimit -s unlimited

g++ -fsanitize=address,undefined -g -std=c++23 -o Test Test.cpp
g++ -O2 -std=c++23 -o gen gen.cpp

files=("Atlanta" "Montreal" "NewYork" "Philly")
algos=("EK" "Dinic")

LOGFILE="output.log"
: > "$LOGFILE"

TIMEOUT=2400

for file in "${files[@]}"; do
    for algo in "${algos[@]}"; do
        echo "Running $file with $algo"
        echo "$file $algo" >> "$LOGFILE"
        timeout "$TIMEOUT" ./Test "$algo" "$file" >> "$LOGFILE" 2>&1
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

N=(100 200 300 400 500 600 700 800 900)
Gen="./data/gen.in"

for n in "${N[@]}"; do
    ./gen "$n" > "$Gen"
    for algo in "${algos[@]}"; do
        echo "Running n = $n with $algo"
        echo "<n = $n> $algo" >> "$LOGFILE"
        timeout "$TIMEOUT" ./Test "$algo" "gen" >> "$LOGFILE" 2>&1
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
rm gen