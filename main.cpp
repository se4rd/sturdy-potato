#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <SDL2/SDL_ttf.h>
using namespace std;

TTF_Font* font;
SDL_Window* window;
SDL_Renderer* renderer;

bool running = true;
size_t start_node = -1;

vector<NODE*> graph;
vector<vector<int>*> adj;

int main(int argc, char* argv[])
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) sdl_log_error_and_exit();
    if (TTF_Init() != 0) ttf_log_error_and_exit();

    window = SDL_CreateWindow("", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) sdl_log_error_and_exit();

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) sdl_log_error_and_exit();

    font = TTF_OpenFont("fonts/VictorMono/VictorMonoNerdFont-Light.ttf", 10);
    if (!font) sdl_log_error_and_exit();

    SDL_Event event;
    while (running) {
        clear_background(COLOR_BLACK);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            if (event.type == SDL_MOUSEBUTTONDOWN) handle_mouse_event(&event);
            if (event.type == SDL_KEYDOWN) handle_keyboard_event(&event);
        }

        draw_graph_nodes();
        draw_nodes_index();
        draw_graph_edges();
        hightlight_hovering_node();

        SDL_RenderPresent(renderer);
    }
    
    return 0;
}

void clear_background(SDL_Color color)
{
    SDL_SetRenderDrawColor(
        renderer,
        color.r, color.g, color.b, color.a
    );
    SDL_RenderClear(renderer);
}

void handle_mouse_event(SDL_Event* event)
{
    if (event->button.button == 1) create_new_node();
    if (event->button.button == 3) start_node = get_hovering_node();
}

void handle_keyboard_event(SDL_Event* event)
{
    if (event->key.keysym.sym == SDLK_q) running = 0;
    if (event->key.keysym.sym == SDLK_c) clear_canvas();
}

void draw_graph_nodes()
{
    for (size_t i=0; i<graph.size(); i++) {
        
        if (i == start_node) SDL_SetRenderDrawColor(renderer, 255,   0,   0, 255);
        else                 SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        NODE* node = graph.at(i);
        draw_circle(node->x, node->y, CIRCLE_RADIUS);
    }
}

void draw_graph_edges()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (NODE* node  : graph)
    for (NODE* node_ : graph)
    SDL_RenderDrawLine(renderer, node->x, node->y, node_->x, node_->y);
}

void draw_nodes_index()
{
    char buffer[50];
    for (size_t i=0; i<graph.size(); i++) {
        
        sprintf(buffer, "%d", i);
        NODE* node = graph.at(i);

        SDL_Surface* surface = TTF_RenderText_Solid(font, buffer, COLOR_RED);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect dest = {
            (node->x) - (2 * CIRCLE_RADIUS),
            (node->y) - (2 * CIRCLE_RADIUS),
            30, 30
        };

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }
}

void create_new_node()
{
    NODE* new_node = new NODE {};
    SDL_GetMouseState(&new_node->x, &new_node->y);


    if (!check_overlap(new_node)) {
        insert_node(new_node);
        display_adj_matrix();
    }
}

bool check_overlap(NODE* node)
{
    for (NODE* node_ : graph)
        if (distance(node, node_) < (2 * CIRCLE_RADIUS))
        return true;

    return false;
}

void insert_node(NODE* new_node)
{
    graph.push_back(new_node);

    vector<int>* new_row= new vector<int>();
        for (NODE* node : graph)
        new_row->push_back(distance(new_node, node));
    adj.push_back(new_row);

    for (size_t i=0; i<(adj.size() - 1); i++) {
        vector<int>* row = adj.at(i);
        row->push_back(distance(new_node, graph.at(i)));
    }  
}

int get_hovering_node()
{
    SDL_Point mouse_pos;
    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

    for (size_t i=0; i<graph.size(); i++)
    if (distance(&mouse_pos, graph.at(i)) < (2 * CIRCLE_RADIUS)) return i;

    return -1;
}

void hightlight_hovering_node()
{
    int node_index = get_hovering_node();
    if (node_index == -1) return;

    NODE* node = graph.at(node_index);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    draw_circle(node->x, node->y, 2 * CIRCLE_RADIUS);
}

void clear_canvas()
{
    graph.clear();
    adj.clear();
    start_node = -1;
}

void display_adj_matrix()
{
    for (vector<int>* row : adj) {
        for (int entry : (*row))
            cout << entry << "\t";
        cout << endl;
    }
}

void sdl_log_error_and_exit() 
{
    cout << "Error: " << SDL_GetError() << endl;
    exit(-1);
}

void ttf_log_error_and_exit() 
{
    cout << "Error: " << TTF_GetError() << endl;
    exit(-1);
}

double distance(SDL_Point* Point_A, SDL_Point* Point_B)
{
    double a_sq = pow(Point_B->x - Point_A->x, 2);
    double b_sq = pow(Point_B->y - Point_A->y, 2);
    return sqrt(a_sq + b_sq);
}

void draw_circle(int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

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
