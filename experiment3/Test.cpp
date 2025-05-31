/**
 * Author:  Thephix
 * Created: 2025/05/29 14:59:55
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include "parse.hpp"
#include "BurteForce.hpp"
#include "DH.hpp"
#include "ForwardCheck.hpp"
#include "MRV_ForwardCheck.hpp"
#include "ColorPolling.hpp"

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using i128 = __int128;
using u128 = unsigned __int128;
using f64 = double;
using f128 = __float128;


void solve() {
    auto [n, adj] = parse("sample_4a.col");
    std::cerr << "pares done\n";
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    auto ans = DH(n, adj, 4);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << ans << "\n";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "\n";
}

signed main() {
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T = 1;
    // std::cin >> T;

    while (T--) {
        solve ();
    }

    return 0;
}