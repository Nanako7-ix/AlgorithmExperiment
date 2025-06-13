#pragma once
#include <bits/stdc++.h>

class DSU {
private:
    int n, cnt;
    std::vector<int> pre, siz;
public:
    DSU () = default;

    DSU (int n) { init(n); }

    void init (int n) {
        this -> n = n;
        cnt = n;
        pre.resize(n + 1);
        siz.assign(n + 1, 1);
        std::iota(pre.begin(), pre.end(), 0);
    }

    int find(int x) {
        if(pre[x] == x) return x;
        return pre[x] = find(pre[x]);
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        cnt--, siz[x] += siz[y], pre[y] = x;
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int count() const {
        return cnt;
    }
};

class rollDSU {
private:
    int n, cnt;
    std::vector<int> pre, dep, his;
    std::vector<std::pair<int&, int>> preh, deph;
public:
    rollDSU () = default;

    rollDSU (int n) { init(n); }

    void init(int n) {
        this -> n = n;
        cnt = n;
        pre.resize(n + 1);
        dep.assign(n + 1, 1);
        std::iota(pre.begin(), pre.end(), 0);
    }

    int find (int x) {
        if (pre[x] == x) return x;
        return find(pre[x]);
    }
    
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (dep[x] < dep[y]) std::swap(x, y);
        preh.emplace_back(pre[y], pre[y]);
        deph.emplace_back(dep[x], dep[x]);
        his.push_back(cnt);
        if (x == y) return false;
        dep[x] += dep[x] == dep[y];
        pre[y] = x, cnt--;
        return true;
    }

    void roll() {
        cnt = his.back();
        preh.back().first = preh.back().second;
        deph.back().first = deph.back().second;        
        his.pop_back();
        preh.pop_back();
        deph.pop_back();
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int count() const {
        return cnt;
    }
};