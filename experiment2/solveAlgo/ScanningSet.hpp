#pragma once
#include <bits/stdc++.h>
#include "../Point.hpp"

struct Compare {
    bool operator()(const Point& p1, const Point& p2) const {
        if (p1.y == p2.y) {
            return p1.x < p2.x;
        } return p1.y < p2.y;
    }
};

double ScanningSet(std::vector<Point> a) {
    sort(a.begin(), a.end(), [](Point p1, Point p2) {
        if (p1.x == p2.x) {
            return p1.y < p2.y;
        } return p1.x < p2.x;
    });

    std::multiset<Point, Compare> S;
    
    int n = a.size();
    double ans = inf;
    for (int i = 0, j = 0; i < n; ++i) {
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