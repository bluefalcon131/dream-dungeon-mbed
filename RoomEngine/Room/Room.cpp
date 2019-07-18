#include "Room.h"

// Constructor
Room::Room(int no_of_enemies, int room_type)
{
    _before_boss_room = 4;
    
    _room_type = room_type;
    
    for(int side = 0; side < 4; side++) {
        _doorways[side] = false;
    }
    for(int id = 0; id < MAX_ENEMIES; id++) {
        valid_collectibles[id] = false;
    }
    
    if(room_type >= 10) {   // Special Case for Boss rooms
        init_boss_room();
    } else {
        for (int id = 0; id < MAX_ENEMIES; id++) {
            valid_enemies[id] = id < no_of_enemies;
            if (id < no_of_enemies) {   // For every undefined valid enemy, define:
                enemies_type[id] = (int)(rand() % 3)/2; // 2/3 chance headless 1/3 chance snake
                rand_enemy_coordinate(id);  // define random spawn coordinate
            }
        }
        if (room_type == 0){
            init_normal_room();
        } else if (room_type == 1){
            init_middle_walled_room();
        } else if (room_type == 2){
            init_side_walled_room();
        }
    }
}

void Room::init_boss_room()
{
    valid_walls[0] = false;
    valid_walls[1] = false;
    valid_enemies[0] = true;
    for (int id = 1; id < MAX_ENEMIES; id++) {  // Updating valid_enemies to be false for all the others
        valid_enemies[id] = false;
    }
}

void Room::init_normal_room()
{
    valid_walls[0] = false;
    valid_walls[1] = false;
}

void Room::init_middle_walled_room()
{
    valid_walls[0] = true;
    _wall_stat[0][0] = 14;
    _wall_stat[0][1] = 22;
    _wall_stat[0][2] = 56;
    _wall_stat[0][3] = 12;
    
    valid_walls[1] = false;
}

void Room::init_side_walled_room()
{
    valid_walls[0] = true;
    _wall_stat[0][0] = 16;
    _wall_stat[0][1] = 18;
    _wall_stat[0][2] = 7;
    _wall_stat[0][3] = 19;
    
    valid_walls[1] = true;
    _wall_stat[1][0] = 61;
    _wall_stat[1][1] = 18;
    _wall_stat[1][2] = 7;
    _wall_stat[1][3] = 19;
}

// Deconstructor
Room::~Room()
{
    
}

// Mutator
void Room::set_doorway(int index, bool doorway_value)   // Sets doorways to the needed value at index
{
    _doorways[index] = doorway_value;
}

void Room::set_boss_doorway(int before_boss_room)   // Sets the boss doorway
{
    _before_boss_room = before_boss_room;
}

// Accessors
char * Room::get_current_map_2d(){
    return ((char *)level_map[0][0]);
}

bool * Room::get_doorways()
{
    return (bool *)_doorways;
}

bool Room::get_doorway(int index)
{
    return _doorways[index];
}

char Room::get_room_type()
{
    return _room_type;
}

int Room::get_boss_doorway()
{
    return _before_boss_room;
}

// Functions
void Room::rand_enemy_coordinate(int id)
{
    _spawn_point_coord = rand() % n_spawn_points[_room_type];   // Random available spawning coordinate ID
    _spawn_point_counter = 0;
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
            if(spawn_area[_room_type][j][i] == 0){  // Locate available spawning coordinate
                _spawn_point_counter++; // Increment counter ID
            }
            if(_spawn_point_counter >= _spawn_point_coord){ // If counter ID  reaches the random coordinate ID
                _enemy_coord[id][0] = i;    // Set the random coordinate
                _enemy_coord[id][1] = j;
                goto enemy_coord_set;
            }
        }
    }
    enemy_coord_set:{}  // Acts as a break since there are two for loops
}

void Room::load()   // Spawns all Mobs and Walls with reset status (HP, Attack etc) given that they have not died yet (still valid)
{
    if(_room_type == 10) {
        if (valid_enemies[0]) {
            enemies[0] = new Skull(33, 23);
        }
    } else {
        for (int id = 0; id < MAX_ENEMIES; id++) {
            if (valid_enemies[id]) {
                switch(enemies_type[id]){
                    case 0 :
                        enemies[id] = new Headless(_enemy_coord[id][0], _enemy_coord[id][1]); break;
                    case 1 :
                        enemies[id] = new Snake(_enemy_coord[id][0], _enemy_coord[id][1]); break;
                }
            }
        }
        for (int id = 0; id < 2; id++) {
            if (valid_walls[id]) {
                walls[id] = new Walls(_wall_stat[id][0], _wall_stat[id][1], _wall_stat[id][2], _wall_stat[id][3]);
            }
        }
    }
}

void Room::unload() // Delete existing enemies and walls
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (valid_enemies[i]) {
            delete enemies[i];
        }
    }
    for (int i = 0; i < 2; i++){
        if (valid_walls[i]) {
            delete walls[i];
        }
    }
}

void Room::update_doorways()    // If it's a boss, close the doorways, else, 
{
    if(_room_type == 10) { 
        _doorways[0] = false;
        _doorways[1] = false;
        _doorways[2] = false;
        _doorways[3] = false;
    }
}

void Room::draw(N5110 &lcd, int j)
{
    draw_enemies(lcd, j);
    draw_collectibles(lcd, j);
    draw_walls(lcd, j);
}

void Room::draw_enemies(N5110 &lcd, int j)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (valid_enemies[i]) {
            if (enemies[i]->get_pos_y() == j) {
                enemies[i]->draw(lcd);
            }
        }
    }
}

void Room::draw_collectibles(N5110 &lcd, int j)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (valid_collectibles[i]) {
            if (collectibles[i]->get_pos_y() == j) {
                collectibles[i]->draw(lcd);
            }
        }
    }
}

void Room::draw_walls(N5110 &lcd, int j)
{
    for (int i = 0; i < 2; i++) {
        if (valid_walls[i]) {
            if (walls[i]->get_pos_y() == j) {
                walls[i]->draw(lcd);
            }
        }
    }
}
void Room::draw_room(N5110 &lcd)
{
    lcd.drawSprite(0, 0, screen_height, screen_width, (char *)level_map[1]); // drawing 3d map
    draw_doorways(lcd); // Draw walls that are behind the player
    if (_before_boss_room == 0) {    // Displaying Special Doorway to Boss room
        lcd.drawSprite(35, 0, 12, 14, (char *)boss_doorway_n[0]);
    }
}

void Room::draw_doorways(N5110 &lcd)
{
    if(!_doorways[0]) { // N
        lcd.drawSprite(36, 0, 10, 12, (char *)wall_n);
    }
}

void Room::draw_room_overlay(N5110 &lcd)
{
    lcd.drawSpriteTransparent(0, 0, screen_height, screen_width, (char *)level_map[2]); // drawing 3d map overlay
    draw_doorways_overlay(lcd);
    if (_before_boss_room == 0) {    // Displaying Special Doorway to Boss room
        lcd.drawSpriteTransparent(35, 0, 12, 14, (char *)boss_doorway_n[1]);
    } else if (_before_boss_room == 1) {
        lcd.drawSpriteTransparent(79, 14, 19, 5, (char *)boss_doorway_e);
    } else if (_before_boss_room == 2) {
        lcd.drawSpriteTransparent(35, 41, 7, 14, (char *)boss_doorway_s);
    } else if (_before_boss_room == 3) {
        lcd.drawSpriteTransparent(0, 14, 19, 5, (char *)boss_doorway_w);
    }
}

void Room::draw_doorways_overlay(N5110 &lcd)    // Draw walls that are in front of the player
{
    if(!_doorways[1]) { // E
        lcd.drawSpriteTransparent(81, 15, 11, 3, (char *)wall_x[0]);
    }
    if(!_doorways[2]) { // S
        lcd.drawSpriteTransparent(36, 45, 3, 12, (char *)wall_s);
    }
    if(!_doorways[3]) { // W
        lcd.drawSpriteTransparent(0, 15, 11, 3, (char *)wall_x[1]);
    }
}

bool Room::enemies_exist()  // Returns true if valid enemies exist
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (valid_enemies[i]) {
            return true;
        }       
    }
    return false;
}