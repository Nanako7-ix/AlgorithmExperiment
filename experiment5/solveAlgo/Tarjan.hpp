#include <bits/stdc++.h>

struct EDCC {
    int n;
    std::vector<std::vector<std::array<int, 2>>> adj;
    std::vector<std::array<int, 2>> bridges;
    std::vector<int> dep, low;
    int cur, edges;

    EDCC () = default;
    EDCC (int n) {
        init(n);
    }

    void init (int n) {
        this -> n = n;
        adj.assign(n + 1, {});
        dep.assign(n + 1, 0);
        low.assign(n + 1, 0);
        cur = edges = 0;
    }

    void add (int u, int v) {
        adj[u].push_back({v, edges++});
        adj[v].push_back({u, edges++});
    }

    void tarjan (int u, int in) {
        low[u] = dep[u];
        for (auto [v, out] : adj[u]) {
            if ((out ^ in) == 1) continue;
            if (dep[v] == 0) {
                dep[v] = dep[u] + 1;
                tarjan(v, out);
                low[u] = std::min(low[u], low[v]);
                if (dep[u] < low[v]) {
                    bridges.push_back({u, v});
                }
            } else {
                low[u] = std::min(low[u], dep[v]);
            }
        }
    }

    std::vector<std::array<int, 2>> work () {
        for (int i = 1; i <= n; ++i) {
            if (dep[i] == 0) {
                dep[i] = 1;
                tarjan(i, -1);
            }
        }
        return bridges;
    }
};

std::vector<std::array<int, 2>> Tarjan (int n, int m, std::vector<std::array<int, 2>> edges) {
    EDCC edcc(n);
    for (int i = 1; i <= m; ++i) {
        auto [u, v] = edges[i];
        edcc.add(u, v);
    }
    auto ans = edcc.work();
    for (auto& [u, v] : ans) {
        if (u > v) std::swap(u, v);
    }
    std::sort(ans.begin(), ans.end());
    return ans;
}