#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <iomanip>

std::pair<double, double> CalculateSegment(const std::pair<int, int>& point, double radius) {
    std::pair<double, double> segment;
    double root_first = point.first + sqrt(radius * radius - point.second * point.second);
    double root_second = point.first - sqrt(radius * radius - point.second * point.second);
    segment = {std::min(root_first, root_second), std::max(root_first, root_second)};
    return segment;
}

struct Segment {
    double coordinate;
    int flag;
};

bool Less(const Segment& lhs, const Segment& rhs) {
    double eps = 0.000001;
    if (lhs.coordinate - rhs.coordinate > eps) {
        return lhs.coordinate < rhs.coordinate;
    }
    if (rhs.coordinate - lhs.coordinate > eps) {
        return lhs.coordinate < rhs.coordinate;
    }
    return lhs.flag > rhs.flag;
}

int IntersectionSegments(const std::vector<std::pair<double, double>>& segments) {

    if (segments.empty()) {
        return 0;
    }

    std::vector<Segment> coordinates;
    for (const auto& segment : segments) {
        coordinates.push_back({segment.first, 1});
        coordinates.push_back({segment.second, -1});
    }

    std::sort(coordinates.begin(), coordinates.end(), Less);

    int cnt = 0;
    int max_cnt = 0;
    for (const auto& coordinate : coordinates) {
        cnt += coordinate.flag;
        max_cnt = std::max(max_cnt, cnt);
    }

    return max_cnt;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nn, kk;
    std::cin >> nn >> kk;
    std::vector<std::pair<int, int>> points(nn);
    for (int i = 0; i < nn; ++i) {
        int xx, yy;
        std::cin >> xx >> yy;
        std::pair<int, int> point = {xx, yy};
        points[i] = point;
    }


    double left = 0;
    double right = 1437.228322;
    double eps = 0.000001;

    while (std::fabs(right - left) >= eps) {
        double mid = (left + right) / 2;

        std::vector<std::pair<double, double>> segments;
        for (int i = 0; i < nn; ++i) {
            double dd = 4 * (mid * mid - points[i].second * points[i].second);
            if (dd >= eps) {
                segments.push_back(CalculateSegment(points[i], mid));
            }
        }

        if (IntersectionSegments(segments) >= kk) {
            right = mid;
        } else {
            left = mid;
        }
    }

    std::cout << std::fixed << std::setprecision(6) << (left + right) / 2 << "\n";

    return 0;
}
