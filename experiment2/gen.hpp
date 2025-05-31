#ifndef GEN_HPP
#define GEN_HPP

#include <bits/stdc++.h>
#include "Point.hpp"

using u32 = unsigned int;
using u64 = unsigned long long;

const u64 Mod = 1000000000;

static std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

i64 genNumber() {
    u64 x = rng() % Mod;
    if (rng() % 2 == 1) {
        x *= -1;
    }
    return x;
}

std::vector<Point> Generate(u32 N) {
    std::vector<Point> data(N);
    for (u32 i = 0; i < N; ++i) {
        data[i] = Point { genNumber(), genNumber() };
    }
    return data;
}

#endif