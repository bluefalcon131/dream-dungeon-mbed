#ifndef ENTITY_H
#define ENTITY_H
#include "sprites.h"
#include "math.h"
#include "N5110.h"

/**Entity Abstract Class
@author Steven Mahasin
@brief Creates an Entity which holds entity datas, functions(movements, damaged actions, collision test, etc), accessors and functions to be inherited by child classes
@date May 2019
*/
class Entity
{
protected:
    struct Hitbox {
        int width;
        int height;
    };
    struct SpriteSize {
        int width;
        int height;
        // Top-left corner of sprite is offset_x
        // to the right of top-left corner of hitbox
        int offset_x;
        // Top-left corner of sprite is offset_y
        // below of top-left corner of hitbox
        int offset_y;
    };
    struct Position {
        float x;
        float y;
    };
    struct FrameCount  {
        int count;
        int number;
        int max;
    };
    /**
    *   @brief A struct containing hitbox data for the entity
    *   @info width and height
    */
    Hitbox _hitbox;
    /**
    *   @brief A struct containing sprite size data for the entity, to be used when drawing sprites on top of their hitboxes
    *   @info sprite width, sprite height, sprite offset x from hitbox, sprite offset y from hitbox
    */
    SpriteSize _sprite_size;
    /**
    *   @brief A struct containing the position of the entity, this position is the top-left corner of the hitbox
    */
    Position _position;
    /**
    *   @brief A struct containing the position of the entity one loop behind
    */
    Position _prev_pos;
    /**
    *   @brief A struct containing frame count, frame number and frame max. Used to animate entities
    */
    FrameCount _frame;
    /**
    *   @brief The health point of an entity
    */
    int _hp;
    /**
    *   @brief The damage the entity does if it attacks another entity
    */
    int _attack;
    /**
    *   @brief The direction the entity is facing
    */
    int _face;
    /**
    *   @brief The speed the entity moves
    */
    float _velocity;
    /**
    *   @brief The chance(out of 100) of dropping a heart when the entity is deleted.
    */
    int _hp_drop_chance;

public:
    // Function
    /**
    *   @brief a virtual function movement of the entity to be inherited
    *   @param x_value @details either joystick x or player's x position
    *   @param y_value @details either joystick y or player's y position
    *   @param map @details the 2d map array that dictates where there are walls or empty space
    *   @param doorways @details an array that dictates which side of the wall has a doorway
    */
    virtual void move(float x_value, float y_value, char * map, bool * doorways) = 0; // movement control and miscellaneous updates
    /**
    *   @brief a virtual function of the action when taking damage to be inherited
    *   @param damage @details the amount of damage to be taken
    */
    virtual void take_damage(int damage) = 0;
    /**
    *   @brief a virtual function of drawing the entity to be inherited
    *   @param lcd @details the screen where the entity is drawn on
    */
    virtual void draw(N5110 &lcd) = 0;
    /**
    *   @brief a function to undo entity's movement in the x direction if condition is true
    *   @param condition @details a boolean statement
    */
    void undo_move_x(bool condition);
    /**
    *   @brief a function to undo entity's movement in the y direction if condition is true
    *   @param condition @details a boolean statement
    */
    void undo_move_y(bool condition);
    /**
    *   @brief updates the _prev_pos into _position
    */
    void update_prev_pos();
    /**
    *   @brief checks if the entity collides the map
    *   @param pos_x @details entity's x-position
    *   @param pos_y @details entity's y-position
    *   @param two_d_map @details the 2d map array that dictates where there are walls or empty space
    *   @param doorways @details an array that dictates which side of the wall has a doorway
    *   @return true if entity collide with the map
    */
    bool entity_to_map_collision_test(float pos_x, float pos_y, char * two_d_map, bool * doorways);

    // Mutator
    /**
    *   @brief mutates position of the entity to x and y
    *   @param x @details x-coordinate value
    *   @param y @details y-coordinate value
    */
    void set_position(float x, float y);
    /**
    *   @brief adds change_x onto x-position of the entity
    *   @param change_x @details displacement x
    */
    void position_add_x(float change_x);
    /**
    *   @brief adds change_y onto y-position of the entity
    *   @param change_y @details displacement y
    */
    void position_add_y(float change_y);
    
    // Accessors
    /**
    *   @brief gets the entity's chance to drop a health
    *   @return _hp_drop_chance
    */
    int get_hp_drop_chance();
    /**
    *   @brief gets the entity's hitbox width
    *   @return _hitbox.width
    */
    int get_hitbox_width();
    /**
    *   @brief gets the entity's hitbox height
    *   @return _hitbox.height
    */
    int get_hitbox_height();
    /**
    *   @brief gets the entity's face
    *   @return _face
    */
    int get_face();
    /**
    *   @brief gets the entity's sprite width
    *   @return _sprite_size.width
    */
    int get_sprite_width();
    /**
    *   @brief gets the entity's sprite height
    *   @return _sprite_size.height
    */
    int get_sprite_height();
    /**
    *   @brief gets the entity's sprite x-offset
    *   @return _sprite_size.offset_x
    */
    int get_offset_x();
    /**
    *   @brief gets the entity's sprite y-offset
    *   @return _sprite_size.offset_y
    */
    int get_offset_y();
    /**
    *   @brief gets the entity's x-position
    *   @return _position.x
    */
    int get_pos_x();
    /**
    *   @brief gets the entity's y-position
    *   @return _position.y
    */
    int get_pos_y();
    /**
    *   @brief gets the entity's previous x-position
    *   @return _prev_pos.x
    */
    int get_prev_pos_x();
    /**
    *   @brief gets the entity's previous y-position
    *   @return _prev_pos.y
    */
    int get_prev_pos_y();
    /**
    *   @brief gets the entity's attack
    *   @return _attack
    */
    int get_attack();
    /**
    *   @brief gets the entity's hp
    *   @return _hp
    */
    int get_hp();
    /**
    *   @brief gets the entity's velocity
    *   @return _velocity
    */
    float get_velocity();

};

#endif