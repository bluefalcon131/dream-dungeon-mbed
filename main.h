#ifndef MAIN_H
#define MAIN_H

// Pre-Processor
#include "mbed.h"
#include "Gamepad.h"
#include "N5110.h"
#include "math.h"
#include "sprites.h"
#include "Entity.h"
#include "Player.h"
#include "Headless.h"
#include "Snake.h"
#include "RoomEngine.h"
#include "Title.h"

#define INSIDE 4

// Variables
float global_contrast = 0.5;
int boss_room_counter = 0;  // Counter of how mnay rooms have been explored/spawned
int boss_room_number;   // Number of rooms that must be explored for a boss room to spawn
bool boss_room_exist;   // Wether or not boss room has been spawned
int number_of_enemies_killed;   // For scoring, no of kills
int total_time;                 // For scoring, time of which the game was played (without pause, without minimap, without room transitions)
int no_of_doorways; // For room generation, number of doorways that room should have
int room_x = MAX_ROOMS_MAP_X;   // Room x-coordinate
int room_y = MAX_ROOMS_MAP_Y;   // Room y-coordinate
bool have_to[4] = {false, false, false, false}; // Array of which doorways must exist (index order = NESW)
bool cannot[4] = {false, false, false, false};  // Array of which doorways must not exist (index order = NESW)
Player *player;
Room *rooms[MAX_ROOMS_MAP_Y][MAX_ROOMS_MAP_X];
bool valid_rooms[MAX_ROOMS_MAP_Y][MAX_ROOMS_MAP_X];
RoomEngine *room_engine;

// Objects
N5110 lcd(PTC9,PTC0,PTC7,PTD2,PTD1,PTC11);
Gamepad gamepad;
Title title;

// Prototypes
void init();
void game_loop();

void room_entrance();
void room_exit();
void generate_room();
void update_room_coords();
void minimap_detection();
void draw_minimap(int j, int i);

void game_over();
void win();
void display_stats();
void game_unload();

int opposite(int value);
int count_doorways();
void update_definite_doorways();
void update_definite_doorways_up();
void update_definite_doorways_right();
void update_definite_doorways_down();
void update_definite_doorways_left();

int available_boss_room();
void set_boss_room(int room_y, int room_x, int side);

#endif