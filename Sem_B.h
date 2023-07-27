#include <iostream>
#include <vector>
#include <algorithm>

int64_t Calculate(const std::vector<int64_t>& left,
                  const std::vector<int64_t>& right, int64_t Left) { // [Left; +inf)
    auto ll = left.begin();
    auto rr = right.begin();

    int64_t cnt = 0;

    while (ll != left.end() && rr != right.end()) {
        while ((rr != right.end()) && (*rr - *ll < Left)) {
            ++rr;
        }
        cnt += static_cast<int64_t>(right.end() - rr);
        ++ll;
    }
    return cnt;
}

template <class Iterator>
std::vector<int64_t> Merge(Iterator lhs_first, Iterator lhs_last,
                           Iterator rhs_first, Iterator rhs_last, int64_t* cnt, int64_t Left) {

    std::vector<int64_t> left(lhs_first, lhs_last);
    std::vector<int64_t> right(rhs_first, rhs_last);
    *cnt += Calculate(left, right, Left);

    size_t size_merge = (lhs_last - lhs_first) + (rhs_last - rhs_first);
    std::vector<int64_t> merge_result(size_merge);

    int index = 0;
    while (lhs_first != lhs_last && rhs_first != rhs_last) {
        if (*lhs_first <= *rhs_first) {
            merge_result[index] = *lhs_first;
            ++lhs_first;
        } else {
            merge_result[index] = *rhs_first;
            ++rhs_first;
        }
        index++;
    }

    if (lhs_first != lhs_last) {
        std::copy(lhs_first, lhs_last, merge_result.begin() + index);
    } else {
        std::copy(rhs_first, rhs_last, merge_result.begin() + index);
    }

    return merge_result;
}

template<class Iterator>
void MergeSort(Iterator begin, Iterator end, int64_t* cnt, int64_t L) {
    size_t split = 1;
    size_t size = end - begin;
    while (split <= size) {
        size_t from = 0;
        while (from + split < size) {
            auto to = (from + 2 * split <= size) ? begin + from + 2 * split : end;
            auto merge = Merge(begin + from, begin + from + split,
                               begin + from + split, to, cnt, L);

            std::copy(merge.begin(), merge.end(), begin + from);
            from += 2 * split;
        }
        split *= 2;
    }
}

int64_t Solution(const std::vector<int>& nums, int size, int64_t Left, int64_t Right) {
    std::vector<int64_t> prefix_sums(size + 1);
    prefix_sums[0] = 0;
    for (int i = 0; i < size; ++i) {
        prefix_sums[i + 1] = prefix_sums[i] + nums[i];
    }
    auto copy_prefix_sums = prefix_sums;

    int64_t cnt_L = 0;
    MergeSort(prefix_sums.begin(), prefix_sums.end(), &cnt_L, Left);

    int64_t cnt_R = 0;
    MergeSort(copy_prefix_sums.begin(), copy_prefix_sums.end(), &cnt_R, Right + 1);
    int64_t result = cnt_L - cnt_R;
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int size;
    std::cin >> size;
    std::vector<int> nums(size);
    for (auto& it : nums) {
        std::cin >> it;
    }

    int64_t Left, Right;
    std::cin >> Left >> Right;

    std::cout << Solution(nums, size, Left, Right) << "\n";

    return 0;
}
