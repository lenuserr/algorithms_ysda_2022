#include <iostream>
#include <vector>

std::vector<std::vector<int>> ReadVectors(int length, int l) {
    std::vector<std::vector<int>> result;
    for (int i = 0; i < length; ++i) {
        std::vector<int> new_sequence(l);
        for (auto &it: new_sequence) {
            std::cin >> it;
        }
        result.push_back(new_sequence);
    }
    return result;
}

int BinarySearchSolution(const std::vector<int>& upper, const std::vector<int>& lower, int l) {
    int left = 0;
    int right = l - 1;
    int middle;
    while (left < right) {
        middle = (left + right) / 2;
        if (upper[middle] >= lower[middle]) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    int k = left + 1;
    if (k > 1 && std::max(upper[k - 2], lower[k - 2]) < std::max(upper[k - 1], lower[k - 1])) {
        k -= 1;
    }
    return k;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> vec(3);
    for (auto& it : vec)
        std::cin >> it;

    int n = vec[0], m = vec[1], l = vec[2];

    std::vector<std::vector<int>> A = ReadVectors(n, l);
    std::vector<std::vector<int>> B = ReadVectors(m, l);

    int q;
    std::cin >> q;
    int i, j;
    for (int request = 0; request < q; ++request) {
        std::cin >> i >> j;
        std::cout << BinarySearchSolution(A[i - 1], B[j - 1], l) << "\n";
    }

    return 0;
}
