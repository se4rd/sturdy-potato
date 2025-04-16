#include "main.h"
#include "graph.h"

void CreateVertex(SDL_Point* vertex_pos) {
    
    graph.push_back(new std::vector<int>(100, -1));

    SDL_Point* vertex_pos_copy = new SDL_Point {vertex_pos->x, vertex_pos->y};
    vertex_v.push_back(vertex_pos_copy);
}

void DeleteVertex() {
    if (selected_vextex_i < 0) return;
        
    graph[selected_vextex_i] = NULL;
    vertex_v[selected_vextex_i] = NULL;

    for (std::vector<int>* vertex : graph) {
        if (vertex == NULL) continue;
        (*vertex)[selected_vextex_i] = -1;
    }

    selected_vextex_i = -1;
}

void ClearGraph() {
    graph.clear();
    vertex_v.clear();
}