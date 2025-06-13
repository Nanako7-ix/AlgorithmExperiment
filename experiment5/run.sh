#!/bin/zsh
cd "$(dirname "$0")"
ulimit -s unlimited

g++ -O2 -std=c++23 -o Test Test.cpp
g++ -O2 -std=c++23 -o gen gen.cpp

files=("small" "medium" "large")
algos=("BurteForce" "SegmentTreeDivide" "DSUMaintainEDCC" "Tarjan")

LOGFILE="output.log"
"" > "$LOGFILE"

TIMEOUT=1200

for file in "${files[@]}"; do
    for algo in "${algos[@]}"; do
        echo "Running $file with $algo"
        echo "$file $algo" >> "$LOGFILE"
        timeout "$TIMEOUT" ./Test "$file" "$algo" >> "$LOGFILE" 2>&1
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

N=(1000000 2000000 3000000 4000000 5000000)
Gen="./data/gen.txt"

for n in "${N[@]}"; do
    ./gen "$n" "$((4*n))" > "$Gen"
    for algo in "${algos[@]}"; do
        echo "Running n = $n with $algo"
        echo "$n $algo" >> "$LOGFILE"
        timeout "$TIMEOUT" ./Test "gen" "$algo" >> "$LOGFILE" 2>&1
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