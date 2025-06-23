#include <bits/stdc++.h>
#include "Point.hpp"
#include "./solveAlgo/BurteForce.hpp"
#include "./solveAlgo/Divide.hpp"
#include "./solveAlgo/ScanningSet.hpp"

std::map<std::string, double (*)(std::vector<Point>)> algo {
    {"BurteForce", BurteForce},
    {"Divide", Divide},
    {"ScanningSet", ScanningSet},
};

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
constexpr int Mod = 1000000000;

std::vector<Point> Gen(int n) {
    std::vector<Point> data(n);
    for (int i = 0; i < n; ++i) {
        data[i] = Point { rng() % Mod, rng() % Mod };
    }
    return data;
}

int main (int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: <N> <Algorithm>\n";
        return 1;
    }
    int n = std::atoi(argv[1]);
    auto algoFunc = algo[argv[2]];
    auto points = Gen(n);

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    algoFunc(points);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    double runningTime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0;
    std::cerr << "Running Time: " << runningTime << " ms\n";
    return 0;
}