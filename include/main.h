#ifndef Main_H

#include <SDL2/SDL.h>

#define Main_H

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 500
#define CIRCLE_RADIUS 20

#define FONT "fonts/VictorMono/VictorMonoNerdFont-Light.ttf"
#define FONT_SIZE 10

inline SDL_Color COLOR_BLACK = SDL_Color {0, 0, 0, 255};
inline SDL_Color COLOR_WHITE = SDL_Color {255, 255, 255, 255};
inline SDL_Color COLOR_YELLOW = SDL_Color {255, 255, 0, 255};
inline SDL_Color COLOR_RED = SDL_Color {255, 0, 0, 255};
inline SDL_Color COLOR_GREEN = SDL_Color {0, 255, 0, 255};
inline SDL_Color COLOR_BLUE = SDL_Color {0, 0, 255, 255};
inline SDL_Color COLOR_GREY = SDL_Color {197, 196, 197, 255};

inline bool running = true;

inline int source_i = -1;
inline int selected_vextex_i = -1;

#endif