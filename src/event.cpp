#include "main.h"
#include "graph.h"
#include "event.h"
#include "util.h"

void ProcessEvent(SDL_Event* event) {

	switch (event->type) {

	case SDL_QUIT:
		running = false;

	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
		HandleMouseButtonEvent(event);
		break;

	case SDL_KEYDOWN:
		HandleKeyboardEvent(event);
		break;
	}

}

void HandleMouseButtonEvent(SDL_Event* event) {
	if (event->button.button == 1) HandleMouseLeftButtonEvent(event);
	if (event->button.button == 3) HandleMouseRightButtonEvent(event);
}

void HandleMouseLeftButtonEvent(SDL_Event* event) {
	if (event->button.state == SDL_PRESSED) HandleMouseLeftButtonPressedEvent(event);
	if (event->button.state == SDL_RELEASED) HandleMouseLeftButtonReleasedEvent(event);
}

void HandleMouseLeftButtonPressedEvent(SDL_Event* event) {

	SDL_Point cur_mouse_pos = {event->button.x, event->button.y};
    int vertex_i = GetOverlappingVertexAt(&cur_mouse_pos);

    if (vertex_i >= 0) source_i = vertex_i;
    else CreateVertex(&cur_mouse_pos);
}

void HandleMouseLeftButtonReleasedEvent(SDL_Event* event) {
	if (source_i < 0) return;
		
	SDL_Point cur_mouse_pos = {event->button.x, event->button.y};
    int vertex_i = GetOverlappingVertexAt(&cur_mouse_pos);

    if (vertex_i >= 0 && vertex_i != source_i) {
        std::vector<int>* vertex = graph.at(source_i);
        (*vertex)[vertex_i] = 1;
    }

    source_i = -1;
}

void HandleMouseRightButtonEvent(SDL_Event* event) {
	SDL_Point cur_mouse_pos = {event->button.x, event->button.y};
	int vertex_i = GetOverlappingVertexAt(&cur_mouse_pos);

    if (vertex_i >= 0) {
        selected_vextex_i = vertex_i;
    }
}

void HandleKeyboardEvent(SDL_Event* event) {
	if (event->key.keysym.sym == SDLK_q) running = false;
    if (event->key.keysym.sym == SDLK_c) ClearGraph();
    if (event->key.keysym.sym == SDLK_d) DeleteVertex();
}