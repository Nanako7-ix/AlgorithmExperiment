#ifndef DIVIDE_HPP
#define DIVIDE_HPP
#include <bits/stdc++.h>
#include "Point.hpp"
#include "burte_force.hpp"

namespace Divide {
    using i64 = long long;
    using u32 = unsigned int;
    using u64 = unsigned long long;

    /**
     * 分治法求平面最近点对
     * 时间复杂度: O(NlogN)
     * 空间复杂度: O(N)
     */
    double solve(u32 N, std::vector<Point> a) {
        std::sort(a.begin(), a.end(), Comp_X);

        return [&](this auto &&dfs, auto l, auto r) -> double {
            /**
             * 点的数量比较少的时候, 可以暴力判断
             */
            if (r - l <= 3) {
                std::sort(l, r, Comp_Y);
                return BurteForce::solve(r - l, std::vector<Point>(l, r));
            }
        
            /**
             * 因为每次都会排序, 所以需要先保留中位数的点
             */
            auto mid = l + (r - l) / 2;
            Point P = *mid;
        
            /**
             * 每次处理完后是按 Y 有序的
             * 所以直接使用归并排序的思想合并两个有序序列
             * 合并完后又是按 Y 有序的
             * 这部分操作可以在 O(N) 的时间复杂度内完成
             */
            double d = std::min(dfs(l, mid), dfs(mid, r));
            std::inplace_merge(l, mid, r, Comp_Y);
        
            /**
             * 接下来只需要处理 P1 属于左半部分, P2 属于右半部分的情况
             * 那么需要考虑 P1 和 P2 的 X 坐标差值小于 d 的情况
             * 所以只需要计算中轴线 x = P.x 两侧 d 的范围内的点
             */
            std::vector<Point> b;
            for (auto it = l; it != r; ++it) {
                if (std::abs(it -> x - P.x) < d) {
                    b.push_back(*it);
                }
            }
        
            /**
             * 考虑最朴素的方式处理部分的点就是 O(N^2) 的方式处理
             * 但是由于 Y 的差值大于 d 的点不需要考虑
             * 所以可以增加一个限制条件 (b[j].y - b[i].y) < d
             * 容易证明这里最多只需要计算五个点
             * 那么这部分的时间复杂度就是 O(N)
             */
            for (u32 i = 0; i < b.size(); ++i) {
                for (u32 j = i + 1; j < b.size() && (b[j].y - b[i].y) < d; ++j) {
                    d = std::min(d, distance(b[i], b[j]));
                }
            }
            return d;
        } (a.begin(), a.end());
    }
}
#endif