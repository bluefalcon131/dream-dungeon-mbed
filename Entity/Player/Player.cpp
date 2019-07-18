#include "Player.h"
#include "math.h"

// Constructor
Player::Player(float pos_x, float pos_y)
{
    _hp = 3;
    _attack = 1;
    _face = 2;
    
    _hitbox.width = 6;
    _hitbox.height = 5;
    
    _position.x = pos_x;
    _position.y = pos_y;
    
    _sprite_size.width = 6;
    _sprite_size.height = 12;
    _sprite_size.offset_x = 0;
    _sprite_size.offset_y = -7;
    
    _frame.count = 0;
    _frame.number = 0;
    _frame.max = 4;
    
    for (int i = 0; i < bullets_max; i++) {
        valid_bullets[i] = false;
    }
    
    _invulnerability_counter = INVULNERABILITY_PERIOD;

    // Upgradable status
    _fire_rate_delay = 30;
    _fire_rate_counter = _fire_rate_delay;
    _velocity = 0.7;
    _bullet_speed = 1;
}

Player::~Player()
{
    delete_bullets();
}

// Accessors
int Player::get_bullet_speed()
{
    return _bullet_speed;
}
int Player::get_hearts_width()
{
    return 9;
}
int Player::get_hearts_height()
{
    return 9;
}
char * Player::get_hearts_sprite()
{
    return (char *) sprite_heart;
}

// Functions
void Player::move(float mapped_x, float mapped_y, char * map, bool * doorways)  // Update all bullet movement and player movement, also takes care of animation
{
    move_player(mapped_x, mapped_y, map, doorways);
    move_bullets();
    increment_frames(mapped_x, mapped_y);   // Sets the face of the person, and increment frame count
    _invulnerability_counter++;  // for damage checking
}

void Player::move_player(float mapped_x, float mapped_y, char * map, bool * doorways)   // Moves the player unless if the player walks onto a wall
{
    update_prev_pos();
    _position.y -= _velocity*mapped_y;
    _position.x += _velocity*mapped_x;
    
    undo_move_x(entity_to_map_collision_test(_position.x, _prev_pos.y, map, doorways));
    undo_move_y(entity_to_map_collision_test(_prev_pos.x, _position.y, map, doorways));
}

void Player::move_bullets() // For each bullet, move them
{
    for (int i = 0; i < bullets_max; i++) {
        if (valid_bullets[i]) {
            bullets_array[i]->move(get_bullet_speed(), 0, 0, (bool *) 0);
        }
    }
}

void Player::increment_frames(float mapped_x, float mapped_y)
{
    if (abs(mapped_x) + abs(mapped_y) > 0.1f) { // If player is moving
        if (mapped_y < 0 && abs(mapped_y) > abs(mapped_x)) {
            _face = 2;
        } else if (mapped_y > 0 && abs(mapped_y) > abs(mapped_x)) {
            _face = 0;
        } else if (mapped_x > 0 && abs(mapped_x) > abs(mapped_y)) {
            _face = 1;
        } else if (mapped_x < 0 && abs(mapped_x) > abs(mapped_y)) {
            _face = 3;
        }
        if (_frame.number < _frame.max) { // Animate frames by incrementing and reseting frames
            _frame.count++;
        } else {
            _frame.count = 0;
        }
    } else {
        _frame.count = 0;    // If the player is not moving, don't animate
    }
    _frame.number = (_frame.count/8) % _frame.max; // Frame number is used in chosing sprite-frame for animation; the constant 8 is the number of frames per sprite-frame
}

void Player::take_damage(int damage)    // Takes damage unless if player just got damaged within invulnerability period
{
    if (damage < 0){
        _hp -= damage;
    }
    else if (_invulnerability_counter >= INVULNERABILITY_PERIOD) {
        _hp -= damage;
        _invulnerability_counter = 0;
    }
    if (_hp > 5) {   // Max HP is a constant 5, this might be an upgradable status later
        _hp = 5;
    }
}

bool Player::delete_out_of_bounds_bullets(char * map, bool * doorways)  // Attempts to delete bullets that are out of bounds or colliding with the wall, returns true if any bullets are deleted
{
    bool result = false;
    for (int i = 0; i < bullets_max; i++) {
        if((valid_bullets[i]) && (bullets_array[i]->out_of_bounds_check(map, doorways))) {
            valid_bullets[i] = false;
            delete bullets_array[i];
            result = true;
        }
    }
    return result;
}

void Player::draw(N5110 &lcd)
{
    draw_player(lcd);
}

void Player::draw_player(N5110 &lcd)
{
    lcd.drawSpriteTransparent(_position.x+_sprite_size.offset_x,
                              _position.y+_sprite_size.offset_y,
                              _sprite_size.height,
                              _sprite_size.width,
                              get_frame());
}

void Player::draw_bullets(N5110 &lcd, int j)
{
    for (int i = 0; i < bullets_max; i++) {
        if ((valid_bullets[i]) && (bullets_array[i]->get_pos_y() == j)) {
            bullets_array[i]->draw(lcd);
        }
    }
}

void Player::delete_bullets()   // Delete all bullets, normally used in unloading
{
    for (int i = 0; i < bullets_max; i++) {
        if (valid_bullets[i]) {
            delete bullets_array[i];
            valid_bullets[i] = false;
        }
    }
}

char * Player::get_frame()  // Returns the current frame's sprite pointer
{
    if ((_invulnerability_counter < INVULNERABILITY_PERIOD) && (_invulnerability_counter % 10 <= 4)) {
        return (char*) sprite_transparent_player;
    }
    return (char *) sprite_player[_face][_frame.number];
}

void Player::buttons(bool button_A, bool button_B, bool button_Y, bool button_X)    // Summons new bullets and overloads the player face when buttons are pressed
{
    _fire_rate_counter++;
    if (button_Y) {
        _face = 0;
    } else if (button_B) {
        _face = 1;
    } else if (button_A) {
        _face = 2;
    } else if (button_X) {
        _face = 3;
    }
    if (button_Y || button_B || button_A || button_X) {
        for (int i = 0; i < bullets_max; i++) {
            if (!valid_bullets[i] && (_fire_rate_counter >= _fire_rate_delay)) {  // waits until _fire_rate_delay is done before creating a bullet in an invalid slot of bullet_array
                bullets_array[i] = new Bullets(_position.x+2, _position.y+2, _face);
                valid_bullets[i] = true;
                _fire_rate_counter = 0;
                break;
            }
        }
    }
}
