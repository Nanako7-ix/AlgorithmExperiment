#pragma once
#include <bits/stdc++.h>

using i64 = long long;
struct Point {
    i64 x, y;
    Point() {
        x = y = i64 {};
    }
    Point(i64 x, i64 y) {
        this -> x = x;
        this -> y = y;
    }
};

constexpr double inf = 4E18;

double distance(Point p1, Point p2) {
    return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

bool Comp_X(Point p1, Point p2) {
    return p1.x < p2.x;
}

bool Comp_Y(Point p1, Point p2) {
    return p1.y < p2.y;
}