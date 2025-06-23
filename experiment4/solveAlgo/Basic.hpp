#pragma once

#include <bits/stdc++.h>
using i64 = long long;

i64 Basic (i64 n, i64 m) {
    std::vector<i64> dp(m + 1);
    std::iota(dp.begin(), dp.end(), 0);
    for (i64 i = 2; i <= n; ++i) {
        std::vector<i64> ndp(m + 1, 0x3f3f3f3f3f3f3f3f);
        ndp[0] = 0;
        for (i64 j = 1; j <= m; ++j) {
            for (i64 x = 1; x <= j; ++x) {
                ndp[j] = std::min(ndp[j], std::max(dp[x - 1], ndp[j - x]) + 1);
            }
        }
        std::swap(dp, ndp);
    }
    return dp[m];
}