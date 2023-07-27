#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int numbers_size;
    std::cin >> numbers_size;
    std::vector<int> numbers(numbers_size);
    for (auto& it : numbers) {
        std::cin >> it;
    }

    int indicators_size;
    std::cin >> indicators_size;
    std::vector<char> indicators(indicators_size);
    for (auto& it : indicators) {
        std::cin >> it;
    }

    std::stack<int> tail;
    int TAIL_MAX = numbers[0];
    std::stack<int> head;
    int HEAD_MAX = -1000000001;
    std::stack<int> head_max;
    int right = 1;

    for (auto indicator : indicators) {
        if (indicator == 'R') {
            TAIL_MAX = std::max(TAIL_MAX, numbers[right]);
            std::cout << std::max(TAIL_MAX, HEAD_MAX) << " ";
            tail.push(numbers[right]);
            right += 1;
            continue;
        }

        if (head.empty()) {
            while (!tail.empty()) {
                int top = tail.top();
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
            TAIL_MAX = -1000000001;
        }
        HEAD_MAX = head_max.top();
        std::cout << std::max(TAIL_MAX, HEAD_MAX) << " ";
        head_max.pop();
    }

    std::cout << "\n";
    return 0;
}
