#include <stdlib.h>
#include <iostream>

#include "main.h"
#include "window.h"

void CreateWindow() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) Log(SDL_ERROR);
    if (TTF_Init() != 0) Log(TTF_ERROR);

    window = SDL_CreateWindow("", 50, 50, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) Log(SDL_ERROR);

    SDL_SetWindowFullscreen(window, /*SDL_WINDOW_FULLSCREEN_DESKTOP*/ 0);

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) Log(SDL_ERROR);
}

void LoadFont() {

	font = TTF_OpenFont(FONT, FONT_SIZE);
    if (!font) Log(TTF_ERROR);
}

void Log(int error_type) {

	const char* error;

	if (error_type == SDL_ERROR) error = SDL_GetError();
	else if (error_type == TTF_ERROR) error = TTF_GetError();

    std::cout << "Error: " << SDL_GetError() << std::endl;
    exit(-1);
}