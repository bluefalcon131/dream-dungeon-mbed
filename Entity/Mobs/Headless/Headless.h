#ifndef HEADLESS_H
#define HEADLESS_H
#include "Entity.h"

/**Headless Class
@author Steven Mahasin
@brief Creates a Headless which inherits the Entity class, this is one of the mobs that spawns in the normal rooms.
@date May 2019
*/
class Headless : public Entity
{

public:
    /** Constructor 
    *   @brief creates a headless at positions pos_x and pos_y
    *   @param pos_x @details initialise _position.x
    *   @param pos_y @details initialise _position.y
    */
    Headless(float pos_x, float pos_y);

    // Functions
    /**
    *   @brief function moves the headless towards the player
    *   @param x_value @details player x-position
    *   @param y_value @details player y-position
    *   @param map @details the 2d map array that dictates where there are walls or empty space
    *   @param doorways @details an array that dictates which side of the wall has a doorway
    */
    virtual void move(float player_x, float player_y, char * map, bool * doorways);
    /**
    *   @brief reduce _hp by damage
    *   @param damage @details the amount of damage to be taken
    */
    virtual void take_damage(int damage);
    /**
    *   @brief a virtual function of drawing the headless onto the screen
    *   @param lcd @details the screen where the headless is drawn on
    */
    virtual void draw(N5110 &lcd);

private:
    // Methods
    /**
    *   @brief gets the sprite array
    *   @return char pointer array of the corresponding snake sprite frame
    */
    char * get_frame();
    /**
    *   @brief increase _frame.count which increases _frame.number to animate snake
    */
    void increment_frame();
};

const char sprite_headless[4][4][9][6] = {   // Player [Face][SpriteAnimationFrame][Size_Y][Size_X]
    {
        // Up
        {
            {0,0,0,0,0,0,},
            {1,0,0,0,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,}
        },
        {
            {0,0,0,0,0,0,},
            {0,0,0,1,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,},
            {0,0,0,0,1,0,}
        },
        {
            {0,0,0,0,1,0,},
            {0,0,1,0,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,}
        },
        {
            {0,1,0,0,0,0,},
            {0,0,0,0,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,0,0,}
        }
    },
    {
        // Right
        {
            {0,0,0,0,0,0,},
            {0,0,1,0,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,1,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,0,0,0,},
            {0,0,1,0,0,0,},
            {0,0,1,1,0,0,}
        },
        {
            {0,1,0,0,0,0,},
            {0,0,0,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,1,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,0,1,0,},
            {0,0,1,0,1,0,},
            {0,1,0,0,0,1,}
        },
        {
            {0,0,0,0,1,0,},
            {0,0,0,0,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,1,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,0,0,0,},
            {0,0,1,0,0,0,},
            {0,0,1,1,0,0,}
        },
        {
            {0,0,0,0,0,0,},
            {0,0,0,0,0,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,1,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,0,1,0,},
            {0,0,1,0,1,0,},
            {0,1,0,0,0,1,}
        }
    },
    {
        // Down
        {
            {0,0,0,0,0,0,},
            {1,0,0,0,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,}
        },
        {
            {0,0,0,0,0,0,},
            {0,0,0,1,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,},
            {0,0,0,0,1,0,}
        },
        {
            {0,0,0,0,1,0,},
            {0,0,1,0,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,}
        },
        {
            {0,1,0,0,0,0,},
            {0,0,0,0,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,0,0,}
        }
    },
    {
        // Left
        {
            {0,0,0,0,0,0,},
            {0,0,0,1,0,0,},
            {0,0,1,1,0,0,},
            {1,1,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,0,0,},
            {0,0,0,1,0,0,},
            {0,0,1,1,0,0,}
        },
        {
            {0,0,0,0,1,0,},
            {0,0,1,0,0,0,},
            {0,0,1,1,0,0,},
            {1,1,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,1,0,0,},
            {0,1,0,1,0,0,},
            {1,0,0,0,1,0,}
        },
        {
            {0,1,0,0,0,0,},
            {0,0,0,0,0,0,},
            {0,0,1,1,0,0,},
            {1,1,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,0,0,},
            {0,0,0,1,0,0,},
            {0,0,1,1,0,0,}
        },
        {
            {0,0,0,0,0,0,},
            {1,0,0,0,0,0,},
            {0,0,1,1,0,0,},
            {1,1,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,1,0,0,},
            {0,1,0,1,0,0,},
            {1,0,0,0,1,0,}
        }
    }
};

#endif