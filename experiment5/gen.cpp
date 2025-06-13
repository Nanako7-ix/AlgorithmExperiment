#include <bits/stdc++.h>

int main (int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: <n> <m>\n";
        return 1;
    }

    int n = std::atoi(argv[1]);
    int m = std::atoi(argv[2]);

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::set<std::array<int, 2>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = rng() % n;
        int v = rng() % n;
        if (u > v) std::swap(u, v);
        if (edges.contains({u, v})) {
            u = rng() % n;
            v = rng() % n;
            if (u > v) std::swap(u, v);
        }
        edges.insert({u, v});
    }

    std::cout << n << " " << m << "\n";
    for (auto edge : edges) {
        std::cout << edge[0] << " " << edge[1] << "\n";
    }
    return 0;
}