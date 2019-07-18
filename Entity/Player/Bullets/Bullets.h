#ifndef BULLETS_H
#define BULLETS_H
#include "Entity.h"

/**Bullets Class
@author Steven Mahasin
@brief Creates a Bullet which inherits the Entity class, this will be a created projectile by the player class
@date May 2019
*/
class Bullets : public Entity
{

public:
    /** Constructor 
    *   @brief creates a bullet at positions pos_x and pos_y travelling at face dir
    *   @param pos_x @details initialise _position.x
    *   @param pos_y @details initialise _position.y
    *   @param dir @details initialise _face
    */
    Bullets(float pos_x, float pos_y, int dir);

    // Functions
    /**
    *   @brief function moves the bullet on it's face at a speed
    *   @param speed @details the speed of the bullet
    *   @param unused @details not used
    *   @param map @details not used
    *   @param doorways @details not used
    */
    virtual void move(float speed, float unused, char * map, bool * doorways);
    /**
    *   @brief draws the bullet onto the screen
    *   @param lcd @details the screen where the bullet is drawn
    */
    virtual void draw(N5110 &lcd);
    /**
    *   @brief reduce _hp by damage
    *   @param damage @details the amount of damage to be taken
    */
    virtual void take_damage(int damage);
    /**
    *   @brief checks if the bullet is out of bounds (hit wall or out of screen)
    *   @param map @details the 2d map array that dictates where there are walls or empty space
    *   @param doorways @details an array that dictates which side of the wall has a doorway
    *   @returns true if bullet is out of bounds
    */
    bool out_of_bounds_check(char * map, bool * doorways);
};

const char bullets_sprite[3][3] = {{1,1,1},
    {1,1,1},
    {1,1,1}
};

#endif