#pragma once
#include <bits/stdc++.h>
#include "../Point.hpp"
    
double BurteForce(std::vector<Point> a) {
    int n = a.size();
    double ans = inf;
    if (n != 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ans = std::min(ans, distance(a[i], a[j]));
            }
        }
    }
    return ans;
}