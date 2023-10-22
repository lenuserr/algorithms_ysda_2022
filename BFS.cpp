#include <iostream>
#include <vector>
#include <unordered_map>

enum class Color {
    White,
    Gray,
    Black,
};

struct Edge {
    int start;
    int end;
};

void BFS(std::vector<int>* queue, const std::vector<std::vector<Edge>>& graph, std::vector<Color>* colors, 
std::unordered_map<int, int>* distance, int* i) {
    while (*i < static_cast<int>(colors->size())) {
        int u = (*queue)[*i];
        (*i)++;
        for (auto edge : graph[u]) {
            int v = edge.end;
            if ((*colors)[v] == Color::White) {
                (*colors)[v] = Color::Gray;
                (*distance)[v] = (*distance)[u] + 1;
                queue->push_back(v);
            }
        }
        
        (*colors)[u] = Color::Black;
    }
}

int main() {
    
    int V, E;
    std::cin >> V >> E;
    
    std::vector<std::vector<Edge>> graph(V);
    std::vector<Color> colors(V, Color::White);
    
    int start, end;
    for (int i = 0; i < E; ++i) {
        std::cin >> start >> end;
        graph[start].push_back({start, end});
        graph[end].push_back({end, start});
    }
    
    std::unordered_map<int, int> distance;
    distance[0] = 0;
    std::vector<int> queue{0};
    colors[0] = Color::Gray;
    int i = 0;
    
    BFS(&queue, graph, &colors, &distance, &i);
    
    for (const auto& [key, value] : distance) {
        std::cout << value << "\n";
    }
    
    return 0;
}
