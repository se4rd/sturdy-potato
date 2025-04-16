
#include <SDL2/SDL.h>

#include "main.h"
#include "window.h"
#include "graphics.h"
#include "event.h"

int main() {

    CreateWindow();
    LoadFont();

    SDL_Event event;
    while (running) {

        while (SDL_PollEvent(&event)) {
            ProcessEvent(&event);
        }

        ClearBackground();

        DrawVertices();
        DrawEdges();

        DrawEdgeBeingCreated();
        HightlightHoveringVertex();

        SDL_RenderPresent(renderer);
    }
    
    return 0;
}
