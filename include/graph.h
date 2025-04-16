#ifndef Graph_H
#define Graph_H

#include <SDL2/SDL.h>
#include <vector>

inline std::vector<std::vector<int>*> graph;
inline std::vector<SDL_Point*> vertex_v;

void CreateVertex(SDL_Point* vertex_pos);
void DeleteVertex();
void ClearGraph();

#endif