#include <bits/stdc++.h>
#include "./solveAlgo/EK.hpp"
#include "./solveAlgo/Dinic.hpp"

using i64 = long long;

auto Parse (std::string file) {
    std::ifstream fin("./data/" + file + ".in");

    int n, m, s, t;
    fin >> n >> m >> s >> t;
    std::vector<std::tuple<int, int, i64>> edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        i64 cap;
        fin >> u >> v >> cap;
        edges.emplace_back(u, v, cap);
    }
    fin.close();

    return std::make_tuple(n, s, t, edges);
}


int main (int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: <Algorithm> <File>\n";
        return 1;
    }

    std::string algo = argv[1];
    std::string file = argv[2];

    auto [n, s, t, edges] = Parse(file);

    i64 MaxFlow = 0;
    double runningTime = 0.0;

    if (algo == "EK") {
        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        EK<i64> ek(n);
        for (auto [u, v, cap] : edges) {
            ek.add(u, v, cap);
        }
        MaxFlow = ek(s, t);
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        runningTime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0;
    } else if (algo == "Dinic") {
        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        Dinic<i64> dinic(n);
        for (auto [u, v, cap] : edges) {
            dinic.add(u, v, cap);
        }
        MaxFlow = dinic(s, t);
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        runningTime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0;
    } else {
        std::cerr << "Unknown algorithm: " << algo << std::endl;
        return 1;
    }

    std::cout << "Max Flow: " << MaxFlow << std::endl;
    std::cout << "Running Time: " << runningTime << " ms" << std::endl;

    return 0;
}