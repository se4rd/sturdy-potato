#ifndef Window_H
#define Window_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SDL_ERROR 0
#define TTF_ERROR 1

inline SDL_Window* window;
inline SDL_Renderer* renderer;
inline TTF_Font* font;

void CreateWindow();
void LoadFont();
void Log(int error_type);

#endif