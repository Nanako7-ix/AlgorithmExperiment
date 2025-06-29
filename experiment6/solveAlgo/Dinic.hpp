#include <bits/stdc++.h>

template<typename Flow>
struct Dinic {
    struct Edge {
        int to;
        Flow cap;
        Edge(int to, Flow cap) : to(to), cap(cap) {}
    };

    int n;
    Flow maxflow;
    std::vector<Edge> e;
    std::vector<std::vector<int>> adj;
    std::vector<int> cur, h;

    Dinic (int n) : n(n) {
        adj.assign(n, {});
        cur.resize(n);
        h.resize(n);
    }

    void add(int u, int v, Flow cap) {
        assert(u > 0 && v > 0);
        u--, v--;
        adj[u].push_back(e.size());
        e.emplace_back(v, cap);
        adj[v].push_back(e.size());
        e.emplace_back(u, 0);
    }

    bool bfs(int s, int t) {
        h.assign(n, 0);

        std::queue<int> q;
        h[s] = 1, q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int i : adj[u]) {
                auto [v, cap] = e[i];
                if(cap == 0 || h[v] != 0) continue;
                h[v] = h[u] + 1;
                if(v == t) return true;
                q.push(v);
            }
        }
        return false;
    }

    Flow dfs(int u, int t, Flow flow) {
        if(u == t) return flow;
        Flow rest = flow;
        for (int& i = cur[u]; i < (int) adj[u].size(); ++i) {
            const int j = adj[u][i];
            auto [v, cap] = e[j];
            if(cap > 0 && h[v] == h[u] + 1) {
                Flow aug = dfs(v, t, std::min(rest, cap));
                e[j].cap -= aug;
                e[j ^ 1].cap += aug;
                rest -= aug;
                if(rest == 0) return flow;
            }
        }
        return flow - rest;
    }

    Flow operator() (int s, int t) {
        s--, t--;
        Flow ans = 0;
        while(bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<Flow>::max());
        }
        return ans;
    }
};