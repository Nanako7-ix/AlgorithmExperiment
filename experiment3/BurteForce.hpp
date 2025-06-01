#pragma once
#include <bits/stdc++.h>

int BurteForce(const int n, const std::vector<std::vector<int>>& adj, const int count) {
    std::vector<int> col(n + 1);
    auto check = [&]() -> bool {
        for (int u = 1; u <= n; ++u) {
            for (auto v : adj[u]) {
                if (col[u] == col[v]) {
                    return false;
                }
            }
        }
        return true;
    };

    int ans = 0;
    [&](this auto&& dfs, int i) -> void {
        if (i == n + 1) {
            if (check()) ans++;
            return;
        }
        for (int c = 1; c <= count; ++c) {
            col[i] = c;
            dfs(i + 1);
            if (ans != 0) return;
        }
        col[i] = 0;
    } (1);

    return ans;
}