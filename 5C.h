#include <iostream>
#include <vector>
#include <algorithm>

enum class Color {
    White,
    Gray,
    Black,
};

struct Edge {
    int start;
    int end;
    int cost;
};

void DFS(int uu, int dad, const std::vector<std::vector<Edge>>& graph, std::vector<Color>* colors,
         std::vector<int>* enter, int* time, std::vector<int>* ll, int* min_cost) {

    (*enter)[uu] = ++(*time);
    (*colors)[uu] = Color::Gray;
    (*ll)[uu] = 100000;
    for (auto edge : graph[uu]) {
        int vv = edge.end;
        if (vv == dad) {
            continue;
        }

        if ((*colors)[vv] == Color::White) {
            DFS(vv, uu, graph, colors, enter, time, ll, min_cost);
            (*ll)[uu] = std::min((*ll)[uu], (*ll)[vv]);

            if ((*ll)[vv] > (*enter)[uu]) {
                *min_cost = std::min(*min_cost, edge.cost);
            }
        }
        (*ll)[uu] = std::min((*ll)[uu], (*enter)[vv]);
    }
    (*colors)[uu] = Color::Black;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int VV, E;
    std::cin >> VV >> E;

    std::vector<Color> colors(VV + 1, Color::White);
    std::vector<int> enter(VV + 1);
    std::vector<int> ll(VV + 1);

    std::vector<std::vector<Edge>> graph(VV + 1);

    int aa, b, cost;
    for (int i = 0; i < E; ++i) {
        std::cin >> aa >> b >> cost;
        graph[aa].push_back({aa, b, cost});
        graph[b].push_back({b, aa, cost});
    }

    int time = 0;
    int min_cost = 1000000001;
    DFS(1, 0, graph, &colors, &enter, &time, &ll, &min_cost);

    if (min_cost != 1000000001) {
        std::cout << min_cost << "\n";
    } else {
        std::cout << -1 << "\n";
    }

    return 0;
}
