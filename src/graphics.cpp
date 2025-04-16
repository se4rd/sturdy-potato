#include "main.h"
#include "graphics.h"
#include "window.h"
#include "graph.h"
#include "util.h"

void ClearBackground() {
    SetRenderDrawColor(&CANVAS_BACKGROUND_COLOR);
    SDL_RenderClear(renderer);
}

void DrawVertices() {

    for (int i=0; i<vertex_v.size(); i++) {

        SDL_Point* vertex = vertex_v.at(i);
        if (vertex == NULL) continue;

        if (i == source_i)
            SetRenderDrawColor(&VERTEX_SOURCE_COLOR);
        else if (i == selected_vextex_i)
            SetRenderDrawColor(&VERTEX_SELECTED_COLOR);
        else
            SetRenderDrawColor(&VERTEX_NORMAL_COLOR);

        DrawCircle(vertex->x, vertex->y, CIRCLE_RADIUS);
    }
}

void DrawEdges() {
    
    for (int i=0; i<graph.size(); i++) {
        
        std::vector<int>* vertex = graph.at(i);
        if (vertex == NULL) continue;

        for (int j=0; j<vertex->size(); j++) {
            if (vertex->at(j) == -1) continue;
            DrawEdgeBetween(vertex_v.at(i), vertex_v.at(j));
        }
    }
}

void DrawEdgeBetween(SDL_Point* source, SDL_Point* dest) {
    SetRenderDrawColor(&EDGE_NORMAL_COLOR);
    SDL_RenderDrawLine(renderer, source->x, source->y, dest->x, dest->y);
}

void DrawEdgeBeingCreated() {
    if (source_i < 0) return;
        
    SDL_Point* source = vertex_v.at(source_i);
    SDL_Point dest; SDL_GetMouseState(&dest.x, &dest.y);

    SetRenderDrawColor(&EDGE_CREATING_COLOR);
    SDL_RenderDrawLine(renderer, source->x, source->y, dest.x, dest.y);
}

void HightlightHoveringVertex() {
    SDL_Point cur_mouse_pos;
    SDL_GetMouseState(&cur_mouse_pos.x, &cur_mouse_pos.y);

    int vertex_i = GetOverlappingVertexAt(&cur_mouse_pos);
    if (vertex_i < 0) return;

    SDL_Point* vertex = vertex_v.at(vertex_i);

    SetRenderDrawColor(&VERTEX_HIGHTLIGHT_COLOR);
    DrawCircle(vertex->x, vertex->y, 2 * CIRCLE_RADIUS);
}

void DrawCircle(int centreX, int centreY, int radius) {
   const int diameter = (radius * 2);

   int x = (radius - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (x >= y)
   {
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void SetRenderDrawColor(SDL_Color* color) {
    SDL_SetRenderDrawColor(
        renderer,
        color->r,
        color->g,
        color->b,
        color->a
    );
}