#include <bits/stdc++.h>
#include "DSU.hpp"

std::vector<std::array<int, 2>> BurteForce(int n, int m, std::vector<std::array<int, 2>> edges) {
    std::vector<std::array<int, 2>> ans;
    std::vector<std::vector<std::array<int, 2>>> adj(n + 1);
    for (int i = 1; i <= m; ++i) {
        auto [u, v] = edges[i];
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    auto Component = [&](int del) -> int {
        int count = 0;
        std::vector<int> vis(n + 1);
        for (int i = 1; i <= n; ++i) {
            [&](this auto&& dfs, int u) -> void {
                vis[u] = 1;
                for (auto [v, id] : adj[u]) {
                    if (vis[v] || id == del) continue;
                    dfs(v);
                }
            } (i);
        }
        return count;
    };

    int count = Component(0);

    for (int i = 1; i <= m; ++i) {
        if (Component(i) != count) {
            auto [u, v] = edges[i];
            ans.push_back(std::array {u, v});
        }
    }

    return ans;
}