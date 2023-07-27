#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

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

    std::vector<int> parents_;
    std::vector<int> sizes_;
};

int Director(int aa, const std::vector<int>& directors, DSU* dsu) {
    int parent_a = dsu->GetParent(aa);
    return directors[parent_a];
}

int Process(int aa, int bb, std::vector<int>* directors, DSU* dsu) {
    int parent_a = dsu->GetParent(aa);
    int parent_b = dsu->GetParent(bb);
    if (parent_a != parent_b && ((*directors)[parent_b] == bb)) {
        dsu->Unite(aa, bb);
        if (dsu->sizes_[parent_a] < dsu->sizes_[parent_b]) {
            (*directors)[parent_b] = (*directors)[parent_a];
        }

        return 1;
    } else {
        return 0;
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nn, mm;
    std::string str;
    std::stringstream stream;
    std::getline(std::cin, str);
    stream << str;
    stream >> nn, stream >> mm;

    auto dsu = DSU(nn);
    std::vector<int> directors(nn + 1);
    for (int v = 1; v <= nn; ++v) {
        directors[v] = v;
    }

    for (int ii = 0; ii < mm; ++ii) {
        std::string input;
        std::stringstream ss;
        std::vector<int> data;
        int buf;

        std::getline(std::cin, input);
        ss << input;
        data.reserve(2);
        while (ss >> buf) {
            data.push_back(buf);
        }

        if (data.size() == 1) {
            std::cout << Director(data[0], directors, &dsu) << "\n";
        } else {
            std::cout << Process(data[0], data[1], &directors, &dsu) << "\n";
        }
    }

    return 0;
}
