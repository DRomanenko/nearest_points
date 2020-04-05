#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Point {
    int x = 0, y = 0;

    Point() = default;

    Point(const int &_x, const int &_y) : x(_x), y(_y) {}

    bool operator<(const Point &other) const {
        return y < other.y;
    }

    int distTo(const Point &other) const {
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
    }
};

int min_dist = INT32_MAX;
std::vector<Point> points;

void solve(const int &left, const int &right) {
    if (right - left <= 3) {
        for (int i = left; i <= right; ++i)
            for (int q = i + 1; q <= right; ++q)
                min_dist = std::min(min_dist, points[i].distTo(points[q]));
        sort(points.begin() + left, points.begin() + right + 1);
        return;
    }

    const int middle = ((left + right) >> 1);
    const int middle_x = points[middle].x;
    std::vector<Point> help(points.size());
    solve(left, middle);
    solve(middle + 1, right);
    std::merge(points.begin() + left, points.begin() + middle + 1,
               points.begin() + middle + 1, points.begin() + right + 1,
               help.begin());
    std::copy(help.begin(), help.begin() + right - left + 1, points.begin() + left);

    int tmp_size = 0;
    for (int i = left; i <= right; ++i) {
        if (std::abs(points[i].x - middle_x) < min_dist) {
            for (int q = tmp_size - 1; q >= 0 && points[i].y - help[q].y < min_dist; --q)
                min_dist = std::min(min_dist, points[i].distTo(help[q]));
            help[tmp_size++] = points[i];
        }
    }
}

const std::string FILE_NAME = "test";

signed main() {
    // freopen((FILE_NAME + ".in").c_str(), "r", stdin);
    // freopen((FILE_NAME + ".out").c_str(), "w", stdout);
    std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    size_t n;
    std::cin >> n;
    points.resize(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }
    sort(points.begin(), points.end(),
         [](const Point &a, const Point &b) { return a.x < b.x || (a.x == b.x && a.y < b.y); });
    solve(0, (int) points.size() - 1);
    std::cout << min_dist;
    return 0;
}