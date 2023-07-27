#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t nn;
    std::cin >> nn;

    int dd, gcd;
    std::vector<std::vector<int>> triangles(nn);
    for (size_t i = 0; i < nn; ++i) {
        std::vector<int> triangle(3);
        for (auto& length : triangle) {
            std::cin >> length;
        }

        std::sort(triangle.begin(), triangle.end());
        dd = std::gcd(triangle[1], triangle[2]);
        gcd = std::gcd(triangle[0], dd);

        triangles[i] = {triangle[0] / gcd, triangle[1] / gcd, triangle[2] / gcd};
    }

    size_t pp = 1000000033;
    size_t mm = 3 * nn;

    std::vector<std::vector<std::vector<int>>> table(mm);
    size_t num_of_classes = 0;

    for (auto& triangle : triangles) {
        size_t index = (triangle[0] * ((static_cast<uint64_t>(pp) * pp) % mm)
                + static_cast<uint64_t>(triangle[1]) * pp + triangle[2]) % mm;

        if (table[index].empty()) {
            table[index].push_back(triangle);
            num_of_classes += 1;
        } else {

            bool append = true;
            for (auto& triplet : table[index]) {
                if (triangle == triplet) {
                    append = false;
                    break;
                }
            }
            if (append) {
                table[index].push_back(triangle);
                num_of_classes += 1;
            }
        }
    }

    std::cout << num_of_classes << "\n";

    return 0;
}
