#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <functional>

struct Flags {
    bool is_alive;
    bool in_max_heap;
};

void RInsert(int* right, int* num_of_alive_in_max_heap, std::vector<Flags>* flags,
             std::vector<std::pair<int, int>>* max_heap, std::vector<std::pair<int, int>>* min_heap,
             const std::vector<int>& elements) {
    (*right)++;
    if (max_heap->empty()) {
        (*num_of_alive_in_max_heap)++;
        (*flags)[*right].in_max_heap = true;
        max_heap->emplace_back(elements[*right], *right);
        std::push_heap(max_heap->begin(), max_heap->end());
    } else {
        std::pop_heap(max_heap->begin(), max_heap->end());
        auto root = max_heap->back();
        max_heap->pop_back();
        (*flags)[root.second].in_max_heap = false;

        while (!max_heap->empty() && !(*flags)[root.second].is_alive) {
            std::pop_heap(max_heap->begin(), max_heap->end());
            root = max_heap->back();
            max_heap->pop_back();
            (*flags)[root.second].in_max_heap = false;
        }

        if (!(*flags)[root.second].is_alive) { // если мертвый.
            (*num_of_alive_in_max_heap)++;
            (*flags)[*right].in_max_heap = true;
            max_heap->emplace_back(elements[*right], *right);
            std::push_heap(max_heap->begin(), max_heap->end());
        } else {
            // делаем проверку: сравнение вставляемого элемента с корнем max heap
            if (elements[*right] >= root.first) {
                (*flags)[root.second].in_max_heap = true;
                max_heap->emplace_back(root.first, root.second);
                std::push_heap(max_heap->begin(), max_heap->end());

                min_heap->emplace_back(elements[*right], *right);
                std::push_heap(min_heap->begin(), min_heap->end(), std::greater<>{});
            } else {
                min_heap->emplace_back(root.first, root.second);
                std::push_heap(min_heap->begin(), min_heap->end(), std::greater<>{});

                (*flags)[*right].in_max_heap = true;
                max_heap->emplace_back(elements[*right], *right);
                std::push_heap(max_heap->begin(), max_heap->end());
            }
        }
    }
}


void LDelete(int* left, int* num_of_alive_in_max_heap, std::vector<Flags>* flags) {
    if ((*flags)[*left].in_max_heap) {
        (*num_of_alive_in_max_heap)--;
    }
    (*flags)[*left].is_alive = false;
    (*left)++;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int nn, mm, k_statistic;
    std::cin >> nn >> mm >> k_statistic;
    std::vector<int> elements(nn);
    for (auto& it : elements) {
        std::cin >> it;
    }
    std::string operations;
    std::cin >> operations;

    // Max heap
    std::vector<std::pair<int, int>> max_heap;
    std::make_heap(max_heap.begin(), max_heap.end());

    // Min heap
    std::vector<std::pair<int, int>> min_heap;
    std::make_heap(min_heap.begin(), min_heap.end(), std::greater<>{});

    std::vector<Flags> flags(nn, {true, false});

    int num_of_alive_in_max_heap = 0;
    int left = 0;
    int right = 0;

    num_of_alive_in_max_heap++;
    flags[0].in_max_heap = true;
    max_heap.emplace_back(elements[0], 0);
    std::push_heap(max_heap.begin(), max_heap.end());


    for (const auto& operation : operations) {
        if (operation == 'R') {
            RInsert(&right, &num_of_alive_in_max_heap, &flags, &max_heap, &min_heap, elements);
        } else {
            LDelete(&left, &num_of_alive_in_max_heap, &flags);
        }
        // совершаем перебрасывание элементов из min heap в max heap.
        while (!min_heap.empty() && num_of_alive_in_max_heap != k_statistic) {
            std::pop_heap(min_heap.begin(), min_heap.end(), std::greater<>{});
            auto root = min_heap.back();
            min_heap.pop_back();

            if (flags[root.second].is_alive) {
                num_of_alive_in_max_heap++;
                flags[root.second].in_max_heap = true;
                max_heap.emplace_back(root.first, root.second);
                std::push_heap(max_heap.begin(), max_heap.end());
            }
        }

        if (num_of_alive_in_max_heap == k_statistic) {
            // печатаем содержимое корня max heap.
            // если по времени не будет проходить вытаскивание + затаскивание,
            // значит будем улучшать, кажется, можно, но пока не надо.
            std::pop_heap(max_heap.begin(), max_heap.end());
            auto root = max_heap.back();
            max_heap.pop_back();
            // ИЩЕМ ЖИВОЙ КОРЕНЬ И РАСПЕЧАТЫВАЕМ ЕГО.
            while (!flags[root.second].is_alive) {
                std::pop_heap(max_heap.begin(), max_heap.end());
                root = max_heap.back();
                max_heap.pop_back();
            }

            max_heap.emplace_back(root.first, root.second);
            std::push_heap(max_heap.begin(), max_heap.end());

            std::cout << root.first << "\n";
        } else {
            std::cout << -1 << "\n";
        }
    }

    return 0;
}
