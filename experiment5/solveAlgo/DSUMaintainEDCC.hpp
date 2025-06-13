#include <bits/stdc++.h>
#include "DSU.hpp"

std::vector<std::array<int, 2>> DSUMaintainEDCC(int n, int m, std::vector<std::array<int, 2>> edges) {
    int cnt = 0;
    DSU dsu(n);
    std::vector<std::vector<std::array<int, 2>>> adj(n + 1);
    for (int i = 1; i <= m; ++i) {
        auto [u, v] = edges[i];
        adj[u].push_back({v, cnt++});
        adj[v].push_back({u, cnt++});
    }
    std::vector<int> vis(n + 1), fa(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (vis[i] == 0) {
            [&](this auto&& tarjan, int u, int in) -> void {
                vis[u] = 1;
                for (auto [v, out] : adj[u]) {
                    if ((in ^ out) == 1) continue;
                    if (vis[v] == 0) {
                        fa[v] = dsu.find(u);
                        tarjan(v, out);
                    } else {
                        // 返祖边
                        for (int x = dsu.find(u); x != dsu.find(v); x = dsu.find(fa[x])) {
                            
                            dsu.merge(v, x);
                        }
                    }
                }
            } (i, -1);
        }
    }
    std::vector<std::array<int, 2>> ans;
    for (int i = 1; i <= m; ++i) {
        auto [u, v] = edges[i];
        if (!dsu.same(u, v)) {
            ans.push_back({u, v});
        }
    }
    return ans;
}