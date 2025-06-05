#!/bin/bash

g++ -O2 -std=c++23 -o Test Test.cpp
g++ -O2 -std=c++23 -o gen gen.cpp

algorithms=("BurteForce" "Selective" "DegreeOpt" "ForwardCheck" "MRV" "ColorPolling")
maps=("sample_4a" "le450_5a" "le450_15b" "le450_25a")
node_sizes=(1000 2000 3000 4000 5000)

TIME_LIMIT=600
mkdir -p logs
> output.log

# 任务1: 测试找出所有解的时间 (find_first=0)
echo "测试所有解的时间 (find_first=0)" >> output.log
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

# 任务2: 测试找出第一个解的时间 (find_first=1)
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

# 任务3: 测试生成固定点数并找出所有解的运行时间
echo -e "\n测试生成图的所有解时间 (find_first=0)" >> output.log
for n in "${node_sizes[@]}"; do
    echo "生成 $n 个节点的图..."
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