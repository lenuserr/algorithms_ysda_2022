#include <iostream>
#include <vector>

std::vector<int> Increase(const std::vector<int>& nums) {

    int nums_size = static_cast<int>(nums.size());

    std::vector<std::vector<int>> increasing_sequences;
    int i = 0;
    while (i < nums_size - 1) {
        std::vector<int> new_seq;
        if (nums[i] > nums[i + 1]) {
            i += 1;
            continue;
        }
        while((i < nums_size - 1) && (nums[i] < nums[i + 1])) {
            new_seq.push_back(nums[i]);
            i += 1;
        }
        new_seq.push_back(nums[i]);
        increasing_sequences.push_back(new_seq);
        i += 1;
    }

    std::vector<std::vector<int>> decreasing_sequences;
    i = 0;
    while (i < nums_size - 1) {
        std::vector<int> new_seq;
        if (nums[i] < nums[i + 1]) {
            i += 1;
            continue;
        }
        while((i < nums_size - 1) && (nums[i] > nums[i + 1])) {
            new_seq.push_back(nums[i]);
            i += 1;
        }
        new_seq.push_back(nums[i]);
        decreasing_sequences.push_back(new_seq);
        i += 1;
    }

    std::vector<int> result_sequence;
    result_sequence.push_back(increasing_sequences[0][0]);
    size_t p = 1;
    for (size_t i = 0; i < decreasing_sequences.size(); ++i) {
        bool flag = false;
        for (size_t j = p; j < increasing_sequences[i].size(); ++j) {
            if (flag) { break; }
            for (size_t k = 0; k < decreasing_sequences[i].size(); ++k) {
                if (flag) { break; }
                if (increasing_sequences[i][j] > decreasing_sequences[i][k]) {
                    if (i + 1 < increasing_sequences.size()) {
                        for (size_t r = 0; r < increasing_sequences[i + 1].size(); ++r) {
                            if (decreasing_sequences[i][k] < increasing_sequences[i + 1][r]) {
                                result_sequence.push_back(increasing_sequences[i][j]);
                                result_sequence.push_back(decreasing_sequences[i][k]);
                                flag = true;
                                p = r;
                                break;
                            }
                        }

                    } else {
                        result_sequence.push_back(increasing_sequences[i][j]);
                        result_sequence.push_back(decreasing_sequences[i][k]);
                        flag = true;
                        break;
                    }
                }
            }
        }
    }

    if (increasing_sequences.size() > decreasing_sequences.size()) {
        int inc_size = static_cast<int>(increasing_sequences.size());
        result_sequence.push_back(increasing_sequences[inc_size - 1][p]);
    }

    return result_sequence;
}

std::vector<int> Decrease(const std::vector<int>& nums) {

    int nums_size = static_cast<int>(nums.size());

    std::vector<std::vector<int>> decreasing_sequences;
    int i = 0;
    while (i < nums_size - 1) {
        std::vector<int> new_seq;
        if (nums[i] < nums[i + 1]) {
            i += 1;
            continue;
        }
        while((i < nums_size - 1) && (nums[i] > nums[i + 1])) {
            new_seq.push_back(nums[i]);
            i += 1;
        }
        new_seq.push_back(nums[i]);
        decreasing_sequences.push_back(new_seq);
        i += 1;
    }

    std::vector<std::vector<int>> increasing_sequences;
    i = 0;
    while (i < nums_size - 1) {
        std::vector<int> new_seq;
        if (nums[i] > nums[i + 1]) {
            i += 1;
            continue;
        }
        while((i < nums_size - 1) && (nums[i] < nums[i + 1])) {
            new_seq.push_back(nums[i]);
            i += 1;
        }
        new_seq.push_back(nums[i]);
        increasing_sequences.push_back(new_seq);
        i += 1;
    }

    std::vector<int> result_sequence;
    result_sequence.push_back(decreasing_sequences[0][0]);
    size_t p = 1;
    for (size_t i = 0; i < increasing_sequences.size(); ++i) {
        bool flag = false;
        for (size_t j = p; j < decreasing_sequences[i].size(); ++j) {
            if (flag) { break; }
            for (size_t k = 0; k < increasing_sequences[i].size(); ++k) {
                if (flag) { break; }
                if (decreasing_sequences[i][j] < increasing_sequences[i][k]) {
                    if (i + 1 < decreasing_sequences.size()) {
                        for (size_t r = 0; r < decreasing_sequences[i + 1].size(); ++r) {
                            if (increasing_sequences[i][k] > decreasing_sequences[i + 1][r]) {
                                result_sequence.push_back(decreasing_sequences[i][j]);
                                result_sequence.push_back(increasing_sequences[i][k]);
                                flag = true;
                                p = r;
                                break;
                            }
                        }

                    } else {
                        result_sequence.push_back(decreasing_sequences[i][j]);
                        result_sequence.push_back(increasing_sequences[i][k]);
                        flag = true;
                        break;
                    }
                }
            }
        }
    }

    if (decreasing_sequences.size() > increasing_sequences.size()) {
        int dec_size = static_cast<int>(decreasing_sequences.size());
        result_sequence.push_back(decreasing_sequences[dec_size - 1][p]);
    }

    return result_sequence;
}

std::vector<int> Solution(const std::vector<int>& sequence, int n) {
    std::vector<int> result;

    if (n == 1) {
        result.push_back(sequence[0]);
        return result;
    }

    std::vector<int> seq;

    for (int i = 0; i < n - 1; ++i) {
        if (sequence[i] != sequence[i + 1]) {
            seq.push_back(sequence[i]);
        }
    }
    seq.push_back(sequence[n - 1]);

    int size = static_cast<int>(seq.size());
    if (size == 1) {
        result.push_back(seq[0]);
        return result;
    }

    if (seq[0] < seq[1]) {
        result = Increase(seq);
        return result;

    } else {
        result = Decrease(seq);
        return result;
    }
}


int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n_size;
    std::cin >> n_size;

    std::vector<int> numbers(n_size);
    for (auto& it : numbers) {
        std::cin >> it;
    }

    std::vector<int> answer = Solution(numbers, n_size);

    for (auto ans : answer) {
        std::cout << ans << " ";
    }

    return 0;
}
