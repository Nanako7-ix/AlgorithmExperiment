#pragma once
#include <bits/stdc++.h>

int ForwardCheck(const int n, const std::vector<std::vector<int>>& adj, const int count) {
    std::vector<int> col(n + 1), deg(n + 1);
    std::vector<std::bitset<30>> colors_set(n + 1);
    std::vector<std::vector<int>> cnt(n + 1, std::vector<int>(count + 1));

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
            if (colors_set[u][c]) continue;
            col[u] = c;
            int ok = 1;
            for (auto v : adj[u]) {
                colors_set[v][c] = 1;
                cnt[v][c]++;
                if ((int) colors_set[v].count() == count) {
                    ok = 0;
                }
            }
            if (ok) dfs(i + 1);
            for (auto v : adj[u]) {
                cnt[v][c]--;
                if (cnt[v][c] == 0) {
                    colors_set[v][c] = 0;
                }
            }
            col[u] = 0;
        }
    } (1);

    return ans;
}