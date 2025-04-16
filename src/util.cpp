#include <SDL2/SDL.h>

#include "main.h"
#include "util.h"
#include "graph.h"

int GetOverlappingVertexAt(SDL_Point* point) {

    for (int i=0; i<graph.size(); i++) {
        
        SDL_Point* vertex = vertex_v.at(i);
        if (vertex == NULL) continue;

        if (CalculateDistance(vertex, point) < (2 * CIRCLE_RADIUS)) return i;
    }

    return -1;
}


double CalculateDistance(SDL_Point* source, SDL_Point* dest) {

    double a_sq = pow(dest->x - source->x, 2);
    double b_sq = pow(dest->y - source->y, 2);
    
    return sqrt(a_sq + b_sq);
}