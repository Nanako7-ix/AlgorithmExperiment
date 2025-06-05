#include <bits/stdc++.h>
#include "Parse.hpp"
#include "BurteForce.hpp"
#include "Selective.hpp"
#include "DegreeOpt.hpp"
#include "ForwardCheck.hpp"
#include "MRV.hpp"
#include "ColorPolling.hpp"

std::map<std::string, int> cnt {
    {"sample_4a", 4},
    {"le450_5a", 5},
    {"le450_15b", 15},
    {"le450_25a", 25},
    {"gen", 4}
};

std::map<std::string, int (*)(const int, const std::vector<std::vector<int>>&, const int, const bool)> algo {
    {"BurteForce", BurteForce},
    {"Selective", Selective},
    {"DegreeOpt", DegreeOpt},
    {"ForwardCheck", ForwardCheck},
    {"MRV", MRV},
    {"ColorPolling", ColorPolling}
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <FileName> <Algorithm> <find_first>\n";
        return 1;
    }

    std::string FileName = argv[1];
    if (cnt.find(FileName) == cnt.end()) {
        std::cerr << "错误：未知文件 '" << FileName << "'\n";
        return 1;
    }
    int count = cnt[FileName];

    std::string Algorithm = argv[2];
    if (algo.find(Algorithm) == algo.end()) {
        std::cerr << "错误：未知算法 '" << Algorithm << "'\n";
        return 1;
    }
    
    bool find_first = atoi(argv[3]);

    std::cerr << "FileName: " << FileName << ", Count: " << count << ", Algorithm: " << Algorithm << "\n";
    auto algoFunc = algo[Algorithm];
    auto [n, adj] = parse(FileName);
    
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    algoFunc(n, adj, count, find_first);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    double runningTime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0;
    std::cerr << "Running Time: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0 << " ms\n\n";
    std::cout << runningTime << "\n";
    return 0;
}