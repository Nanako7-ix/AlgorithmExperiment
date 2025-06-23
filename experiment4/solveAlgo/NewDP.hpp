#pragma once

#include <bits/stdc++.h>
using i64 = long long;

i64 NewDP(i64 n, i64 m) {
    if (n >= std::__lg(m) + 1) {
        return std::__lg(m) + 1;
    }

    if (n == 1) return m;

    std::vector<i64> dp(n + 1, 1);
    dp[0] = 0;

    for (int x = 1; true; ++x) {
        if (dp[n] >= m) return x;
        for (i64 i = n; i >= 1; --i) {
            dp[i] += dp[i - 1] + 1;
        }
    }
}