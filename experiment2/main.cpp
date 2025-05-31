#include <bits/stdc++.h>
#include "Tester.hpp"
#include "burte_force.hpp"
#include "divide.hpp"
#include "NoDivide.hpp"

int main () {
    freopen("output.txt", "w", stdout);
    for (u32 N = 100000; N <= 1000000; N += 100000) {
        std::cout << "N = " << N << std::endl;
        std::cout << Test(N, BurteForce::solve) << std::endl;
        std::cout << Test(N, Divide::solve) << std::endl;
        std::cout << Test(N, NoDivide::solve) << std::endl;
        std::cout << std::endl;
    }
}