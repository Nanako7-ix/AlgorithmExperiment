#include <bits/stdc++.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: <n>\n";
        return 1;
    }

    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    
    int n = std::atoi(argv[1]);
    int m = (n * (n - 1)) / 1;
    int S = n + m + 1, T = S + 1, tot = 1;
    
    std::cout << n + m + 2 << ' ' << 3 * m + n << ' ' << S << ' ' << T << "\n";
    
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            std::cout << S << ' ' << tot << ' ' << rng() << "\n";
            std::cout << tot << ' ' << i + m << ' ' << rng() << "\n";
            std::cout << tot << ' ' << j + m << ' ' << rng() << "\n";
            tot++;
        }
        std::cout << i + m << ' ' << T << ' ' << rng() << "\n";
    }

    return 0;
}