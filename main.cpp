#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <SDL2/SDL_ttf.h>
using namespace std;

TTF_Font* font;
SDL_Window* window;
SDL_Renderer* renderer;

bool running = true;
size_t start_node = -1;

// vector<NODE*> graph;
// vector<vector<int>*> adj;

// struct edge {
//     int v1, v2;
// }

vector<vector<int>*> graph;
vector<SDL_Point*> vertex_v;

int source_i = -1;
SDL_Point* dest = new SDL_Point {};

int selected_vextex_i = -1;

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
            if (event.type == SDL_MOUSEBUTTONDOWN) handle_mouse_button_event(&event);
            if (event.type == SDL_MOUSEBUTTONUP) handle_mouse_button_event(&event);
            if (event.type == SDL_MOUSEMOTION) handle_mouse_motion_event(&event);
            if (event.type == SDL_KEYDOWN) handle_keyboard_event(&event);
        }

        draw_vertex_all();
        draw_edge_all();
        draw_edge_being_created();
        // draw_nodes_index();
        // draw_graph_edges();
        hightlight_hovering_node();

        SDL_RenderPresent(renderer);
    }
    
    return 0;
}

// void execute_tsp()
// {
//     vector<int> l;
    
//     for (int i=0; i<graph.size(); i++)
//     if (start_node != i) l.push_back(i);

//     vector<vector<int>> permutations = calculate_permutations(&l);

//     for (vector<int> path : permutations) {
//         path.insert(0, start_node);
//         calculate_distance(&path);
//     }
// }

// vector<vector<int>>* calculate_permutations(vector<int> *l)
// {
    
// }

// int calculate_distance(vector<int>* path)
// {

// }

void clear_background(SDL_Color color)
{
    SDL_SetRenderDrawColor(
        renderer,
        color.r, color.g, color.b, color.a
    );
    SDL_RenderClear(renderer);
}

void handle_mouse_button_event(SDL_Event* event)
{
    if (event->button.button == 1 && event->button.state == SDL_PRESSED) {
#if 1
        // check if any vertex is overlapping
        SDL_Point cur_mouse_pos;
        SDL_GetMouseState(&cur_mouse_pos.x, &cur_mouse_pos.y);
        int vertex_i = check_if_overlap_with_any_vertex(&cur_mouse_pos);

        if (vertex_i != -1) {
            // select the overlapping vertex
            source_i = vertex_i;
            dest->x = cur_mouse_pos.x;
            dest->y = cur_mouse_pos.y;
        }

        else {
            // if not create new vertex
            create_vertex(&cur_mouse_pos);
        }
#endif
        // cout << "SDL_PRESSED" << endl;
    }

    if (event->button.button == 1 && event->button.state == SDL_RELEASED) {

        // check if source exist

        // check if dest overlaps any vertex
        // if overlaps, create edge between source and that vertex

        // else
        // source = NULL;

        if (source_i != -1) {
            int dest_i = check_if_overlap_with_any_vertex(dest);

            if (dest_i != -1 && source_i != dest_i) {
                // create edge
                graph.at(source_i)->push_back(dest_i);
            }

            source_i = -1;
        }

        // cout << "SDL_RELEASED" << endl;
    }

    if (event->button.button == 3){
        SDL_Point point = {event->button.x, event->button.y};
        int i = check_if_overlap_with_any_vertex(&point);

        if (i != -1) {
            selected_vextex_i = i;
        }
    }
}

void handle_mouse_motion_event(SDL_Event* event) {
    // check if vertex is selected currently
    // if selected, draw edge from that vertex to curr mouse pos

    if (source_i != -1) {
        dest->x = event->motion.x;
        dest->y = event->motion.y;
    }
}

void handle_keyboard_event(SDL_Event* event)
{
    if (event->key.keysym.sym == SDLK_q) running = 0;
    if (event->key.keysym.sym == SDLK_c) reset();

    // TODO: Implement vertex deletion.
    
    if (event->key.keysym.sym == SDLK_d) {
        if (selected_vextex_i != -1) {
            graph.erase(graph.begin() + selected_vextex_i);
            vertex_v.erase(vertex_v.begin() + selected_vextex_i);
        }
    }
    // if (event->key.keysym.sym == SDLK_t) execute_tsp();
}

void draw_vertex_all()
{
    // for (size_t i=0; i<graph.size(); i++) {
        
    //     if (i == start_node)
	// SDL_SetRenderDrawColor(renderer, 255,   0,   0, 255);
    //     else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //     NODE* node = graph.at(i);
    //     draw_circle(node->x, node->y, CIRCLE_RADIUS);
    // }

    for (int i=0; i<vertex_v.size(); i++) {

        SDL_Point* vertex = vertex_v.at(i);

        if (i == source_i) SDL_SetRenderDrawColor(renderer, 255, 100, 255, 255);
        else if (i == selected_vextex_i) SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
        else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        draw_circle(vertex->x, vertex->y, CIRCLE_RADIUS);
    }
}

void draw_edge_all() {
    for (int i=0; i<graph.size(); i++) {
        vector<int>* v = graph.at(i);

        for (int j=0; j<v->size(); j++) {
            draw_edge_between(vertex_v.at(i), vertex_v.at(v->at(j)));
        }
    }
}

void draw_edge_between(SDL_Point* vertex1, SDL_Point* vertex2) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, vertex1->x, vertex1->y, vertex2->x, vertex2->y);
}

void draw_edge_being_created() {
    if (source_i != -1) {
        SDL_Point* source = vertex_v.at(source_i);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, source->x, source->y, dest->x, dest->y);
    }
}

// void draw_graph_edges()
// {
//     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

//     for (NODE* node  : graph)
//     for (NODE* node_ : graph)
//     SDL_RenderDrawLine(renderer, node->x, node->y, node_->x, node_->y);
// }

// void draw_nodes_index()
// {
//     char buffer[50];
//     for (int i=0; i<graph.size(); i++) {
        
//         sprintf(buffer, "%d", i);
//         NODE* node = graph.at(i);

//         SDL_Surface* surface = TTF_RenderText_Solid(font, buffer, COLOR_RED);
//         SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

//         SDL_Rect dest = {
//             (node->x) - (2 * CIRCLE_RADIUS),
//             (node->y) - (2 * CIRCLE_RADIUS),
//             30, 30
//         };

//         SDL_RenderCopy(renderer, texture, NULL, &dest);
//     }
// }

// void create_new_node()
// {
//     NODE* new_node = new NODE {};
//     SDL_GetMouseState(&new_node->x, &new_node->y);


//     if (!check_overlap(new_node)) {
//         insert_node(new_node);
//         // display_adj_matrix();
//     }
// }

int check_if_overlap_with_any_vertex(SDL_Point* point)
{
    for (int i=0; i<vertex_v.size(); i++) {
        SDL_Point* vertex = vertex_v.at(i);
        if (distance(point, vertex) < (2 * CIRCLE_RADIUS)) return i;
    }

    return -1;
}

void create_vertex(NODE* new_node)
{
    // graph.push_back(new_node);

    // vector<int>* new_row= new vector<int>();
    //     for (NODE* node : graph)
    //     new_row->push_back(distance(new_node, node));
    // adj.push_back(new_row);

    // for (size_t i=0; i<(adj.size() - 1); i++) {
    //     vector<int>* row = adj.at(i);
    //     row->push_back(distance(new_node, graph.at(i)));
    // }

    graph.push_back(new vector<int>());
    vertex_v.push_back(new SDL_Point{new_node->x, new_node->y});
}

int get_hovering_node()
{
    SDL_Point mouse_pos;
    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

    for (int i=0; i<graph.size(); i++)
    if (distance(&mouse_pos, vertex_v.at(i)) < (2 * CIRCLE_RADIUS)) return i;

    return -1;
}

void hightlight_hovering_node()
{
    int node_index = get_hovering_node();
    if (node_index == -1) return;

    SDL_Point* v_pos = vertex_v.at(node_index);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    draw_circle(v_pos->x, v_pos->y, 2 * CIRCLE_RADIUS);
}

void reset()
{
    graph.clear();
    vertex_v.clear();
}

// void display_adj_matrix()
// {
//     for (vector<int>* row : adj) {
//         for (int entry : (*row))
//             cout << entry << "\t";
//         cout << endl;
//     }
// }

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
