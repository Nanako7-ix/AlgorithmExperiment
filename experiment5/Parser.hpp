#pragma once
#include <bits/stdc++.h>

auto parse(const std::string& file) {
    std::fstream fin("./data/" + file + ".txt");
    int n, m;
    fin >> n >> m;
    std::vector<std::array<int, 2>> edges(m + 1);
    for (int i = 1; i <= m; ++i) {
        fin >> edges[i][0] >> edges[i][1];
        edges[i][0]++, edges[i][1]++;
    }
    return std::tuple {n, m, edges};
}