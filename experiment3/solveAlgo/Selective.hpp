#pragma once
#include <bits/stdc++.h>

int Selective(const int n, const std::vector<std::vector<int>>& adj, const int count,
              const bool find_first = false) {
    std::vector<int> col(n + 1);
    auto check = [&](int u, int c) -> bool {
        for (auto v : adj[u]) {
            if (col[v] != 0 && c == col[v]) {
                return false;
            }
        }
        return true;
    };

    int ans = 0;
    [&](this auto&& dfs, int i) -> void {
        if (i == n + 1) {
            ans++;
            return;
        }
        for (int c = 1; c <= count; ++c) {
            if (!check(i, c)) continue;
            col[i] = c;
            dfs(i + 1);
            if (ans != 0) return;
        }
        col[i] = 0;
    } (1);

    return ans;
}