#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int Partition(std::vector<unsigned int>* vec, int begin, int end, unsigned int lambda) {
    int left = begin;
    int right = begin;

    while (right < end) {
        if ((*vec)[right] == lambda) {
            if (left - begin >= right - left + 1) {
                right += 1;
            } else {
                std::swap((*vec)[left], (*vec)[right]);
                left += 1;
                right += 1;
            }

        } else if ((*vec)[right] > lambda) {
            right += 1;
        } else {
            std::swap((*vec)[left], (*vec)[right]);
            left += 1;
            right += 1;
        }
    }

    return left;
}

void QuickSelect(std::vector<unsigned int>* vec, int left, int right, int k_statistic) {
    if (right - left <= 1) {
        return;
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(left, right - 1);

    int rand_index = dist(rng);
    unsigned int lambda = (*vec)[rand_index];
    int middle = Partition(vec, left, right, lambda);

    if (left <= k_statistic && k_statistic <= middle - 1) {
        QuickSelect(vec, left, middle, k_statistic);
    } else {
        QuickSelect(vec, middle, right, k_statistic);
    }
}

unsigned int cur = 0;
unsigned int aa, bb;

unsigned int nextRand24() {
    cur = cur * aa + bb;
    return cur >> 8;
}

unsigned int nextRand32() {
    unsigned int aa = nextRand24(), bb = nextRand24();
    return (aa << 8) ^ bb;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n_size;
    std::cin >> n_size;
    std::cin >> aa >> bb;

    std::vector<unsigned int> coordinates(n_size);
    for (int ind = 0; ind < n_size; ++ind) {
        coordinates[ind] = nextRand32();
    }

    int k_statistic = static_cast<int>(coordinates.size()) / 2;
    QuickSelect(&coordinates, 0, static_cast<int>(coordinates.size()), k_statistic);

    unsigned int median = coordinates[k_statistic];

    int64_t distance = 0;
    for (auto coordinate : coordinates) {
        if (median > coordinate) {
            distance += static_cast<int64_t>(median) - coordinate;
        } else {
            distance += static_cast<int64_t>(coordinate) - median;
        }
    }

    std::cout << distance << "\n";
    return 0;
}
