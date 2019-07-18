#ifndef SNAKE_H
#define SNAKE_H
#include "Entity.h"

/**Snake Class
@author Steven Mahasin
@brief Creates a Snake which inherits the Entity class, this is one of the mobs that spawns in the normal rooms.
@date May 2019
*/
class Snake : public Entity
{

public:
    /** Constructor 
    *   @brief creates a snake at positions pos_x and pos_y
    *   @param pos_x @details initialise _position.x
    *   @param pos_y @details initialise _position.y
    */
    Snake(float pos_x, float pos_y);

    // Functions
    /**
    *   @brief calls the movement functions to move the snake in the desired way
    *   @param x_value @details player's x-position
    *   @param y_value @details player's y-position
    *   @param map @details the 2d map array that dictates where there are walls or empty space
    *   @param doorways @details an array that dictates which side of the wall has a doorway
    */
    virtual void move(float x_value, float y_value, char * map, bool * doorways);
    /**
    *   @brief reduce hp by damage
    *   @param damage @details the amount of damage to be taken
    */
    virtual void take_damage(int damage);
    /**
    *   @brief a virtual function of drawing the snake onto the screen
    *   @param lcd @details the screen where the snake is drawn on
    */
    virtual void draw(N5110 &lcd);

private:
    // Member Function
    /**
    *   @brief updates _prev_face into _face
    */
    void update_prev_face();
    /**
    *   @brief gets the sprite array
    *   @return char pointer array of the corresponding snake sprite frame
    */
    char * get_frame();
    /**
    *   @brief changes the face everytime the snake finish slithering, towards the player
    *   @param diff_x @details the difference between the player x-position and the snake x-position
    *   @param diff_y @details the difference between the player y-position and the snake y-position
    */
    void update_face(float diff_x, float diff_y);
    /**
    *   @brief function moves the snake in a slither effect
    */
    void move_snake();
    /**
    *   @brief increase _frame.count which increases _frame.number to animate snake
    */
    void increment_frame();

    // Member Mutator
    /**
    *   @brief updates the hitbox status and sprite status of the snake since different face has unique hitbox and sprite status
    *   @param _hitbox_width @details the width of the hitbox
    *   @param _hitbox_height @details the height of the hitbox
    *   @param _sprite_size_width @details the width of the sprite
    *   @param _sprite_size_height @details the height of the sprite
    *   @param _sprite_size_offset_x @details the x-offset of the sprite to the hitbox
    *   @param _sprite_size_offset_y @details the y-offset of the sprite to the hitbox
    *   @param max_frame @details the maximum number of frames for animation
    */
    void update_hitbox(int _hitbox_width, int _hitbox_height, int _sprite_size_width, int _sprite_size_height, int _sprite_size_offset_x, int _sprite_size_offset_y, int max_frame);

    // Member Variable
    /**
    *   @brief an index to choose which velocity the snake currently has, this is to add the slither effect
    */
    int _velocity_index;
    /**
    *   @brief the previous face of the snake, to detect change in snake's face
    */
    int _prev_face;

};

const float snake_velocity_pattern[6] = {0, 0.15, 0.25, 0.5, 0.1, -0.1};

const char sprite_snake_x[2][4][7][12] = {   // Player [Face][SpriteAnimationFrame][Size_Y][Size_X]
    {
        // Right
        {
            {0,0,0,0,0,0,0,0,1,1,1,0,},
            {0,0,0,0,0,0,0,1,1,1,2,1,},
            {0,0,0,0,0,0,0,1,1,1,1,1,},
            {0,0,0,0,0,0,0,1,1,1,0,0,},
            {0,0,0,0,0,0,0,0,1,1,1,0,},
            {0,0,1,1,1,1,0,1,1,1,1,0,},
            {1,1,1,0,1,1,1,1,1,1,0,0,},
        },
        {
            {0,0,0,0,0,0,0,0,1,1,1,0,},
            {0,0,0,0,0,0,0,1,1,1,2,1,},
            {0,0,0,0,0,0,0,1,1,1,1,1,},
            {0,0,0,0,0,0,0,1,1,1,0,0,},
            {0,0,0,0,0,0,0,0,1,1,1,0,},
            {0,1,1,1,1,0,1,1,1,1,1,0,},
            {1,0,0,1,1,1,1,1,1,1,0,0,},
        },
        {
            {0,0,0,0,0,0,0,0,1,1,1,0,},
            {0,0,0,0,0,0,0,1,1,1,2,1,},
            {0,0,0,0,0,0,0,1,1,1,1,1,},
            {0,0,0,0,0,0,0,1,1,1,0,0,},
            {1,0,0,0,0,0,0,0,1,1,1,0,},
            {0,1,0,0,1,1,1,1,1,1,1,0,},
            {0,0,1,1,1,0,1,1,1,1,0,0,},
        },
        {
            {0,0,0,0,0,0,0,0,1,1,1,0,},
            {0,0,0,0,0,0,0,1,1,1,2,1,},
            {0,0,0,0,0,0,0,1,1,1,1,1,},
            {0,0,0,0,0,0,0,1,1,1,0,0,},
            {0,0,0,0,0,0,0,0,1,1,1,0,},
            {1,1,0,1,1,1,1,1,1,1,1,0,},
            {0,0,1,1,0,1,1,1,1,1,0,0,},
        }
    },
    {
        // Left
        {
            {0,1,1,1,0,0,0,0,0,0,0,0,},
            {1,2,1,1,1,0,0,0,0,0,0,0,},
            {1,1,1,1,1,0,0,0,0,0,0,0,},
            {0,0,1,1,1,0,0,0,0,0,0,0,},
            {0,1,1,1,0,0,0,0,0,0,0,0,},
            {0,1,1,1,1,0,1,1,1,1,0,0,},
            {0,0,1,1,1,1,1,1,0,1,1,1,},
        },
        {
            {0,1,1,1,0,0,0,0,0,0,0,0,},
            {1,2,1,1,1,0,0,0,0,0,0,0,},
            {1,1,1,1,1,0,0,0,0,0,0,0,},
            {0,0,1,1,1,0,0,0,0,0,0,0,},
            {0,1,1,1,0,0,0,0,0,0,0,0,},
            {0,1,1,1,1,1,0,1,1,1,1,0,},
            {0,0,1,1,1,1,1,1,1,0,0,1,},
        },
        {
            {0,1,1,1,0,0,0,0,0,0,0,0,},
            {1,2,1,1,1,0,0,0,0,0,0,0,},
            {1,1,1,1,1,0,0,0,0,0,0,0,},
            {0,0,1,1,1,0,0,0,0,0,0,0,},
            {0,1,1,1,0,0,0,0,0,0,0,1,},
            {0,1,1,1,1,1,1,1,0,0,1,0,},
            {0,0,1,1,1,1,0,1,1,1,0,0,},
        },
        {
            {0,1,1,1,0,0,0,0,0,0,0,0,},
            {1,2,1,1,1,0,0,0,0,0,0,0,},
            {1,1,1,1,1,0,0,0,0,0,0,0,},
            {0,0,1,1,1,0,0,0,0,0,0,0,},
            {0,1,1,1,0,0,0,0,0,0,0,0,},
            {0,1,1,1,1,1,1,1,1,0,1,1,},
            {0,0,1,1,1,1,1,0,1,1,0,0,},
        }
    }
};

const char sprite_snake_y[2][6][12][6] = {   // Player [Face][SpriteAnimationFrame][Size_Y][Size_X]
    {
        // Up
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,1,0,0,},
            {0,1,1,0,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,1,0,},
            {0,0,0,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,0,0,0,0,},
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,1,0,0,0,},
            {0,1,1,0,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,1,0,},
            {0,0,0,0,1,0,},
            {0,0,1,1,0,0,},
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,0,0,0,},
            {0,1,1,0,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,0,1,0,},
            {0,0,0,1,0,0,},
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,1,0,},
            {0,0,0,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,0,0,0,},
            {0,1,1,0,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,0,1,0,},
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,1,0,},
            {0,0,0,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,0,0,0,},
            {0,1,0,0,0,0,},
            {0,0,1,1,0,0,},
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,0,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,1,0,},
            {0,0,0,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,0,0,0,0,},
            {0,0,1,0,0,0,},
        }
    },
    {
        // Down
        {
            {0,0,0,0,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,0,0,0,},
            {0,1,1,0,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,1,0,},
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,2,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
        },
        {
            {0,0,1,1,0,0,},
            {0,1,0,0,0,0,},
            {0,1,1,0,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,1,0,},
            {0,0,0,1,1,0,},
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,2,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
        },
        {
            {0,0,1,0,0,0,},
            {0,1,0,0,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,1,0,},
            {0,0,0,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,2,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
        },
        {
            {0,1,0,0,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,1,0,},
            {0,0,0,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,0,0,0,},
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,2,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
        },
        {
            {0,0,1,1,0,0,},
            {0,0,0,0,1,0,},
            {0,0,0,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,0,0,0,},
            {0,1,1,0,0,0,},
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,2,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
        },
        {
            {0,0,0,1,0,0,},
            {0,0,0,0,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,0,0,0,},
            {0,1,1,0,0,0,},
            {0,0,1,1,0,0,},
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,2,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
        }
    }
};

#endif