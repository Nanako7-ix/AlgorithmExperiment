#pragma once
#include <bits/stdc++.h>

int ColorPolling(const int n, const std::vector<std::vector<int>>& adj, const int count,
                 const bool find_first = false) {
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
    [&](this auto&& dfs, int i, std::bitset<30> used_colors) -> void {
        if (i == n + 1) {
            ans += used_colors.count();
            return;
        }

        int u = 0, Min = count + 1;
        for (int i = 1; i <= n; ++i) {
            if (col[id[i]] != 0) continue;
            if (count - (int) colors_set[id[i]].count() < Min) {
                Min = count - colors_set[id[i]].count();
                u = id[i];
            }
        }

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
            if (ok) {
                dfs(i + 1, used_colors | std::bitset<30>(1 << c));
                if (find_first && ans != 0) return;
            }
            for (auto v : adj[u]) {
                cnt[v][c]--;
                if (cnt[v][c] == 0) {
                    colors_set[v][c] = 0;
                }
            }
            col[u] = 0;
        }
    } (1, {});

    return ans;
}