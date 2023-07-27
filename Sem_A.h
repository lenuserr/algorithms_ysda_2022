#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <optional>

class MaxQueue {
public:
    void Insert(int64_t value) {
        size++;
        if (!TAIL_MAX) {
            TAIL_MAX = value;
            current_maximum = value;
            return;
        }
        TAIL_MAX = std::max(TAIL_MAX.value(), value);
        current_maximum = std::max(TAIL_MAX.value(), HEAD_MAX);
        tail.push(value);
    }

    void PopFront() {
        if (size == 1) {
            size--;
            TAIL_MAX = std::nullopt;
            return;
        }
        size--;
        if (head.empty()) {
            while (!tail.empty()) {
                int64_t top = tail.top();
                head.push(top);
                tail.pop();

                if (head_max.empty()) {
                    head_max.push(top);
                } else {
                    head_max.push(std::max(head_max.top(), top));
                }
            }
        }
        head.pop();
        if (tail.empty()) {
            TAIL_MAX = -1000000000000000000;
        }
        HEAD_MAX = head_max.top();
        current_maximum = std::max(TAIL_MAX.value(), HEAD_MAX);
        head_max.pop();
    }

    int64_t GetMax() const {
        return current_maximum;
    }

    int Size() const {
        return size;
    }

private:
    std::stack<int64_t> head;
    std::stack<int64_t> tail;
    std::stack<int64_t> head_max;
    std::optional<int64_t> TAIL_MAX = std::nullopt;
    int64_t HEAD_MAX = -1000000000000000000;
    int64_t current_maximum;
    int size = 0;
};

class ModifiedQueue {
public:
    ModifiedQueue() = delete;
    explicit ModifiedQueue(int cnt) : add_(0), cnt_(cnt) {
    }

    void insert(int64_t value) {
        if (value == -inf_) {
            max_queue.Insert(value);
        } else {
            max_queue.Insert(value - add_);
        }

        if (max_queue.Size() > cnt_ + 1) {
            max_queue.PopFront();
        }
    }

    int64_t get_max() const {
        int64_t max = max_queue.GetMax();
        if (max == -inf_) {
            return -inf_;
        }
        return max + add_;
    }

    void increment(int value) {
        add_ += value;
    }

private:
    MaxQueue max_queue;
    int64_t add_ = 0;
    int cnt_;
    int64_t inf_ = 1000000000000000000;
};


struct Group {
    int weight;
    int cost;
    int num_of_items;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nn, W;
    std::cin >> nn >> W;

    std::vector<Group> groups(nn + 1);

    for (int i = 1; i <= nn; ++i) {
        std::cin >> groups[i].weight  >> groups[i].cost >> groups[i].num_of_items;
    }

    int64_t inf = 1000000000000000000; // 10^18;
    std::vector<int64_t> dp(W + 1, -inf);
    dp[0] = 0;

    for (int kk = 1; kk <= nn; ++kk) {
        std::vector<int64_t> row(W + 1, -inf);
        for (int jj = 0; jj < std::min(groups[kk].weight, W + 1); ++jj) {
            int ll = 0;
            int add = groups[kk].cost;
            ModifiedQueue queue(groups[kk].num_of_items);

            int64_t index;
            while ((static_cast<int64_t>(ll) * groups[kk].weight) + jj <= W) {
                index = (static_cast<int64_t>(ll) * groups[kk].weight) + jj;
                queue.insert(dp[index]);
                row[index] = queue.get_max();

                queue.increment(add);
                ll++;
            }
        }

        dp = std::move(row);
    }

    int64_t total_cost = 0;
    for (auto local_cost : dp) {
        total_cost = std::max(total_cost, local_cost);
    }

    std::cout << total_cost << "\n";

    return 0;
}
