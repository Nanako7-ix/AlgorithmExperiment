#include <bits/stdc++.h>
#include "./solveAlgo/Basic.hpp"
#include "./solveAlgo/Basic_Limit.hpp"
#include "./solveAlgo/Basic_Limit_BinarySearch.hpp"
#include "./solveAlgo/NewDP.hpp"

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

std::map<std::string, i64 (*) (i64, i64)> Algorithm {
    {"Basic", Basic},
    {"Basic_Limit", Basic_Limit},
    {"Basic_Limit_BinarySearch", Basic_Limit_BinarySearch},
    {"NewDP", NewDP}
};

i64 gen(i64 l, i64 r) {
    return std::uniform_int_distribution<i64>(l, r)(rng);
}

int main (int argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << "Usage: <Test Type>\n";
        return 1;
    }

    std::string opt = argv[1];

    if (opt == "correctness") {
        for (int n = 1; n <= 300; ++n) {
            for (int m = 1; m <= 300; ++m) {
                i64 ans1 = Basic(n, m);
                i64 ans2 = Basic_Limit(n, m);
                i64 ans3 = Basic_Limit_BinarySearch(n, m);
                i64 ans4 = NewDP(n, m);
                if (ans1 != ans2 || ans2 != ans3 || ans3 != ans4) {
                    std::cout << "Error in: n = " << n << ", " << "m = " << m << "\n";
                    std::cout << "ans = [" << ans1 << ", " << ans2 << ", " << ans3 << ", " << ans4 << "]\n";
                    return 0;
                }
                std::cerr << "\rTest OK" << " (\t" << n << ",\t" << m << ")";
            }
        }
        std::cerr << "\n";
        std::cout << "All tests passed!\n";
    } else if (opt == "efficiency") {
        if (argc < 5) {
            std::cerr << "Usage: <Test Type> <Algorithm> <ML> <MR> <NL = auto> <NR = auto>\n";
        }

        auto algoFunc = Algorithm[argv[2]];

        i64 ML = std::atoll(argv[3]);
        i64 MR = std::atoll(argv[4]);
        if (ML > MR) {
            std::cerr << "Error: ML > MR\n";
            return 1;
        }

        i64 NL = argc > 5 ? std::atoll(argv[5]) : std::__lg(ML);
        i64 NR = argc > 6 ? std::atoll(argv[6]) : std::__lg(MR);
        if (NL > NR) {
            std::cerr << "Error: NL > NR\n";
            return 1;
        }

        double runningTime = 0;
        for (int T = 1; T <= 50; ++T) {
            i64 n = gen(NL, NR);
            i64 m = gen(ML, MR);
            std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
            algoFunc(n, m);
            std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
            runningTime += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0;
        }
        std::cout << "Algorithm: " << argv[2] << "\n";
        std::cout << "Range: [" << NL << ", " << NR << "] + [" << ML << ", " << MR << "]\n";
        std::cout << "Time: " << runningTime / 50.0 << " ms\n";
    } else {
        std::cerr << "Unknown test type: " << opt << "\n";
        std::cerr << "Available options: correctness, efficiency\n";
        return 1;
    }

    return 0;
}