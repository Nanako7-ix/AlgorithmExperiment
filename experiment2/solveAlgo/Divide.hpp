#pragma once
#include <bits/stdc++.h>
#include "../Point.hpp"
#include "BurteForce.hpp"

double Divide(std::vector<Point> a) {
    std::sort(a.begin(), a.end(), Comp_X);

    return [&](this auto &&dfs, auto l, auto r) -> double {
        if (r - l <= 3) {
            std::sort(l, r, Comp_Y);
            return BurteForce(std::vector<Point>(l, r));
        }

        auto mid = l + (r - l) / 2;
        Point P = *mid;

        double d = std::min(dfs(l, mid), dfs(mid, r));
        std::inplace_merge(l, mid, r, Comp_Y);

        std::vector<Point> b;
        for (auto it = l; it != r; ++it) {
            if (std::abs(it -> x - P.x) < d) {
                b.push_back(*it);
            }
        }
        for (int i = 0; i < (int) b.size(); ++i) {
            for (int j = i + 1; j < (int) b.size() && (b[j].y - b[i].y) < d; ++j) {
                d = std::min(d, distance(b[i], b[j]));
            }
        }
        return d;
    } (a.begin(), a.end());
}