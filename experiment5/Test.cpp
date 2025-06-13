#include <bits/stdc++.h>
#include "Parser.hpp"
#include "./solveAlgo/DSU.hpp"
#include "./solveAlgo/BurteForce.hpp"
#include "./solveAlgo/SegmentTreeDivide.hpp"
#include "./solveAlgo/Tarjan.hpp"
#include "./solveAlgo/DSUMaintainEDCC.hpp"

std::set<std::string> fileList {
    "small",
    "medium",
    "large",
    "gen",
};
std::map<std::string, std::vector<std::array<int, 2>> (*)(int, int, std::vector<std::array<int, 2>>)> algo {
    {"BurteForce", BurteForce},
    {"SegmentTreeDivide", SegmentTreeDivide},
    {"DSUMaintainEDCC", DSUMaintainEDCC},
    {"Tarjan", Tarjan},
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <FileName> <Algorithm>\n";
        return 1;
    }

    std::string FileName = argv[1];
    if (!fileList.contains(FileName)) {
        std::cerr << "错误：未知文件 '" << FileName << "'\n";
        return 1;
    }

    std::string Algorithm = argv[2];
    if (!algo.contains(Algorithm)) {
        std::cerr << "错误：未知算法 '" << Algorithm << "'\n";
        return 1;
    }

    auto algoFunc = algo[Algorithm];
    auto [n, m, edges] = parse(FileName);
    
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    algoFunc(n, m, edges);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    double runningTime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0;
    std::cerr << "Running Time: " << runningTime << " ms\n";
    return 0;
}