#ifndef HEALTH_H
#define HEALTH_H
#include "Entity.h"

/**Health Class
@author Steven Mahasin
@brief Creates a Health which inherits the Entity class, this is a collectible entity that the player interracts with to gain health points.
@date May 2019
*/
class Health : public Entity
{
public:
    /** Constructor 
    *   @brief creates a heart that heals when picked up
    *   @param pos_x @details initialise _position.x
    *   @param pos_y @details initialise _position.y
    */
    Health(float pos_x, float pos_y);

    // Functions
    /**
    *   @brief just because entity has a pure virtual function move, the function is of no use in health as it does not move
    *   @param unused @details not used
    *   @param unused1 @details not used
    *   @param unused2 @details not used
    *   @param unused3 @details not used
    */
    virtual void move(float unused, float unused1, char *unused2, bool *unused3);
    /**
    *   @brief reduce _hp by damage
    *   @param damage @details the amount of damage to be taken
    */
    virtual void take_damage(int damage);
    /**
    *   @brief a virtual function of drawing the health onto the screen
    *   @param lcd @details the screen where the health is drawn on
    */
    virtual void draw(N5110 &lcd);
};

const char health_sprite[7][7] = {
    {0,1,1,0,1,1,0},
    {1,1,1,1,1,1,1},
    {1,0,1,1,1,1,1},
    {1,0,1,1,1,1,1},
    {0,1,0,1,1,1,0},
    {0,0,1,1,1,0,0},
    {0,0,0,1,0,0,0}
};

#endif