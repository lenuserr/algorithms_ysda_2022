#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n_size, m_size;

    std::cin >> n_size >> m_size;

    std::vector<std::vector<int>> sequence(n_size);

    for (int i = 0; i < n_size; ++i) {
        std::vector<int> new_vector(m_size);
        for (auto& it : new_vector) {
            std::cin >> it;
        }
        sequence[i] = new_vector;
    }

    std::vector<std::vector<int>> my_heap(n_size);

    int index = 0;
    for (const auto& lst : sequence) {
        my_heap[index] = {lst[0], index, 0};
        index += 1;
    }

    std::make_heap(my_heap.begin(), my_heap.end(), std::greater<>{});

    std::vector<int> result;

    while (!my_heap.empty()) {
        std::pop_heap(my_heap.begin(), my_heap.end(), std::greater<>{});
        int value = my_heap.back()[0];
        int num_sequence = my_heap.back()[1];
        int num_element = my_heap.back()[2];
        my_heap.pop_back();

        result.push_back(value);


        if (static_cast<int>(sequence[num_sequence].size()) > num_element + 1) {
            my_heap.push_back(
                    {sequence[num_sequence][num_element + 1], num_sequence, num_element + 1});
            std::push_heap(my_heap.begin(), my_heap.end(), std::greater<>{});
        }
    }

    for (auto res : result) {
        std::cout << res << " ";
    }

    return 0;
}
