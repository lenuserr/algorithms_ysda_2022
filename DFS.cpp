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
};

void DFS(int u, const std::vector<std::vector<Edge>>& graph, std::vector<Color>* colors) {
    (*colors)[u] = Color::Gray;
    for (auto edge : graph[u]) {
        int v = edge.end;
        
        if ((*colors)[v] == Color::White) {
            DFS(v, graph, colors);
        }
    }
    
    (*colors)[u] = Color::Black;
}

int main() {

    int V, E; // V - число вершин в графе. E - число ребер в графе.
    std::cin >> V >> E;

    std::vector<Color> colors(V, Color::White);
    std::vector<std::vector<Edge>> graph(V);

    int start, end;
    for (int i = 0; i < E; ++i) {
        std::cin >> start >> end;
        graph[start].push_back({start, end});
        //graph[end].push_back({end, start}); если граф неориентированный, то нужно раскомментировать эту строчку кода.
    }
    
    DFS(0, graph, &colors); // DFS запущенный из вершины 0.

    return 0;
}
