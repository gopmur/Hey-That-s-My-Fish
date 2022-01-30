#pragma once

#include "allegro5/allegro.h"

#include "data_types.h"
#include "defines.h"

// this function checks the  initialization of a given allegro function
// if the the given allegro function didn't initialize properly returns
// true and prints out the error
void check_init(bool function, char *description, bool *error);

bool get_screen_resolution(int *resX, int *resY);

bool validate_move(GameData gameData);

bool check_possible_moves(int i, int j, Tile tileMap[TILE_ROW][TILE_COL]);

void check_for_lost(GameData *gameData);

void remove_player(int player, GameData *gameData);

// this function generates a random combination of the tile map 
void generate_random_tile_map(Tile tileMap[TILE_ROW][TILE_COL]);

// this function draws a hexagon using 6 triangles
void draw_hexagon(float x, float y, float length, ALLEGRO_COLOR color);

void draw_start_screen(GameData gameData);

void draw_main_menu(GameData gameData);

void draw_player_select_menu(GameData gameData);

void draw_game_screen(GameData gameData);

void draw_settings_menu(GameData gameData, int resList[][2]);

void draw_winner_screen(GameData gameData);

void key_handle_start_screen(ALLEGRO_EVENT event, GameData *gameData);

void key_handle_main_menu(ALLEGRO_EVENT event, GameData *gameData, bool *done, int resList[][2]);

void key_handle_player_count_menu(ALLEGRO_EVENT event, GameData *gameData, int *penguinCountTemp);

void key_handle_settings_menu(ALLEGRO_EVENT event, GameData *gameData, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue, int resList[][2]);

void key_handle_game_screen(ALLEGRO_EVENT event, GameData *gameData, int *penguinCountTemp);

void key_handle_winner_screen(ALLEGRO_EVENT event, GameData *gameData);