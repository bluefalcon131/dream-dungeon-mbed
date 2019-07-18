/*
ELEC2645 Embedded Systems Project
School of Electronic & Electrical Engineering
University of Leeds
Name: Steven Mahasin
Username: el17sm
Student ID Number: 201192939
Date: 11/04/2019
*/
#include "main.h"

int main()
{
    // Initialize
    init();
    
    while(1) { // Gameloop
        boss_room_exist = false;    // Game initialize variables
        number_of_enemies_killed = 0;
        total_time = 0;
        
        title.main(lcd, gamepad, global_contrast);
        srand(title.get_seed());
        player = new Player(39, 27);
        room_engine = new RoomEngine(global_contrast);
        
        game_loop();
        game_unload(); // Deletion of player, rooms, roomengine
    }
}

void init()
{
    lcd.init();
    lcd.setContrast(global_contrast); 
    gamepad.init();
    for (int j = 0; j < MAX_ROOMS_MAP_Y; j++){
        for (int i = 0; i < MAX_ROOMS_MAP_X; i++){
            valid_rooms[j][i] = false;
        }
    }
}

void game_loop()
{
    while(1) {  // Floor Loop 
        boss_room_number = 5 + rand() % 4; // Boss room appears after travelling 5-8 rooms
        boss_room_counter = 0;
        while(1) {  // Room Loop
            room_entrance();    // Generation of new room, loading of room and entrance scene
            while(room_engine->check_player_room_position() == INSIDE) {  // actions inside the Room
                room_engine->read_input(gamepad);
                room_engine->update(number_of_enemies_killed);
                room_engine->render(lcd, gamepad);
                minimap_detection();
                total_time++;   // Incrementing time score
                if  (player->get_hp() <= 0) {goto gameover;}    // gameover if player health depleted
                if ((rooms[room_y][room_x]->get_room_type() == 10) && !(rooms[room_y][room_x]->enemies_exist())){goto winner;}  // wins game if room is a boss room, and the boss is dead
            }
            room_exit();    // Exit scene, deletion of existing entities and update of room coordinates
        }
    }
    gameover : { game_over(); goto displaystats;}
    winner : { win(); goto displaystats;}
    displaystats : { display_stats();}
}

void room_entrance()
{
    update_room_coords();   // Accessor to room_engine room coords
    if (!valid_rooms[room_y][room_x]){generate_room();} // generate a new room if player enters a nonexistent room
    room_engine->load(player, rooms[room_y][room_x]);
    room_engine->entrance_scene(lcd, gamepad);
}

void room_exit()
{
    room_engine->exit_scene(lcd, gamepad);
    rooms[room_y][room_x]->unload();
    player->delete_bullets();
    room_engine->update_current_room(); // Increments room coord
}

void generate_room()
{
    valid_rooms[room_y][room_x] = true; // Sets the room coord to be valid
    if (boss_room_counter == 0) {   // if first room
        rooms[room_y][room_x] = new Room(0, 0); // no enemies
        rooms[room_y][room_x]->set_doorway(0, true);
    } else {
        rooms[room_y][room_x] = new Room(rand() % 4, 0);    // random enemies (0-3)
        if (boss_room_counter < boss_room_number) {no_of_doorways = 2 + (rand() % 100 < 10) + (rand() % 100 < 10);} // 20% chance of adding doorways
        else {no_of_doorways = 1;}  // If boss room exist, ensure all unexplored rooms branch out into a dead end
        while (count_doorways() < no_of_doorways) {
            rooms[room_y][room_x]->set_doorway(rand() % 4, true);   // Setting random doorways until number of desired doorways
        }
        update_definite_doorways();
        for (int i = 0; i < 4; i++) {   // Sets the definitive doorways
            if (cannot[i]){rooms[room_y][room_x]->set_doorway(i, false);}
            if (have_to[i]){rooms[room_y][room_x]->set_doorway(i, true);}
        }
        if ((boss_room_counter >= boss_room_number) && (!boss_room_exist)) {    // Sets the doorway towards the boss room to be a boss doorway
            rooms[room_y][room_x]->set_boss_doorway(available_boss_room());
            boss_room_exist = true;
        }
    }
    boss_room_counter++;
}

void update_room_coords()
{
    room_y = room_engine->get_room_y();
    room_x = room_engine->get_room_x();
}

void minimap_detection()
{
    while(gamepad.check_event(Gamepad::R_PRESSED)) {
        lcd.clear();
        for (int j = 0; j < MAX_ROOMS_MAP_Y; j++) {
            for (int i = 0; i < MAX_ROOMS_MAP_X; i++) {
                if (valid_rooms[j][i]) {
                    draw_minimap(j,i);
                }
            }
        }
        lcd.drawSpriteTransparent(33, 17, 15, 20, (char *)minimap_sprite[3]); // draws your current room
        lcd.refresh();
        wait_ms(1000/40);
    };
}

void draw_minimap(int j, int i)
{
    lcd.drawSprite(33 + (i-room_x)*20, 17 + (j-room_y)*15, 15, 20, (char *)minimap_sprite[0]);  // draws normal room
    if (rooms[j][i]->get_room_type() == 10) {
        lcd.drawSprite(33 + (i-room_x)*20, 17 + (j-room_y)*15, 15, 20, (char *)minimap_sprite[2]);  // draws boss room
    } else if (rooms[j][i]->enemies_exist()) {
        lcd.drawSprite(33 + (i-room_x)*20, 17 + (j-room_y)*15, 15, 20, (char *)minimap_sprite[1]);  // draws mob room
    }
    if (rooms[j][i]->get_doorway(0)) {  // Drawing all doorways
        lcd.drawLine(42 + (i-room_x)*20, 17 + (j-room_y)*15, 43 + (i-room_x)*20, 17 + (j-room_y)*15, 1);
    }
    if (rooms[j][i]->get_doorway(1)) {
        lcd.drawLine(52 + (i-room_x)*20, 23 + (j-room_y)*15, 52 + (i-room_x)*20, 24 + (j-room_y)*15, 1);
    }
    if (rooms[j][i]->get_doorway(2)) {
        lcd.drawLine(42 + (i-room_x)*20, 31 + (j-room_y)*15, 43 + (i-room_x)*20, 31 + (j-room_y)*15, 1);
    }
    if (rooms[j][i]->get_doorway(3)) {
        lcd.drawLine(33 + (i-room_x)*20, 23 + (j-room_y)*15, 33 + (i-room_x)*20, 24 + (j-room_y)*15, 1);
    }
}

void game_over()
{
    lcd.clear();
    lcd.setContrast(global_contrast);
    lcd.printString("Game Over", 0, 0);     
}

void win()
{
    lcd.clear();
    lcd.setContrast(global_contrast);
    lcd.printString("You won!", 0, 0);   
}

void display_stats()
{
    lcd.printString("Restart?", 0, 1);   
    lcd.printString("Enemies Killed:", 0, 2);
    char kills[10];
    sprintf(kills, "%d enemies", number_of_enemies_killed);
    lcd.printString(kills, 0, 3);
    lcd.printString("Time:", 0, 4);
    char total_duration[10];
    sprintf(total_duration, "%d seconds", (total_time/40));
    lcd.printString(total_duration, 0, 5);
    lcd.refresh();
    while(gamepad.check_event(Gamepad::A_PRESSED)) {
    }
    wait(0.05);
    while(!gamepad.check_event(Gamepad::A_PRESSED)) {
    }
    wait(0.05);
    while(gamepad.check_event(Gamepad::A_PRESSED)) {
    }
}

int available_boss_room()
{
    if (!valid_rooms[room_y - 1][room_x]){  // if any of the adjacent room is invalid, it is replaced with a boss room
        rooms[room_y][room_x]->set_doorway(0, true);
        set_boss_room(room_y - 1, room_x, 0);
        return 0;
    } else if (!valid_rooms[room_y][room_x + 1]){
        rooms[room_y][room_x]->set_doorway(1, true);
        set_boss_room(room_y, room_x + 1, 1);
        return 1;
    } else if (!valid_rooms[room_y + 1][room_x]){
        rooms[room_y][room_x]->set_doorway(2, true);
        set_boss_room(room_y + 1, room_x, 2);
        return 2;
    } else if (!valid_rooms[room_y][room_x - 1]){
        rooms[room_y][room_x]->set_doorway(3, true);
        set_boss_room(room_y, room_x - 1, 3);
        return 3; }
    delete rooms[room_y - 1][room_x];   // if all adjacent room is valid, mutate the top room into a boss room (default case)
    rooms[room_y][room_x]->set_doorway(3, true);
    set_boss_room(room_y - 1, room_x, 0);
    return 0;
}

void set_boss_room(int room_y, int room_x, int side)
{
    valid_rooms[room_y][room_x] = true;
    rooms[room_y][room_x] = new Room(0, 10);
    rooms[room_y][room_x]->set_doorway(opposite(side), true);   // Sets a definite doorway on the side player comes from
    if ((opposite(side) != 0) && (valid_rooms[room_y - 1][room_x])){ // Deletes any existing doorways unless player entered from that side
        if (rooms[room_y - 1][room_x]->get_doorway(2)){
            rooms[room_y - 1][room_x]->set_doorway(2, false);
    }}
    if ((opposite(side) != 1) && (valid_rooms[room_y][room_x + 1])){
        if (rooms[room_y][room_x + 1]->get_doorway(3)){
            rooms[room_y][room_x + 1]->set_doorway(3, false);
    }}
    if ((opposite(side) != 2) && (valid_rooms[room_y + 1][room_x])){
        if (rooms[room_y + 1][room_x]->get_doorway(0)){
            rooms[room_y + 1][room_x]->set_doorway(0, false);
    }}
    if ((opposite(side) != 3) && (valid_rooms[room_y][room_x - 1])){
        if (rooms[room_y][room_x - 1]->get_doorway(1)){
            rooms[room_y][room_x - 1]->set_doorway(1, false);
    }}
}

void game_unload()
{
    delete room_engine;
    // Deletes every generated rooms
    for (int i = 0; i < MAX_ROOMS_MAP_X; i++) { 
        for (int j = 0; j < MAX_ROOMS_MAP_Y; j++) {
            if (valid_rooms[j][i]){
                delete rooms[j][i];
                valid_rooms[j][i] = false;
            }
        }
    }
    delete player;
}

// Functions
int opposite(int value)
{
    if (value <= 1) {
        return value + 2;
    } else {
        return value - 2;
    }
}

int count_doorways()    // counts number of exisisting doorways
{
    int count = 0;
    for (int i = 0; i < 4; i++){
        if (rooms[room_y][room_x]->get_doorway(i)) {
            count++;
        }
    }
    return count;
}

void update_definite_doorways()
{
    update_definite_doorways_up();
    update_definite_doorways_right();
    update_definite_doorways_down();
    update_definite_doorways_left();
}

void update_definite_doorways_up()
{
    if (room_y == 1) {  // if room to be generated is on the border, then doorway cannot exist
        cannot[0] = true;
        have_to[0] = false;
    } else if (valid_rooms[room_y - 1][room_x]){    // if room to be generated has an existing room above it
        if (rooms[room_y - 1][room_x]->get_doorway(2)){ // if room to be generated has an existing doorway, then doorway must exist
            have_to[0] = true;
            cannot[0] = false;
        } else {    // if room to be generated does not have an existing doorway, then doorway must not exist
            have_to[0] = false;
            cannot[0] = true;
        }
    } else {    // else the room does not have any definite doorways set on it's north
        have_to[0] = false;
        cannot[0] = false;
    }
}
void update_definite_doorways_right()
{
    if (room_x == 10) { // if room to be generated is on the border, then doorway cannot exist
        cannot[1] = true;
        have_to[1] = false;
    } else if (valid_rooms[room_y][room_x + 1]){    // if room to be generated has an existing room on it's right
        if (rooms[room_y][room_x + 1]->get_doorway(3)){ // if room to be generated has an existing doorway, then doorway must exist
            have_to[1] = true;
            cannot[1] = false;
        } else {    // if room to be generated does not have an existing doorway, then doorway must not exist
            have_to[1] = false;
            cannot[1] = true;
        }
    } else {    // else the room does not have any definite doorways set on it's right
        have_to[1] = false;
        cannot[1] = false;
    }
}

void update_definite_doorways_down()
{
    if (room_y == 10) { // if room to be generated is on the border, then doorway cannot exist
        cannot[2] = true;
        have_to[2] = false;
    } else if (valid_rooms[room_y + 1][room_x]){    // if room to be generated has an existing room below it
        if (rooms[room_y + 1][room_x]->get_doorway(0)){ // if room to be generated has an existing doorway, then doorway must exist
            have_to[2] = true;
            cannot[2] = false;
        } else {    // if room to be generated does not have an existing doorway, then doorway must not exist
            have_to[2] = false;
            cannot[2] = true;
        }
    } else {    // else the room does not have any definite doorways set on it's south
        have_to[2] = false;
        cannot[2] = false;
    }
}

void update_definite_doorways_left()
{
    if (room_x == 1) {  // if room to be generated is on the border, then doorway cannot exist
        cannot[3] = true;
        have_to[3] = false;
    } else if (valid_rooms[room_y][room_x - 1]){    // if room to be generated has an existing room on it's left
        if (rooms[room_y][room_x - 1]->get_doorway(1)){ // if room to be generated has an existing doorway, then doorway must exist
            have_to[3] = true;
            cannot[3] = false;
        } else {    // if room to be generated does not have an existing doorway, then doorway must not exist
            have_to[3] = false;
            cannot[3] = true;
        }
    } else {    // else the room does not have any definite doorways set on it's left
        have_to[3] = false;
        cannot[3] = false;
    }
}