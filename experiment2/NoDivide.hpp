#ifndef NODIVIDE_HPP
#define NODIVIDE_HPP
#include <bits/stdc++.h>
#include "Point.hpp"

namespace NoDivide {
    using i64 = long long;
    using u32 = unsigned int;
    using u64 = unsigned long long;
    constexpr double inf = 4E18;

    struct Compare {
        bool operator()(const Point& p1, const Point& p2) const {
            if (p1.y == p2.y) {
                return p1.x < p2.x;
            } return p1.y < p2.y;
        }
    };

    double solve(u32 N, std::vector<Point> a) {
        sort(a.begin(), a.end(), [](Point p1, Point p2) {
            if (p1.x == p2.x) {
                return p1.y < p2.y;
            } return p1.x < p2.x;
        });
        std::multiset<Point, Compare> S;
        
        double ans = inf;
        for (u32 i = 0, j = 0; i < N; ++i) {
            while (j < i && a[i].x - a[j].x >= ans) {
                S.erase(S.find(a[j++]));
            }
            for (
                auto it = S.lower_bound(Point(a[i].x, a[i].y - ans));
                it != S.end() && it -> y < a[i].y + ans;
                ++it
            ) {
                ans = std::min(ans, distance(a[i], *it));
            }
            S.insert(a[i]);
        }

        return ans;
    }
}
#endif