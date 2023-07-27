#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

struct Point {
    int xx;
    int yy;
};

struct Edge {
    int aa;
    int bb;
    double distance;
};

double Distance(const Point& lhs, const Point& rhs) {
    double xx = lhs.xx, y = lhs.yy;
    double uu = rhs.xx, v = rhs.yy;
    return std::sqrt(((xx - uu) * (xx - uu)) + ((y - v) * (y - v)));
}

bool Less(const Edge& lhs, const Edge& rhs) {
    return lhs.distance < rhs.distance;
}

class DSU {
public:
    explicit DSU(int nn) : parents_(std::vector<int>(nn + 1)), sizes_(std::vector<int>(nn + 1)) {
        for (int vv = 1; vv <= nn; ++vv) {
            parents_[vv] = vv;
        }

        for (int i = 1; i <= nn; ++i) {
            sizes_[i] = 1;
        }
    }

    int GetParent(int vv) {
        std::vector<int> vertices;
        while (parents_[vv] != vv) {
            vertices.push_back(vv);
            vv = parents_[vv];
        }

        for (auto& vertex : vertices) {
            parents_[vertex] = vv;
        }

        return vv;
    }

    void Unite(int uu, int vv) {
        int parent_u = GetParent(uu);
        int parent_v = GetParent(vv);

        if (sizes_[parent_u] >= sizes_[parent_v]) {
            std::swap(parent_u, parent_v);
        }

        parents_[parent_u] = parent_v;
        sizes_[parent_v] += sizes_[parent_u];
    }

    bool InDifferentComponents(int uu, int vv) {
        return GetParent(uu) != GetParent(vv);
    }

private:
    std::vector<int> parents_;
    std::vector<int> sizes_;
};

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nn;
    std::cin >> nn;

    std::vector<Point> points(nn);
    for (auto& point : points) {
        std::cin >> point.xx >> point.yy;
    }

    int mm = (nn * (nn - 1)) / 2;
    std::vector<Edge> edges(mm);

    int kk = 0;
    for (int i = 0; i < nn; ++i) {
        for (int j = i + 1; j < nn; ++j) {
            edges[kk] = {i, j, Distance(points[i], points[j])};
            kk++;
        }
    }

    std::sort(edges.begin(), edges.end(), Less);

    auto dsu = DSU(nn);
    double result = 0;
    int cnt = 0;
    int ee = 0;

    while (cnt != nn - 1) {
        int parent_a = dsu.GetParent(edges[ee].aa);
        int parent_b = dsu.GetParent(edges[ee].bb);
        if (parent_a != parent_b) {
            dsu.Unite(parent_a, parent_b);
            result = edges[ee].distance;
            cnt++;
        }
        ee++;
    }

    std::cout << std::fixed << std::setprecision(10) << result << "\n";

    return 0;
}
