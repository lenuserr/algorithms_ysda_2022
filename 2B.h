#include <iostream>
#include <vector>
#include <algorithm>

struct Player {
    size_t index;
    int efficiency;
};

struct Team {
    std::vector<Player>::iterator begin;
    std::vector<Player>::iterator end;
    int64_t total_efficiency;
};

bool LessByEfficiency(const Player& lhs, const Player& rhs) {
    return lhs.efficiency <= rhs.efficiency;
}

bool LessByIndex(const Player& lhs, const Player& rhs) {
    return lhs.index <= rhs.index;
}

template <class Iterator, class Compare, class T>
std::vector<T> Merge(Iterator lhs_first, Iterator lhs_last,
                     Iterator rhs_first, Iterator rhs_last,
                     Compare cmp, const T& type) {
    size_t size_merge = (lhs_last - lhs_first) + (rhs_last - rhs_first);
    std::vector<T> merge_result(size_merge);

    size_t index = 0;
    while (lhs_first != lhs_last && rhs_first != rhs_last) {
        if (cmp(*lhs_first, *rhs_first)) {
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

template<class Iterator, class Compare>
void MergeSort(Iterator begin, Iterator end, Compare cmp) {
    size_t split = 1;
    size_t size = end - begin;
    while (split <= size) {
        size_t from = 0;
        while (from + split < size) {
            auto to = (from + 2 * split <= size) ? begin + from + 2 * split : end;
            auto merge = Merge(begin + from, begin + from + split,
                               begin + from + split, to,
                               cmp, *begin);

            std::copy(merge.begin(), merge.end(), begin + from);
            from += 2 * split;
        }
        split *= 2;
    }
}

std::vector<Player> BuildMostEffectiveSolidaryTeam(std::vector<Player> players) {
    if (players.size() == 1) {
        return players;
    }

    MergeSort(players.begin(), players.end(), LessByEfficiency);
    Team team = {players.begin(), players.begin() + 2,
                 static_cast<int64_t>(team.begin->efficiency) + (team.begin + 1)->efficiency};
    Team best_team = team;

    while (team.end != players.end()) {
        int64_t min_sum = static_cast<int64_t>(team.begin->efficiency)
                          + (team.begin + 1)->efficiency;

        while (team.end != players.end() && min_sum >= team.end->efficiency) {
            team.total_efficiency += team.end->efficiency;
            ++team.end;
        }

        if (team.total_efficiency > best_team.total_efficiency) {
            best_team = team;
        }

        team.total_efficiency -= team.begin->efficiency;
        ++team.begin;
    }

    return {best_team.begin, best_team.end};
}

int64_t CalculateTotalEfficiency(const std::vector<Player>& best_team) {
    int64_t result = 0;
    for (const auto& player : best_team) {
        result += player.efficiency;
    }
    return result;
}

std::vector<Player> ReadPlayers() {
    size_t size;
    std::cin >> size;

    std::vector<Player> players(size);
    size_t index = 1;
    for (auto& player : players) {
        player.index = index;
        std::cin >> player.efficiency;
        index++;
    }
    return players;
}

void WriteOutput(std::vector<Player> players) {
    int64_t best_efficiency = CalculateTotalEfficiency(players);
    std::cout << best_efficiency << "\n";

    MergeSort(players.begin(), players.end(), LessByIndex);
    for (const auto& player : players) {
        std::cout << player.index << " ";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto players = ReadPlayers();
    auto best_team = BuildMostEffectiveSolidaryTeam(players);
    WriteOutput(best_team);

    return 0;
}
