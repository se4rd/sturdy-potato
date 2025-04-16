#ifndef Util_H
#define Util_H

#include <SDL2/SDL.h>

int GetOverlappingVertexAt(SDL_Point* point);
double CalculateDistance(SDL_Point* source, SDL_Point* dest);

#endif