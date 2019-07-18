#include "RoomEngine.h"
// Constructor
RoomEngine::RoomEngine(float global_contrast)
{
    _room_x = MAX_ROOMS_MAP_X / 2;
    _room_y = MAX_ROOMS_MAP_Y / 2;
    _global_contrast = global_contrast;
}

// Destructor
RoomEngine::~RoomEngine()
{
    room->unload();
}

// Public Functions
void RoomEngine::load(Player *current_player, Room *current_room)
{
    player = current_player;
    room = current_room;
    set_input(true,0,0,0,0,0,0,0);  // Displays health throughout entrance_scene
    update_player_position(check_player_room_position()); // Moving the player such that he enters opposite of his exit
    room->load();
}

void RoomEngine::update_player_position(int side)
{
    switch(side) { // Depending on which side it exits from, player is repositioned
        case 0 :    // N
            player->set_position(39, 49);
            break;
        case 1 :    // E
            player->set_position(0 - player->get_hitbox_width(), 25);
            break;
        case 2 :    // S
            player->set_position(39, 0 - player->get_hitbox_height());
            break;
        case 3 :    // W
            player->set_position(85, 25);
            break;
        case 4 :    // Default where an exit does not exist (starting position)
            player->set_position(39, 30);
            break;
    }
}

void RoomEngine::entrance_scene(N5110 &lcd, Gamepad &gamepad)
{
    int side = check_player_room_position();
    for(int i = 0; i<50; i++) {
        switch(side) {  // Setting movement of player as it enters the screen (velocity)
            case 0 :
                set_mapped_coord(0, -((4 + player->get_sprite_height()) / (50 * player->get_velocity()))); break;
            case 1 :
                set_mapped_coord(-((4 + player->get_hitbox_width()) / (50 * player->get_velocity())), 0); break;
            case 2 :
                set_mapped_coord(0, ((4 + player->get_hitbox_height()) / (50 * player->get_velocity()))); break;
            case 3 :
                set_mapped_coord(((4 + player->get_hitbox_width()) / (50 * player->get_velocity())), 0); break;
        }
        move_player();
        render(lcd, gamepad);
        if (0.75 - (i * 0.005) > _global_contrast) {    // Fade in
            lcd.setContrast(0.75 - (i * 0.005));
        } else { lcd.setContrast(_global_contrast);}
    }
}

int RoomEngine::check_player_room_position() // returns 0,1,2,3 if the player exits the respective directions, returns 4 if the player is in the room
{
    if (player->get_pos_y() < 0) {
        return 0;
    }
    else if (player->get_pos_x() > WIDTH - (player->get_hitbox_width())) {
        return 1;
    }
    else if (player->get_pos_y() > HEIGHT - (player->get_hitbox_height())) {
        return 2;
    }
    else if (player->get_pos_x() < 0) {
        return 3;
    }
    else {
        return 4;
    }
}

void RoomEngine::read_input(Gamepad &gamepad)   // Updates member variables for easier access
{
    _L = gamepad.check_event(Gamepad::L_PRESSED);
    _R = gamepad.check_event(Gamepad::R_PRESSED);
    _A = gamepad.check_event(Gamepad::A_PRESSED);
    _B = gamepad.check_event(Gamepad::B_PRESSED);
    _X = gamepad.check_event(Gamepad::X_PRESSED);
    _Y = gamepad.check_event(Gamepad::Y_PRESSED);
    mapped_coord = gamepad.get_mapped_coord();
}

void RoomEngine::update(int &number_of_enemies_killed)  // Updates all HP, deletes dead entities, increment score (kills),
{                                                       // checks wall collisions (exclusive for entity:walls), movements for all entities and player action detection
    room->update_doorways();
    check_damage();
    check_enemies_death(number_of_enemies_killed);
    check_walls_collision();
    move();
    player->buttons(_A, _B, _Y, _X);
}

void RoomEngine::check_damage()
{
    check_damage_player();  // damage player if collide with enemy / heal if collide with hearts
    check_damage_enemies(); // damage enemy if collide with player's bullets
}


void RoomEngine::check_enemies_death(int &number_of_enemies_killed) // Deletes dead enemies, spawn hearts based on chance(defined in each enemy) and increments kill score
{
    // Enemy Death
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if((room->valid_enemies[i]) && (room->enemies[i]->get_hp() <= 0)) {
            if ((rand() % 100) < room->enemies[i]->get_hp_drop_chance()){
                for (int j = 0; j < MAX_ENEMIES; j++) {
                    if (!room->valid_collectibles[j]) {
                        room->collectibles[j] = new Health(room->enemies[i]->get_pos_x(), room->enemies[i]->get_pos_y()); // Spawn a health drop
                        room->valid_collectibles[j] = true;
                        break;
                    }
                }
            }
            delete room->enemies[i];
            room->valid_enemies[i] = false;
            number_of_enemies_killed++;
        }
    }
}

void RoomEngine::check_walls_collision()    // Undo moves of player and enemy if colliding with entity:wall and kills bullets when colliding with entity:wall
{                                           // Currently unused (room types 0 and 10 do not spawn entity:wall)
    // Enemy
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if(room->valid_enemies[i]) {    // Undo move of every valid enemy upon collision with entity:wall
            room->enemies[i]->undo_move_x(entity_move_check_x(room->enemies[i], room->walls, 2, 10, room->valid_walls));
            room->enemies[i]->undo_move_y(entity_move_check_y(room->enemies[i], room->walls, 2, 10, room->valid_walls));
        }
    }
    // Player
    player->undo_move_x(entity_move_check_x(player, room->walls, 2, 10, room->valid_walls));
    player->undo_move_y(entity_move_check_y(player, room->walls, 2, 10, room->valid_walls));
    // Bullets
    for (int i = 0; i < bullets_max; i++) {
        for (int j = 0; j < 2; j++) {   // given that both walls and bullets are valid, check if they're colliding
            if ((player->valid_bullets[i]) && (room->valid_walls[j]) && (entity_collision(*player->bullets_array[i], *room->walls[j]))) {
                delete player->bullets_array[i]; player->valid_bullets[i] = false;
            }
        }
    }
}

void RoomEngine::move()
{
    move_player();
    move_enemies();
}

void RoomEngine::render(N5110 &lcd, Gamepad &gamepad)
{
    pause_detection(lcd, gamepad);
    lcd.clear();
    draw(lcd);
    lcd.refresh();
    wait_ms(1000/40); // setting FPS
}

void RoomEngine::pause_detection(N5110 &lcd, Gamepad &gamepad)
{
    if(gamepad.check_event(Gamepad::START_PRESSED)) {
        draw_health(lcd);
        char * paused_screen = lcd.readScreen();    // Saves current screen
        int pause_timer = 0;
        lcd.drawSpriteTransparent(20, 20, 9, 45, (char *)pause_sprite);
        // Ensures that Start button is toggled twice to exit loop
        while(gamepad.check_event(Gamepad::START_PRESSED)) {
            draw_pause_screen(lcd, paused_screen, pause_timer);
        }
        while(!gamepad.check_event(Gamepad::START_PRESSED)) {
            draw_pause_screen(lcd, paused_screen, pause_timer);
        }
        while(gamepad.check_event(Gamepad::START_PRESSED)) {
            draw_pause_screen(lcd, paused_screen, pause_timer);
        }
    }
}

void RoomEngine::draw_pause_screen(N5110 &lcd, char * paused_screen, int &pause_timer)
{
    lcd.clear();
    lcd.drawSprite(0, 0, HEIGHT, WIDTH, paused_screen);
    if (pause_timer % 20 < 10) {    // Draws pause sprite only 10/20 frames of pause_timer, this way pause blinks
        lcd.drawSpriteTransparent(20, 20, 9, 45, (char *)pause_sprite);
    }
    lcd.refresh();
    pause_timer++;
    wait_ms(1000/40);
}

void RoomEngine::draw(N5110 &lcd)   // Draws everything onto the screen
{   
    room->draw_room(lcd);
    for(int j = 0; j < HEIGHT; j++) {   // To create a 3D illusion, all entities are drawn at the order of it's hitbox height (highest to lowest)
        if (j == player->get_pos_y()) {
            player->draw(lcd);
        }
        player->draw_bullets(lcd, j);
        room->draw(lcd, j);
    }
    
    room->draw_room_overlay(lcd);   // Special overlay such as side doorways and boss doorways
    
    if (_L) {   // Displaying Hearts if L is pressed
        draw_health(lcd);
    }
}

void RoomEngine::draw_health(N5110 &lcd)
{
    for (int i = 0; i < player->get_hp(); i++){ // For every health, draw a heart at x pos i*10
        lcd.drawSpriteTransparent(i*10,
                                  0,
                                  player->get_hearts_height(),
                                  player->get_hearts_width(),
                                  player->get_hearts_sprite());
    }
}

void RoomEngine::exit_scene(N5110 &lcd, Gamepad &gamepad)   // Plays an exit scene
{
    int side = check_player_room_position();
    
   for(int i = 0; i<50; i++) {
        switch(side) {  // Setting movement of player as it exits the screen (velocity)
            case 0 :
                set_mapped_coord(0, (player->get_velocity() / 2)); break;
            case 1 :
                set_mapped_coord((player->get_velocity() / 2), 0); break;
            case 2 :
                set_mapped_coord(0, -(player->get_velocity() / 2)); break;
            case 3 :
                set_mapped_coord(-(player->get_velocity() / 2), 0); break;
        }
        move_player();
        render(lcd, gamepad);
        lcd.setContrast(_global_contrast + (i * 0.005)); // Fade out
    }
    lcd.setContrast(0.75);
}

void RoomEngine::update_current_room()  // Increments room coord depending on direction
{
    switch(check_player_room_position()) {
        case 0 :
            _room_y--;
            break;
        case 1 :
            _room_x++;
            break;
        case 2 :
            _room_y++;
            break;
        case 3 :
            _room_x--;
            break;
        default :
        break;
    }
}

// Public Accessors

int RoomEngine::get_room_x()
{
    return _room_x;
}
int RoomEngine::get_room_y()
{
    return _room_y;
}

// Private Mutators

void RoomEngine::set_input(bool L, bool R, bool A, bool B, bool X, bool Y, float mapped_x, float mapped_y)
{
    _L = L;
    _R = R;
    _A = A;
    _B = B;
    _X = X;
    _Y = Y;
    set_mapped_coord(mapped_x, mapped_y);
}

void RoomEngine::set_mapped_coord(float x, float y)
{
    mapped_coord.x = x;
    mapped_coord.y = y;
}

// Methods

bool RoomEngine::entity_collision(Entity &a, Entity &b)  // returns true if the two entity hitboxes collide
{
    if (((b.get_pos_x() <= a.get_pos_x()) && (a.get_pos_x() <= b.get_pos_x() + b.get_hitbox_width() - 1)) ||    // if Entity A's x of left side of the hitbox is inside Entity B's hitbox x range
            ((b.get_pos_x() <= a.get_pos_x() + a.get_hitbox_width() - 1) && (a.get_pos_x() + a.get_hitbox_width() - 1 <= b.get_pos_x() + b.get_hitbox_width() - 1))) {  // if Entity A's x of right side of the hitbox is inside Entity B's hitbox x range
        if (((b.get_pos_y() <= a.get_pos_y()) && (a.get_pos_y() <= b.get_pos_y() + b.get_hitbox_height() - 1)) ||   // if Entity A's y of top side of the hitbox is inside Entity B's hitbox y range
                ((b.get_pos_y() <= a.get_pos_y() + a.get_hitbox_height() - 1) && (a.get_pos_y() + a.get_hitbox_height() - 1 <= b.get_pos_y() + b.get_hitbox_height() - 1))) {   // if Entity A's y of bottom side of the hitbox is inside Entity B's hitbox y range
            return true;
        }
    }
    return 0;
}

// returns -1 or 1 if the hitbox of "entity a" collides with any hitboxes of entities within "array" as "entity a" moves on the x direction
float RoomEngine::entity_move_check_x(Entity *a, Entity *array[], int no_of_enemies, int current_entity, bool valid_enemies[])
{
    for (int i = 0; i < no_of_enemies; i++) { // For every enemy = Entity B
        if ((valid_enemies[i]) && (i != current_entity)) {  // only check if entity b exists and entity a is not the same as entity b
            if (((array[i]->get_prev_pos_x() <= a->get_pos_x()) && (a->get_pos_x() <= array[i]->get_prev_pos_x() + array[i]->get_hitbox_width() - 1)) ||    // Same as entity_collision, except that Entity B's x position is its previous x position
                    ((array[i]->get_prev_pos_x() <= a->get_pos_x() + a->get_hitbox_width() - 1) && (a->get_pos_x() + a->get_hitbox_width() - 1 <= array[i]->get_prev_pos_x() + array[i]->get_hitbox_width() - 1))) {
                if (((array[i]->get_prev_pos_y() <= a->get_prev_pos_y()) && (a->get_prev_pos_y() <= array[i]->get_prev_pos_y() + array[i]->get_hitbox_height() - 1)) ||
                        ((array[i]->get_prev_pos_y() <= a->get_prev_pos_y() + a->get_hitbox_height() - 1) && (a->get_prev_pos_y() + a->get_hitbox_height() - 1 <= array[i]->get_prev_pos_y() + array[i]->get_hitbox_height() - 1))) {
                    return (2*((a->get_pos_x() > array[i]->get_prev_pos_x()) - 0.5));
                }
            }
        }
    }
    return 0;
}

// returns -1 or 1 if the hitbox of "entity a" collides with any hitboxes of entities within "array" as "entity a" moves on the y direction
float RoomEngine::entity_move_check_y(Entity *a, Entity *array[], int no_of_enemies, int current_entity, bool valid_enemies[])
{
    for (int i = 0; i < no_of_enemies; i++) { // For every enemy = Entity B
        if ((valid_enemies[i]) && (i != current_entity)) {  // only check if entity b exists and entity a is not the same as entity b
            if (((array[i]->get_prev_pos_x() <= a->get_prev_pos_x()) && (a->get_prev_pos_x() <= array[i]->get_prev_pos_x() + array[i]->get_hitbox_width() - 1)) ||  // Same as entity_collision, except that Entity B's y position is its previous y position
                    ((array[i]->get_prev_pos_x() <= a->get_prev_pos_x() + a->get_hitbox_width() - 1) && (a->get_prev_pos_x() + a->get_hitbox_width() - 1 <= array[i]->get_prev_pos_x() + array[i]->get_hitbox_width() - 1))) {
                if (((array[i]->get_prev_pos_y() <= a->get_pos_y()) && (a->get_pos_y() <= array[i]->get_prev_pos_y() + array[i]->get_hitbox_height() - 1)) ||
                        ((array[i]->get_prev_pos_y() <= a->get_pos_y() + a->get_hitbox_height() - 1) && (a->get_pos_y() + a->get_hitbox_height() - 1 <= array[i]->get_prev_pos_y() + array[i]->get_hitbox_height() - 1))) {
                    return (2*((a->get_pos_y() > array[i]->get_prev_pos_y()) - 0.5));
                }
            }
        }
    }
    return 0;
}

void RoomEngine::check_damage_player()
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (room->valid_enemies[i]) {   // Checking each valid enemy
            if(entity_collision(*player, *room->enemies[i])) {
                player->take_damage(room->enemies[i]->get_attack());
                break; // only let 1 enemy damage player at a time
            }
        }
        if (room->valid_collectibles[i]) {  // Checking each valid collectible (hearts, coins)
            if(entity_collision(*player, *room->collectibles[i])) {
                player->take_damage(room->collectibles[i]->get_attack());
                delete room->collectibles[i];
                room->valid_collectibles[i] = false;
                break; // only let 1 heart heal player at a time
            }
        }
    }
}

void RoomEngine::check_damage_enemies()
{
    for (int i = 0; i < bullets_max; i++) {
        if (player->valid_bullets[i]) {
            if (!(player->delete_out_of_bounds_bullets(room->get_current_map_2d(), room->get_doorways()))) { // Delete any bullet that goes out the screen or hits walls, if none, then
                for (int j = 0; j < MAX_ENEMIES; j++) {
                    if (room->valid_enemies[j] && (entity_collision(*player->bullets_array[i], *room->enemies[j]))) { // Delete bullets and damage enemy if player bullets collide with any enemy
                        room->enemies[j]->take_damage(player->get_attack());
                        delete player->bullets_array[i]; player->valid_bullets[i] = false;
                        break;
                    }
                }
            }
        }
    }
}

void RoomEngine::move_player()
{
    player->move(mapped_coord.x, mapped_coord.y, room->get_current_map_2d(), room->get_doorways());
}

void RoomEngine::move_enemies()
{
    // Actual Movement of Enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (room->valid_enemies[i]) {
            room->enemies[i]->update_prev_pos();
            room->enemies[i]->move(player->get_pos_x(), player->get_pos_y(), room->get_current_map_2d(), room->get_doorways());
        }
    }
    // Entity Collision Repulsion
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (room->valid_enemies[i]) {
            room->enemies[i]->position_add_x(entity_move_check_x(room->enemies[i], room->enemies, MAX_ENEMIES, i, room->valid_enemies));    // add 1 x position if collide
            room->enemies[i]->position_add_y(entity_move_check_y(room->enemies[i], room->enemies, MAX_ENEMIES, i, room->valid_enemies));    // add 1 y position if collide
        }
    }
}