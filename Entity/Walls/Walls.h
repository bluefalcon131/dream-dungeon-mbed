#ifndef WALLS_H
#define WALLS_H
#include "Entity.h"
/**Walls Class
@author Steven Mahasin
@brief Creates a Static Wall which inherits the Entity class, not used yet in this version due to bugged spawn areas
@date May 2019
*/
class Walls : public Entity
{
public:
    /** Constructor 
    *   @brief creates a wall at positions pos_x and pos_y
    *   @param pos_x @details initialise _position.x
    *   @param pos_y @details initialise _position.y
    *   @param hitbox_width @details initialise _hitbox.width
    *   @param hitbox_height @details initialise _hitbox.height
    */
    Walls(int pos_x, int pos_y, int hitbox_width, int hitbox_height);
    
    // Functions
    /**
    *   @brief just because entity has a pure virtual function move, the function is of no use in walls as it does not move
    *   @param unused @details not used
    *   @param unused1 @details not used
    *   @param unused2 @details not used
    *   @param unused3 @details not used
    */
    virtual void move(float unused, float unused1, char * unused2, bool * unused3); // movement control and miscellaneous updates
    /**
    *   @brief just because entity has a pure virtual function take_damage, the function is of no use in walls as it does take_damage
    *   @param unused @details not used
    */
    virtual void take_damage(int unused);
    /**
    *   @brief a virtual function of drawing the walls onto the screen
    *   @param lcd @details the screen where the wall is drawn on
    */
    virtual void draw(N5110 &lcd);
};

#endif