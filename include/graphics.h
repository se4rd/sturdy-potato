#ifndef Graphics_H
#define Graphics_H

#include <SDL2/SDL.h>

#define DARK_MODE 1

#if DARK_MODE
	#define CANVAS_BACKGROUND_COLOR COLOR_BLACK
	#define VERTEX_HIGHTLIGHT_COLOR COLOR_YELLOW
	#define VERTEX_NORMAL_COLOR COLOR_WHITE
	#define VERTEX_SELECTED_COLOR COLOR_BLUE
	#define VERTEX_SOURCE_COLOR COLOR_GREEN
	#define EDGE_NORMAL_COLOR COLOR_WHITE
	#define EDGE_CREATING_COLOR COLOR_WHITE
#endif

void ClearBackground();
void DrawVertices();
void DrawEdges();
void DrawEdgeBetween(SDL_Point* source, SDL_Point* dest);
void DrawEdgeBeingCreated();
void HightlightHoveringVertex();
void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius);
void SetRenderDrawColor(SDL_Color* color);

#endif