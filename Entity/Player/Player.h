#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Bullets.h"
#define INVULNERABILITY_PERIOD 50

const int bullets_max = 20;
/**Player Class
@author Steven Mahasin
@brief Creates a Player which inherits the Entity class, contains functions that accepts all user interractions (buttons, joystick, etc)
@date May 2019
*/
class Player : public Entity
{
private:

    // Member Variables
    /**
    *   @brief a counter that increments to give a delay to the fire rate of player
    */
    int _fire_rate_counter;
    /**
    *   @brief a delay between each shot
    */
    int _fire_rate_delay;
    /**
    *   @brief the speed of the bullets created by this player
    */
    int _bullet_speed;
    /**
    *   @brief a counter that increments, allowing player to be invulnerable to a certain period defined
    */
    int _invulnerability_counter;
    
    // Private Functions
    /**
    *   @brief movement of the player
    *   @param mapped_x @details joystick x
    *   @param mapped_y @details joystick y
    *   @param map @details the 2d map array that dictates where there are walls or empty space
    *   @param doorways @details an array that dictates which side of the wall has a doorway
    */
    void move_player(float mapped_x, float mapped_y, char * map, bool * doorways);
    /**
    *   @brief movement of the bullets shot by this player
    */
    void move_bullets();
    /**
    *   @brief to increment the _frame protected variable, for animation of player
    *   @param mapped_x @details joystick x
    *   @param mapped_y @details joystick y
    */
    void increment_frames(float mapped_x, float mapped_y);
    /**
    *   @brief getting the needed frame of animation of player
    *   @return char pointer array to the corresponding player frame
    */
    char * get_frame();
    /**
    *   @brief draws the player onto the screen
    *   @param lcd @details the screen the player is drawn onto
    */
    void draw_player(N5110 &lcd);
    
public:
    /** Constructor 
    *   @brief creates a player at positions pos_x and pos_y
    *   @param pos_x @details initialise _position.x
    *   @param pos_y @details initialise _position.y
    */
    Player(float pos_x, float pos_y);
    /** Deconstructors */
    ~Player();

    // Accessors
    /**
    *   @brief getting the player's bullet speed
    *   @return _bullet_speed
    */
    int get_bullet_speed();
    /**
    *   @brief getting the heart sprite's width
    *   @return  width of the heart sprite
    */
    int get_hearts_width();
    /**
    *   @brief getting the heart sprite's height
    *   @return  height of the heart sprite
    */
    int get_hearts_height();
    /**
    *   @brief getting the heart sprite char array
    *   @return char pointer array to the heart sprite
    */
    char * get_hearts_sprite();
    
    // Functions
    /**
    *   @brief function calls both movement of player and movement of bullets
    *   @param x_value @details joystick x
    *   @param y_value @details joystick y
    *   @param map @details the 2d map array that dictates where there are walls or empty space
    *   @param doorways @details an array that dictates which side of the wall has a doorway
    */
    virtual void move(float x_value, float y_value, char * map, bool * doorways);
    /**
    *   @brief reduce _hp by damage
    *   @param damage @details the amount of damage to be taken
    */
    virtual void take_damage(int damage);
    /**
    *   @brief a virtual function of drawing the player onto the screen
    *   @param lcd @details the screen where the player is drawn on
    */
    virtual void draw(N5110 &lcd);
    /**
    *   @brief a virtual function of drawing the bullets the player shot onto the screen if j is the correct y-position of the bullets
    *   @param lcd @details the screen where the bullets is drawn on
    *   @param j @details which y-position hitboxes are currently being printed
    */
    void draw_bullets(N5110 &lcd, int j);
    /**
    *   @brief attempts to delete any bullets that goes out of bounds (out of screen or onto a wall)
    *   @param map @details the 2d map array that dictates where there are walls or empty space
    *   @param doorawys @details an array that dictates which side of the wall has a doorway
    *   @return true if any bullets is successfully deleted
    */
    bool delete_out_of_bounds_bullets(char * map, bool * doorways);
    /**
    *   @brief deletes any existing bullets
    */
    void delete_bullets();
    /**
    *   @brief shoots bullets at the direction of the buttons
    *   @param button_A @details button down
    *   @param button_B @details button right
    *   @param button_Y @details button up
    *   @param button_X @details button left
    */
    void buttons(bool button_A, bool button_B, bool button_Y, bool button_X);

    // Variables
    /**
    *   @brief a bullets pointer array that holds all the possible bullets the player can shoot
    */
    Bullets *bullets_array[bullets_max];
    /**
    *   @brief a boolean array that dictates which bullets in the bullets array exist
    */
    bool valid_bullets[bullets_max];
    
};

// Sprite
const char sprite_heart[9][9] = {
    {0,1,1,0,0,0,1,1,0,},
    {1,1,1,1,0,1,1,1,1,},
    {1,2,1,1,1,1,1,1,1,},
    {1,2,1,1,1,1,1,1,1,},
    {1,2,1,1,1,1,1,1,1,},
    {0,1,2,1,1,1,1,1,0,},
    {0,0,1,1,1,1,1,0,0,},
    {0,0,0,1,1,1,0,0,0,},
    {0,0,0,0,1,0,0,0,0,}
};

const char sprite_dying_player [5][12][12] = { // sprite_dying_player [Frame][Size_Y][Size_X]
    {
        {0,1,1,1,1,0,0,0,0,0,0,0,},
        {1,1,1,1,1,1,0,0,0,0,0,0,},
        {1,2,1,1,1,1,0,0,0,0,0,0,},
        {1,1,1,1,1,1,0,0,0,0,0,0,},
        {0,1,1,1,1,0,0,0,0,0,0,0,},
        {0,0,1,1,0,0,0,0,0,0,0,0,},
        {0,0,1,1,0,0,0,0,0,0,0,0,},
        {0,0,1,1,0,0,0,0,0,0,0,0,},
        {0,0,1,1,0,0,0,0,0,0,0,0,},
        {0,0,0,1,0,0,0,0,0,0,0,0,},
        {0,0,0,1,0,0,0,0,0,0,0,0,},
        {0,0,1,1,0,0,0,0,0,0,0,0,},
    },
    {
        {0,0,0,0,1,1,1,0,0,0,0,0,},
        {0,0,0,1,2,1,1,1,0,0,0,0,},
        {0,0,0,1,1,1,1,1,0,0,0,0,},
        {0,0,0,1,1,1,1,1,0,0,0,0,},
        {0,0,0,0,1,1,1,0,0,0,0,0,},
        {0,1,1,1,1,0,0,0,0,0,0,0,},
        {0,0,1,1,1,0,0,0,0,0,0,0,},
        {0,0,1,1,0,0,0,0,0,0,0,0,},
        {0,1,1,1,0,0,0,0,0,0,0,0,},
        {0,1,0,1,0,0,0,0,0,0,0,0,},
        {1,0,0,1,0,0,0,0,0,0,0,0,},
        {0,0,1,1,0,0,0,0,0,0,0,0,},
    },
    {
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,1,0,0,0,1,1,1,0,},
        {0,0,0,0,0,1,0,1,1,2,1,1,},
        {0,0,0,0,0,1,1,1,1,1,1,1,},
        {0,0,0,1,1,1,1,1,1,1,1,1,},
        {0,1,1,1,1,1,1,0,1,1,1,0,},
        {1,0,0,1,1,0,0,0,0,0,0,0,},
        {0,0,1,0,0,0,0,0,0,0,0,0,},
        {0,1,0,0,0,0,0,0,0,0,0,0,},
    },
    {
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {1,0,0,0,1,0,0,0,1,1,1,0,},
        {0,1,1,0,0,1,1,1,1,2,1,1,},
        {1,0,0,1,1,1,1,1,1,1,1,1,},
        {1,1,1,1,1,1,1,1,1,1,1,1,},
    },
    {
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,1,1,1,0,},
        {0,0,0,0,0,0,0,1,1,1,1,1,},
        {1,0,0,1,1,1,1,1,1,1,1,1,},
        {1,1,1,1,1,1,1,1,1,1,1,1,},
    }
};
    

const char sprite_transparent_player[12][6] = {
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,}
};

const char sprite_player [4][4][12][6] = {   // Player [Face][SpriteAnimationFrame][Size_Y][Size_X]
    {
        // Up
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,}
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,0,0,}
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,}
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {1,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,0,0,0,1,0,}
        }
    },
    {
        // Right
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,2,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,0,0,0,},
            {0,0,1,0,0,0,},
            {0,0,1,1,0,0,}
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,2,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,0,1,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,0,1,}
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,2,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,0,0,0,},
            {0,0,1,0,0,0,},
            {0,0,1,1,0,0,}
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,1,1,1,2,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,0,1,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,0,1,}
        }
    },
    {
        // Down
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,2,1,},
            {1,1,2,2,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,}
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,2,1,},
            {1,1,2,2,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,0,0,}
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,2,1,},
            {1,1,2,2,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {1,0,1,1,0,1,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,1,0,0,1,0,}
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,2,1,},
            {1,1,2,2,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,1,1,1,1,0,},
            {1,0,1,1,0,1,},
            {1,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,0,1,0,},
            {0,0,0,0,1,0,}
        }
    },
    {
        // Left
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,0,0,},
            {0,0,0,1,0,0,},
            {0,0,1,1,0,0,}
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,1,0,0,},
            {0,1,0,0,1,0,},
            {1,0,0,0,1,0,}
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,0,1,0,0,},
            {0,0,0,1,0,0,},
            {0,0,1,1,0,0,}
        },
        {
            {0,1,1,1,1,0,},
            {1,1,1,1,1,1,},
            {1,2,1,1,1,1,},
            {1,1,1,1,1,1,},
            {0,1,1,1,1,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,0,1,1,0,0,},
            {0,1,0,1,0,0,},
            {0,1,0,0,1,0,},
            {1,0,0,0,1,0,}
        }
    }
};

#endif