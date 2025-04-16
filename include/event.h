#ifndef Event_H
#define Event_H

#include <SDL2/SDL.h>

void ProcessEvent(SDL_Event* event);
void HandleMouseButtonEvent(SDL_Event* event);
void HandleMouseLeftButtonEvent(SDL_Event* event);
void HandleMouseLeftButtonPressedEvent(SDL_Event* event);
void HandleMouseLeftButtonReleasedEvent(SDL_Event* event);
void HandleMouseRightButtonEvent(SDL_Event* event);
void HandleKeyboardEvent(SDL_Event* event);

#endif