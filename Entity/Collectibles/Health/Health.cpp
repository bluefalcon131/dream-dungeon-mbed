#include "Health.h"

Health::Health(float pos_x, float pos_y)
{
    _hp = 1;
    _attack = -1;
    
    _hitbox.width = 7;
    _hitbox.height = 7;
    
    _position.x = pos_x;
    _position.y = pos_y;
    
    _sprite_size.width = 7;
    _sprite_size.height = 7;
    _sprite_size.offset_x = 0;
    _sprite_size.offset_y = 0;
}

void Health::move(float unused, float unused1, char * unused2, bool * unused3)  // Health doesnt move, only typed out since the virtual function is pure
{
    
}

void Health::draw(N5110 &lcd)
{
    lcd.drawSpriteTransparent(_position.x+_sprite_size.offset_x,
                              _position.y+_sprite_size.offset_y,
                              _sprite_size.height,
                              _sprite_size.width,
                              (char *) health_sprite);
}

void Health::take_damage(int damage)
{
    _hp -= damage;
}