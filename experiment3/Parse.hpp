#pragma once
#include <bits/stdc++.h>

auto parse(const std::string& input) {
    std::fstream fin("./data/" + input);
    int n, m;
    while (true) {
        std::string line;
        std::getline(fin, line);
        if (line.empty()) continue;
        if (line[0] == 'p') {
            std::istringstream iss(line);
            std::string _;
            iss >> _ >> _ >> n >> m;
            break;
        }
    }
    std::vector<std::vector<int>> adj(m);
    for (int i = 0; i < m; ++i) {
        char _; int u, v;
        fin >> _ >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    return std::tuple {n, adj};
}