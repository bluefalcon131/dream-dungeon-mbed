#include "Skull.h"
#include <complex>
Skull::Skull(float pos_x, float pos_y)
{
    _hp = 20;
    _attack = 1;
    
    _dash = false;
    _dash_counter = 0;
    
    _hitbox.width = 19;
    _hitbox.height = 9;
    
    _sprite_size.width = 21;
    _sprite_size.height = 23;
    _sprite_size.offset_x = -1;
    _sprite_size.offset_y = -14;
    
    _shadow.width = 19;
    _shadow.height = 5;
    _shadow.offset_x = 0;
    _shadow.offset_y = 5;
    
    _position.x = pos_x;
    _position.y = pos_y;
    update_prev_pos();
    
    _frame.count = 0;
    _frame.number = 0;
    _frame.max = 2;
    _face = 2;
    
    _velocity = 0.2;
    _hp_drop_chance = 0;
}

void Skull::move(float player_x, float player_y, char * map, bool * doorways)
{
    if (_dash_counter < DASH_DELAY) { // Approaching Movement
        approaching_movement(player_x, player_y);
    } else if (_dash_counter < DASH_DELAY + 28){ // Dashing movement; const 28 = 4(velocity_index_increment_delay) * 7 (length of the velocity_pattern)
        dash_movement();
    } else {
        _dash_counter = 0;
        _velocity = 0.2;
    }
    undo_move_x(entity_to_map_collision_test(_position.x, _prev_pos.y, map, doorways));
    undo_move_y(entity_to_map_collision_test(_prev_pos.x, _position.y, map, doorways));
    
    _dash_counter++;
    increment_frames();
}

void Skull::approaching_movement(float player_x, float player_y)
{
    _dash = false;
    std::complex<double> pos_diff(player_x - _position.x, player_y - _position.y);     // defining difference in position as a vector for simplicity, similar to Headless
    _position.x += _velocity * pos_diff.real() / std::abs(pos_diff);
    _position.y += _velocity * pos_diff.imag() / std::abs(pos_diff);
    // Setting Face
    if (abs(pos_diff.real()) > abs(pos_diff.imag())) {
        if (pos_diff.real() > 0) {
            _face = 1;
        } else {
            _face = 3;
        }
    } else {
        if (pos_diff.imag() > 0) {
            _face = 2;
        } else {
            _face = 0;
        }
    }
}

void Skull::dash_movement() // Changes velocity over time using the velocity pattern
{
    _dash = true;
    _velocity = skull_velocity_pattern[(int)((_dash_counter - DASH_DELAY)/4)];
    if (_face == 0){
        _position.y -= _velocity;
    } else if (_face == 1){
        _position.x += _velocity;
    } else if (_face == 2){
        _position.y += _velocity;
    } else if (_face == 3){
        _position.x -= _velocity;
    }
}

void Skull::draw(N5110 &lcd)
{
    update_offsets();
    lcd.drawSpriteTransparent(_position.x+_shadow.offset_x,
                              _position.y+_shadow.offset_y,
                              _shadow.height,
                              _shadow.width,
                              (char *)skull_shadow_sprite[_frame.number]);
    lcd.drawSpriteTransparent(_position.x+_sprite_size.offset_x,
                              _position.y+_sprite_size.offset_y,
                              _sprite_size.height,
                              _sprite_size.width,
                              (char *)skull_sprite[_face][_dash]);
}

void Skull::take_damage(int damage)
{
    _hp -= 1;
}

// Methods

void Skull::increment_frames()
{
    if (_frame.number < _frame.max) {
        _frame.count++;
    } else {
        _frame.count = 0;
    }
    _frame.number = (_frame.count/20) % _frame.max;
}

void Skull::update_offsets()    // Animates the shadows by offsetting the skull from the shadow periodically
{
    if (_frame.number == 0) {
        _sprite_size.offset_y = -14;
    } else if (_frame.number == 1) {
        _sprite_size.offset_y = -15;
    }
}