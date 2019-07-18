#include "Bullets.h"

// Constructor
Bullets::Bullets(float pos_x, float pos_y, int dir)
{
    _face = dir;
    _hp = 1;
    
    _hitbox.width = 3;
    _hitbox.height = 3;
    
    _position.x = pos_x;
    _position.y = pos_y;
    
    _sprite_size.width = 3;
    _sprite_size.height = 3;
    _sprite_size.offset_x = -1;
    _sprite_size.offset_y = -4;
}

// Functions
void Bullets::move(float speed, float unused, char * unused2, bool * unused3)   //  Moves regarding face(constant after constructed)
{
    if (_face == 0) {
        _position.y -= speed;
    } else if (_face == 1) {
        _position.x += speed;
    } else if (_face == 2) {
        _position.y += speed;
    } else if (_face == 3) {
        _position.x -= speed;
    }
}

void Bullets::draw(N5110 &lcd)
{
    lcd.drawSpriteTransparent(_position.x+_sprite_size.offset_x,
                              _position.y+_sprite_size.offset_y,
                              _sprite_size.height,
                              _sprite_size.width,
                              (char *) bullets_sprite);
}

void Bullets::take_damage(int damage)   // Taking damage, currently not used(has to be inherited, as well as useful for possible future use)
{
    _hp -= damage;
}

bool Bullets::out_of_bounds_check(char * map, bool * doorways)  // Returns true when bullets exit map or collide with walls
{
    if (entity_to_map_collision_test(_position.x, _position.y, map, doorways)) {
        return true;
    }
    if ((0 > _position.x) || (_position.x > 84) || (0 > _position.y) || (_position.y > 48)) {
        return true;
    }
    return false;
}