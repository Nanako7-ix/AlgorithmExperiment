#ifndef TESTER_HPP
#define TESTER_HPP

#include <bits/stdc++.h>
#include "burte_force.hpp"
#include "Point.hpp"
#include "gen.hpp"

using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

u64 Test(u32 N, double (*func)(u32, std::vector<Point>)) {
    std::vector<Point> data = Generate(N);
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    func(N, data);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // 验证正确性
    // assert(ans == BurteForce::solve(N, data));
    // std::cout << std::fixed << std::setprecision(12) << ans << std::endl;
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

#endif