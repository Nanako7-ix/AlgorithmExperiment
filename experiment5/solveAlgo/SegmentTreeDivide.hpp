#include <bits/stdc++.h>
#include "DSU.hpp"

std::vector<std::array<int, 2>> SegmentTreeDivide(int n, int m, std::vector<std::array<int, 2>> edges) {
    std::vector<std::array<int, 2>> ans;

    int base = [&]() {
        DSU dsu(n);
        for (int i = 1; i <= m; ++i) {
            auto [u, v] = edges[i];
            dsu.merge(u, v);
        }
        return dsu.count();
    } ();

    std::vector<std::vector<int>> seg(4 << std::__lg(m));
    for (int i = 1; i <= m; ++i) {
        if (i != 1) {
            [&](this auto&& modify, int u, int l, int r) -> void {
                if (1 <= l && r <= i - 1) {
                    seg[u].push_back(i);
                    return;
                }
                int mid = (l + r) >> 1;
                if (1 <= mid) {
                    modify(u << 1, l, mid);
                }
                if (i - 1 > mid) {
                    modify(u << 1 | 1, mid + 1, r);
                }
            } (1, 1, m);
        }
        if (i != m) {
            [&](this auto&& modify, int u, int l, int r) -> void {
                if (i + 1 <= l && r <= m) {
                    seg[u].push_back(i);
                    return;
                }
                int mid = (l + r) >> 1;
                if (i + 1 <= mid) {
                    modify(u << 1, l, mid);
                }
                if (m > mid) {
                    modify(u << 1 | 1, mid + 1, r);
                }
            } (1, 1, m);
        }
    }

    rollDSU dsu(n);
    [&](this auto&& dfs, int u, int l, int r) -> void {
        for (auto i : seg[u]) {
            dsu.merge(edges[i][0], edges[i][1]);
        }
        if (dsu.count() != base) {
            if (l == r) {
                ans.push_back(edges[l]);
            } else {
                int m = (l + r) >> 1;
                dfs(u << 1, l, m);
                dfs(u << 1 | 1, m + 1, r);
            }
        }
        for (int i = 0; i < (int) seg[u].size(); ++i) {
            dsu.roll();
        }
    } (1, 1, m);

    return ans;
}