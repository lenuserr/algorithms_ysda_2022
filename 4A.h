#include <iostream>
#include <vector>
#include <algorithm>

struct Element {
    int value;
    int index;
};

int NumTrees(const std::vector<Element>& roots, const std::vector<std::vector<int>>& dp) {
    if (roots.size() < 2) {
        return 1;
    }

    int mm = static_cast<int>(roots.size());
    int64_t total = 0;
    int64_t mod = 123456789;

    std::vector<Element> unique_roots = {roots[0]};
    for (auto root : roots) {
        if (root.value != unique_roots.back().value) {
            unique_roots.push_back(root);
        }
    }

    int ll = roots[0].index;
    int rr = roots[mm - 1].index;
    for (const auto& root : unique_roots) {
        int ii = root.index - 1;
        int64_t left_subtree = 1;
        if (ii >= ll) {
            left_subtree = dp[ll][ii];
        }
        int jj = root.index + 1;
        int64_t right_subtree = 1;
        if (jj <= rr) {
            right_subtree = dp[jj][rr];
        }
        total = (total + (left_subtree * right_subtree)) % mod;
    }

    return static_cast<int>(total);
}

int Solution(const std::vector<Element>& nums) {
    int nn = static_cast<int>(nums.size());
    std::vector<std::vector<int>> dp(nn, std::vector<int>(nn, 0));

    for (int i = 0; i < nn; ++i) {
        for (int j = 0; j < nn - i; ++j) {
            auto roots = std::vector<Element>(nums.begin() + j, nums.begin() + j + i + 1);
            dp[j][j + i] = NumTrees(roots, dp);
        }
    }

    return dp[0][nn - 1];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nn;
    std::cin >> nn;
    std::vector<int> numbers(nn);

    for (auto& it : numbers) {
        std::cin >> it;
    }

    std::sort(numbers.begin(), numbers.end());
    std::vector<Element> nums(nn);
    for (int i = 0; i < nn; ++i) {
        nums[i] = {numbers[i], i};
    }

    std::cout << Solution(nums) << "\n";

    return 0;
}
