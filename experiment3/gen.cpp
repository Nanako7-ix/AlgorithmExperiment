#pragma once
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n, cnt;
    std::vector<int> f, siz;

    DSU() = default;
    DSU(int n) { init(n); }

    void init(int n) {
        this -> n = n;
        cnt = n;
        f.resize(n + 1);
        siz.assign(n + 1, 1);
        std::iota(f.begin(), f.end(), 0);
    }

    int find(int x) {
        if(f[x] == x) return x;
        return f[x] = find(f[x]);
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return 0;
        cnt--, siz[x] += siz[y];
        return f[y] = x;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return siz[find(x)];
    }

    int count() const {
        return cnt;
    }
};

int genNumber(int l, int r) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(l, r)(rng);
}

// Generate a 2D connected graph
int main (int argc, char *argv[]) {
    freopen("./data/gen.col", "w", stdout);
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <n>\n";
        cerr << "n >= 4\n";
        return 1;
    }
    int n = atoi(argv[1]);
    assert(n >= 4);

    vector<int> col(n + 1);
    col[1] = 1, col[2] = 2, col[3] = 3, col[4] = 4;
    for (int i = 5; i <= n; i++) {
        col[i] = genNumber(1, 4);
    }
    
    vector<array<int, 2>> edges;
    int m = genNumber(n - 1, 3 * n - 6);
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int u = genNumber(1, n);
        int v = genNumber(1, n);
        const int attempts = 100;
        for (int j = 0; j < attempts && col[u] == col[v]; j++) {
            v = genNumber(1, n);
        }
        if (col[u] == col[v]) continue;
        if (u > v) swap(u, v);
        edges.push_back({u, v});
        dsu.merge(u, v);
    }

    // Ensure the graph is connected
    if (dsu.count() > 1) {
        edges.push_back({1, 2}), dsu.merge(1, 2);
        edges.push_back({1, 3}), dsu.merge(1, 3);
        edges.push_back({1, 4}), dsu.merge(1, 4);
        for (int i = 5; i <= n; i++) {
            if (dsu.find(i) != dsu.find(1)) {
                edges.push_back({col[i], i});
                dsu.merge(col[i], i);
            }
        }
    }

    // erase multiple edges
    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());

    cout << "p edge" << n << ' ' << edges.size() << "\n";
    for (auto [u, v] : edges) {
        cout << "e " << u << ' ' << v << "\n";
    }
}