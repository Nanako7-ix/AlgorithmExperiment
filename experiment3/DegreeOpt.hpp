#pragma once
#include <bits/stdc++.h>

int DegreeOpt(const int n, const std::vector<std::vector<int>>& adj, const int count) {
    std::vector<int> col(n + 1), deg(n + 1);

    auto check = [&](int u, int c) -> bool {
        for (auto v : adj[u]) {
            if (col[v] != 0 && c == col[v]) {
                return false;
            }
        }
        return true;
    };

    for (int u = 1; u <= n; ++u) {
        for (auto v : adj[u]) {
            deg[u]++, deg[v]++;
        }
    }
    std::vector<int> id(n + 1);
    std::iota(id.begin(), id.end(), 0);
    std::sort(id.begin() + 1, id.end(), [&](int x, int y) {
        return deg[x] > deg[y];
    });

    int ans = 0;
    [&](this auto&& dfs, int i) -> void {
        if (i == n + 1) {
            ans++;
            return;
        }
        int u = id[i];
        for (int c = 1; c <= count; ++c) {
            if (!check(u, c)) continue;
            col[u] = c;
            dfs(i + 1);
            if (ans != 0) return;
        }
        col[u] = 0;
    } (1);

    return ans;
}