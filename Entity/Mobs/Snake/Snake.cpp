#include "Snake.h"
#include "math.h"
#include <complex>

// Constructor
Snake::Snake(float pos_x, float pos_y)
{
    _hp = 4;
    _attack = 1;
    _face = 0;
    _prev_face = 0;
    _hp_drop_chance = 10; // out of 100
    
    _hitbox.width = 4;
    _hitbox.height = 7;
    
    _position.x = pos_x;
    _position.y = pos_y;
    
    _sprite_size.width = 6;
    _sprite_size.height = 12;
    _sprite_size.offset_x = -1;
    _sprite_size.offset_y = -6;
    
    _frame.count = 0;
    _frame.number = 0;
    _frame.max = 6;
    
    _velocity = 0;
    _velocity_index = 0;
}
// Member Function
void Snake::update_prev_face()
{
    _prev_face = _face;
}

// Member Mutator
void Snake::update_hitbox(int _hitbox_width, int _hitbox_height, int _sprite_size_width, int _sprite_size_height, int _sprite_size_offset_x, int _sprite_size_offset_y, int max_frame)     // Offset, Hitbox and Frame Count update
{
    if (_prev_face != _face) {
        _frame.number = 0;   // Resets animation everytime face changes
        _hitbox.width = _hitbox_width;
        _hitbox.height = _hitbox_height;
        
        _sprite_size.width = _sprite_size_width;
        _sprite_size.height = _sprite_size_height;
        _sprite_size.offset_x = _sprite_size_offset_x;
        _sprite_size.offset_y = _sprite_size_offset_y;
        
        _frame.max = max_frame;
    }
}

// Functions
void Snake::move(float player_x, float player_y, char * map, bool * doorways)
{
    float diff_x = player_x - _position.x;
    float diff_y = player_y - _position.y;
    _velocity = snake_velocity_pattern[_velocity_index]; // Creating slithering effect, changing velocity of movement
    update_prev_face();

    // Setting Face
    update_face(diff_x, diff_y);

    // Movement
    move_snake(); // Movement and updating _hitboxes

    undo_move_x(entity_to_map_collision_test(_position.x, _prev_pos.y, map, doorways));
    undo_move_y(entity_to_map_collision_test(_prev_pos.x, _position.y, map, doorways));

    increment_frame();
}

void Snake::update_face(float diff_x, float diff_y) // Depending on the displacement of player from snake, after a full slither effect, change the face
{
    if (_velocity_index == 0) {
        if (abs(diff_x) > abs(diff_y)) {
            if (diff_x > 0) {
                _face = 1;
            } else {
                _face = 3;
            }
        } else {
            if (diff_y > 0) {
                _face = 2;
            } else {
                _face = 0;
            }
        }
    }
}

void Snake::move_snake()    // Moves the Snake according to velocity, updates the _hitboxes everytime it changes face
{
    if (_face == 0) {
        _position.y -= _velocity;
        update_hitbox(4, 7, 6, 12, -1, -6, 6);
    } else if (_face == 1) {
        _position.x += _velocity;
        update_hitbox(7, 4, 12, 7, -6, -4, 4);
    } else if (_face == 2) {
        _position.y += _velocity;
        update_hitbox(4, 7, 6, 12, -1, -5, 6);
    } else if (_face == 3) {
        _position.x -= _velocity;
        update_hitbox(7, 4, 12, 7, 0, -4, 4);
    }
}

void Snake::increment_frame()   // Frame increment and velocity index increment
{
    _frame.count++;
    if (_frame.count >= 10) {    // Every 10 frames, sprite_frames increments and velocity_index increments
        _frame.count = 0;
        _velocity_index++;
        _frame.number++;
        if (_velocity_index >= 6) { // Velocity_index max; reset
            _velocity_index = 0;
        }
        if (_frame.number >= _frame.max) {    // Frame.number max; reset
            _frame.number = 0;
        }
    }
}

void Snake::take_damage(int damage)
{
    _hp -= damage;
}

char * Snake::get_frame()   // Returns the frame needed
{
    if(_face == 0) {
        return (char *) sprite_snake_y[0][_frame.number];
    } else if(_face == 1) {
        return (char *) sprite_snake_x[0][_frame.number];
    } else if(_face == 2) {
        return (char *) sprite_snake_y[1][_frame.number];
    } else if(_face == 3) {
        return (char *) sprite_snake_x[1][_frame.number];
    }
    return 0;
}

void Snake::draw(N5110 &lcd)
{
    lcd.drawSpriteTransparent(get_pos_x()+_sprite_size.offset_x,
                              get_pos_y()+_sprite_size.offset_y,
                              _sprite_size.height,
                              _sprite_size.width,
                              get_frame());
}