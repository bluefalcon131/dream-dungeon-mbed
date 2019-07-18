#include "Walls.h"
Walls::Walls(int pos_x, int pos_y, int hitbox_width, int hitbox_height)
{   
    _hitbox.width = hitbox_width;
    _hitbox.height = hitbox_height;
    
    _sprite_size.width = hitbox_width;
    _sprite_size.height = hitbox_height + 7;
    _sprite_size.offset_x = 0;
    _sprite_size.offset_y = -7;
    
    _position.x = pos_x;
    _position.y = pos_y;
    update_prev_pos();
}

void Walls::move(float unused, float unused1, char * unused2, bool * unused3) // movement control and miscellaneous updates
{
    
}

void Walls::take_damage(int damage)
{
    
}

void Walls::draw(N5110 &lcd)
{
    lcd.drawRect(_position.x, _position.y + _sprite_size.offset_y, _sprite_size.width, _sprite_size.height, FILL_BLACK);
    lcd.drawRect(_position.x+1, _position.y + _sprite_size.offset_y+1, _sprite_size.width-2, _sprite_size.height-2, FILL_WHITE);
    lcd.drawLine(_position.x, _position.y + _sprite_size.offset_y + _hitbox.height - 1, _position.x + _hitbox.width - 1, _position.y + _sprite_size.offset_y + _hitbox.height - 1, 1);
}