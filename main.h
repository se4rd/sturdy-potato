#include <SDL2/SDL.h>

#define NODE          SDL_Point
#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 600
#define CIRCLE_RADIUS 20

#define COLOR_RED   SDL_Color {255,   0,   0}
#define COLOR_BLACK SDL_Color {  0,   0,   0}
#define COLOR_WHITE SDL_Color {255, 255, 255}

void clear_background(SDL_Colour color);

void handle_mouse_event(SDL_Event* event);
void handle_keyboard_event(SDL_Event* event);

void draw_graph_nodes();
void draw_graph_edges();
void draw_nodes_index();

void create_new_node();
bool check_overlap(NODE* node);
void insert_node(NODE* new_node);

int get_hovering_node();
void hightlight_hovering_node();

void clear_canvas();
void display_adj_matrix();

void sdl_log_error_and_exit();
void ttf_log_error_and_exit();
double distance(SDL_Point* Point_A, SDL_Point* Point_B);
void draw_circle(int32_t centreX, int32_t centreY, int32_t radius);