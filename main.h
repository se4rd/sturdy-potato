#include <vector>
#include <SDL2/SDL.h>
using namespace std;

#define NODE          SDL_Point
#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 600
#define CIRCLE_RADIUS 20

#define COLOR_RED   SDL_Color {255,   0,   0}
#define COLOR_BLACK SDL_Color {  0,   0,   0}
#define COLOR_WHITE SDL_Color {255, 255, 255}

// void execute_tsp();
// vector<vector<int>> calculate_permutations(vector<int> *l);
// int calculate_distance(vector<int>* path);

void clear_background(SDL_Colour color);

void handle_mouse_button_event(SDL_Event* event);
void handle_mouse_motion_event(SDL_Event* event);
void handle_keyboard_event(SDL_Event* event);

void draw_vertex_all();
void draw_edge_all();
void draw_edge_being_created();
void draw_edge_between(SDL_Point* vertex1, SDL_Point* vertex2);
void draw_graph_edges();
void draw_nodes_index();

// void create_new_node();
int check_if_overlap_with_any_vertex(SDL_Point* point);
void create_vertex(NODE* new_node);

int get_hovering_node();
void hightlight_hovering_node();

void reset();
void display_adj_matrix();

void sdl_log_error_and_exit();
void ttf_log_error_and_exit();
double distance(SDL_Point* Point_A, SDL_Point* Point_B);
void draw_circle(int32_t centreX, int32_t centreY, int32_t radius);