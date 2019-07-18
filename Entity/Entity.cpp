#include "Entity.h"

// Functions
void Entity::undo_move_x(bool condition)
{
    if (condition) {
        _position.x = _prev_pos.x;
    }
}
void Entity::undo_move_y(bool condition)
{
    if (condition) {
        _position.y = _prev_pos.y;
    }
}
void Entity::update_prev_pos()
{
    _prev_pos = _position;
}

bool Entity::entity_to_map_collision_test(float pos_x, float pos_y, char * two_d_map, bool * doorways)    // Returns true if the entity clashes a wall
{      
    for (int j = pos_y; j < (int)pos_y + _hitbox.height; j++) {
        for(int i = pos_x; i < (int)pos_x + _hitbox.width; i++) {
            if ((j>=screen_height) || (i>=screen_width) || (j<0) || (i<0)) {} // To allow movement towards outside of the map
            else if (*((two_d_map+j*screen_width)+i) == 1) {  // if entity clashes the 2d map
                return true;
            }
            
            // Checking if the player walks into a wall if no doorway on that side exists
            else if ( !(*(doorways)) && (pos_y <= 10) ) {
                return true;
            }
            else if ( !(*(doorways+1)) && (pos_x + _hitbox.width - 1 >= 81) ) {
                return true;
            }
            else if ( !(*(doorways+2)) && (pos_y + _hitbox.height - 1 >= 45) ) {
                return true;
            }
            else if ( !(*(doorways+3)) && (pos_x <= 3) ) {
                return true;
            }
        }
    }
    return false;
}

// Mutators

void Entity::set_position(float x, float y)
{
    _position.x = x;
    _position.y = y;
}

void Entity::position_add_x(float change_x)
{
    _position.x += change_x;
}
void Entity::position_add_y(float change_y)
{
    _position.y += change_y;
}

// Accessors
int Entity::get_hp_drop_chance()
{
    return _hp_drop_chance;
}
int Entity::get_hitbox_width()
{
    return _hitbox.width;
}
int Entity::get_hitbox_height()
{
    return _hitbox.height;
}
int Entity::get_face()
{
    return _face;
}
int Entity::get_sprite_width()
{
    return _sprite_size.width;
}
int Entity::get_sprite_height()
{
    return _sprite_size.height;
}
int Entity::get_offset_x()
{
    return _sprite_size.offset_x;
}
int Entity::get_offset_y()
{
    return _sprite_size.offset_y;
}
int Entity::get_pos_x()
{
    return _position.x;
}
int Entity::get_pos_y()
{
    return _position.y;
}
int Entity::get_prev_pos_x()
{
    return _prev_pos.x;
}
int Entity::get_prev_pos_y()
{
    return _prev_pos.y;
}
int Entity::get_attack()
{
    return _attack;
}
int Entity::get_hp()
{
    return _hp;
}
float Entity::get_velocity()
{
    return _velocity;
}