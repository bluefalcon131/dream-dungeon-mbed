#include "Headless.h"
#include "math.h"
#include <complex>

Headless::Headless(float pos_x, float pos_y)
{
    _hp = 4;
    _attack = 1;
    _face = 0;
    _hp_drop_chance = 10; // out of 100
    
    _hitbox.width = 6;
    _hitbox.height = 5;
    
    _position.x = pos_x;
    _position.y = pos_y;
    
    _sprite_size.width = 6;
    _sprite_size.height = 9;
    _sprite_size.offset_x = 0;
    _sprite_size.offset_y = -4;
    
    _frame.count = 0;
    _frame.number = 0;
    _frame.max = 4;
    
    _velocity = 0.25;
}

void Headless::move(float player_x, float player_y, char * map, bool * doorways)
{
    std::complex<double> pos_diff(player_x - _position.x, player_y - _position.y); // Defining difference in position as a vector for simplicity (magnitude is hard to calculate)
    _position.x += _velocity * pos_diff.real() / std::abs(pos_diff);
    _position.y += _velocity * pos_diff.imag() / std::abs(pos_diff);
    // Setting face
    if (abs(pos_diff.real()) > abs(pos_diff.imag())) {
        if (pos_diff.real() > 0) { _face = 1;
        } else { _face = 3; 
        }
    } else {
        if (pos_diff.imag() > 0) { _face = 2;
        } else { _face = 0;
        }
    }
    // Wall Collision
    undo_move_x(entity_to_map_collision_test(_position.x, _prev_pos.y, map, doorways));
    undo_move_y(entity_to_map_collision_test(_prev_pos.x, _position.y, map, doorways));
    // Animation
    increment_frame();
}

void Headless::increment_frame()
{
    if (_frame.number < _frame.max) {
        _frame.count++;
    } else {
        _frame.count = 0;
    }
    _frame.number = (_frame.count/16) % _frame.max; // Frame number is used in chosing sprite-frame for animation; the constant 16 is the number of frames per sprite-frame
}

void Headless::draw(N5110 &lcd)
{
    lcd.drawSpriteTransparent(_position.x+_sprite_size.offset_x,
                              _position.y+_sprite_size.offset_y,
                              _sprite_size.height,
                              _sprite_size.width,
                              get_frame());
}

void Headless::take_damage(int damage)
{
    _hp -= damage;
}

char * Headless::get_frame()    // Returns the corresponding frame
{
    return (char *) sprite_headless[_face][_frame.number];
}