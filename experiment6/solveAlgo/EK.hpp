#include <bits/stdc++.h>

template<typename Flow>
struct EK {
    struct Edge {
        int to;
        Flow cap;
        Edge(int to, Flow cap) : to(to), cap(cap) {}
    };

    int n;
    std::vector<Edge> e;
    std::vector<std::vector<int>> adj;
    std::vector<int> pre;

    EK(int n) : n(n) {
        adj.assign(n, {});
    }

    void add(int u, int v, Flow cap) {
        assert(u > 0 && v > 0);
        u--, v--;
        adj[u].push_back(e.size());
        e.emplace_back(v, cap);
        adj[v].push_back(e.size());
        e.emplace_back(u, 0);
    }

    Flow bfs(int s, int t) {
        pre.assign(n, 0);

        std::vector<Flow> dp(n);
        dp[s] = std::numeric_limits<Flow>::max();
        std::queue<int> q;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int i : adj[u]) {
                auto [v, cap] = e[i];
                if(dp[v] || cap == 0) continue;
                q.push(v);
                dp[v] = std::min(cap, dp[u]);
                pre[v] = i;
                if(v == t) return dp[t];
            }
        }
        return 0;
    }

    Flow operator() (int s, int t) {
        s--, t--;
        Flow ans = 0;
        for (Flow aug = bfs(s, t); aug != 0; aug = bfs(s, t)) {
            for (int u = t; u != s; u = e[pre[u] ^ 1].to) {
                e[pre[u]].cap -= aug;
                e[pre[u] ^ 1].cap += aug;
            }
            ans += aug;
        } 
        return ans;
    }
};