#!/bin/bash
ulimit -s unlimited

g++ -O2 -std=c++23 -o Test Test.cpp
g++ -O2 -std=c++23 -o gen gen.cpp

algorithms=("BurteForce" "Selective" "DegreeOpt" "ForwardCheck" "MRV" "ColorPolling")
maps=("sample_4a" "le450_5a" "le450_15b" "le450_25a")
node_sizes=(10000 20000 30000 40000 50000 60000 70000 80000 90000 100000)
!
TIME_LIMIT=1200
mkdir -p logs
> output.log

for algo in "${algorithms[@]}"; do
    for map in "${maps[@]}"; do
        echo "Running $algo on $map..."

        OUTPUT="logs/${algo}_${map}.out"

        timeout $TIME_LIMIT ./Test "$map" "$algo" 0 > "$OUTPUT"
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

echo "" >> output.log
for algo in "${algorithms[@]}"; do
    for map in "${maps[@]}"; do
        echo "Running $algo on $map..."

        OUTPUT="logs/${algo}_${map}.out"

        timeout $TIME_LIMIT ./Test "$map" "$algo" 1 > "$OUTPUT"
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

echo "" >> output.log
for n in "${node_sizes[@]}"; do
    echo "Generating n = $n"
    ./gen "$n"
    
    algo="ColorPolling"
    
    OUTPUT="logs/gen_${n}.out"
    
    timeout $TIME_LIMIT ./Test "gen" "$algo" 0 > "$OUTPUT"
    STATUS=$?
    
    if [ $STATUS -eq 124 ]; then
        echo "gen $n TLE" >> output.log
    elif [ $STATUS -ne 0 ]; then
        echo "gen $n RE" >> output.log
    else
        LAST_LINE=$(tail -n 1 "$OUTPUT")
        echo "gen $n $LAST_LINE" >> output.log
    fi
done

rm -rf logs
rm Test
rm gen