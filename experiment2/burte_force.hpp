#ifndef BURTE_FORCE_HPP
#define BURTE_FORCE_HPP
#include <bits/stdc++.h>
#include "Point.hpp"

namespace BurteForce {
    using i64 = long long;
    using u32 = unsigned int;
    using u64 = unsigned long long;
    constexpr double inf = 4E18;
    
    /**
     * 暴力求平面最近点对
     * 如果只有一个点, 返回无穷大
     * 否则暴力枚举所有的二元组 (i, j), 计算 Pi 和 Pj 之间的距离
     * 时间复杂度: O(N^2)
     */
    double solve(u32 N, std::vector<Point> a) {
        if (N == 1) return inf;
        double ans = inf;
        for (u32 i = 0; i < N; ++i) {
            for (u32 j = i + 1; j < N; ++j) {
                ans = std::min(ans, distance(a[i], a[j]));
            }
        }
        return ans;
    }
}
#endif