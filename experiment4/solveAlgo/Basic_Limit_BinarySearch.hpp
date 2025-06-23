#pragma once

#include <bits/stdc++.h>
using i64 = long long;

i64 Basic_Limit_BinarySearch(i64 n, i64 m) {
    if (n >= std::__lg(m) + 1) {
        return std::__lg(m) + 1;
    }

    std::vector<i64> dp(m + 1);
    std::iota(dp.begin(), dp.end(), 0);
    for (i64 i = 2; i <= n; ++i) {
        std::vector<i64> ndp(m + 1, 0x3f3f3f3f3f3f3f3f);
        ndp[0] = 0;
        for (i64 j = 1; j <= m; ++j) {
            i64 l = 1, r = j, x0 = -1;
            while (l <= r) {
                i64 x = (l + r) >> 1;
                if (ndp[j - x] >= dp[x - 1]) {
                    x0 = x, l = x + 1;
                } else r = x - 1;
            }
            assert(x0 != -1);
            ndp[j] = std::min(ndp[j - x0], dp[x0]) + 1;
        }
        std::swap(dp, ndp);
    }
    return dp[m];
}