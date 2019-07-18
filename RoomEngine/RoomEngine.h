#ifndef ROOMENGINE_H
#define ROOMENGINE_H
#include "N5110.h"
#include "Gamepad.h"

#include "Player.h"
#include "Health.h"
#include "Room.h"

#include "sprites.h"
#define MAX_ROOMS_MAP_X 11
#define MAX_ROOMS_MAP_Y 11

/**RoomEngine Class
@author Steven Mahasin
@brief Handles all Inter-Class Interactions in the room
@date May 2019
*/
class RoomEngine
{
public:
    /** Constructor 
    *   @param global_contrast @details the contrast that the game runs on, set by title screen
    */
    RoomEngine(float global_contrast);
    /** Destructor */
    ~RoomEngine();
    
    // Functions
    /**
    *   @brief loads the current player and room into the engine
    *   @param current_player @details the player we control
    *   @param current_room @details the room the player is currently in
    */
    void load(Player *current_player, Room *current_room);
    /**
    *   @brief plays an entrance_scene of the player into the room
    *   @param lcd @details the screen that is being drawn on
    *   @param gamepad @details the gamepad whose controls are being read
    */
    void entrance_scene(N5110 &lcd, Gamepad &gamepad);
    /**
    *   @brief increments the room coordinate based on which side the player exits the screen from
    */
    void update_current_room();
    
    /**
    *   @brief returns 0-4 based on the player's position in the screen
    *   @return which side of the screen the player is currently at (4 = inside)
    */
    int check_player_room_position();
    
    /**
    *   @brief reads the input from the gamepad and converts it into member variables
    *   @param gamepad @details the gamepad whose controls are being read
    */
    void read_input(Gamepad &gamepad);
    /**
    *   @brief updates the interaction between entities in room (enemies hp, damage, etc)
    *   @param number_of_enemies_killed @details for the final score, gets incremented everytime an enemy is killed
    */
    void update(int &number_of_enemies_killed);
    /**
    *   @brief to draw all the map, entities, doorway onto the screen
    *   @param lcd @details the screen that the roomengine draws on
    */
    void render(N5110 &lcd, Gamepad &gamepad);
    
    /**
    *   @brief Plays an exit scene of the player leaving the room
    *   @param lcd @details the screen that the exit scene is drawn on
    *   @param gamepad @details the gamepad whose controls are being read
    */
    void exit_scene(N5110 &lcd, Gamepad &gamepad);
    
    // Accessor
    /**
    *   @brief reads the member variable _room_x
    *   @return the current room's x-coordinate
    */
    int get_room_x();
    /**
    *   @brief reads the member variable _room_y
    *   @return the current room's y-coordinate
    */
    int get_room_y();
    
private:
    // Member variables
    /**
    *   @brief A boolean to indicate if button L is pressed
    */
    bool _L;
    /**
    *   @brief A boolean to indicate if button R is pressed
    */
    bool _R;
    /**
    *   @brief A boolean to indicate if button A is pressed
    */
    bool _A;
    /**
    *   @brief A boolean to indicate if button B is pressed
    */
    bool _B;
    /**
    *   @brief A boolean to indicate if button X is pressed
    */
    bool _X;
    /**
    *   @brief A boolean to indicate if button Y is pressed
    */
    bool _Y;
    /**
    *   @brief A vector2D that stores the x and y of the mapped_coordinates of the joystick
    */
    Vector2D mapped_coord;
    /**
    *   @brief The x-coordinate value for the current room's position
    */
    int _room_x;
    /**
    *   @brief The y-coordinate value for the current room's position
    */
    int _room_y;
    /**
    *   @brief The value of set contrast from title screen, which dictates the contrast of lcd
    */
    float _global_contrast;
    /**
    *   @brief A pointer to a Room, used to access the current room class and it's functions
    */
    Room *room;
    /**
    *   @brief A pointer to a Player, used to access the current player class and it's functions
    */
    Player *player;
    
    // Mutator
    /**
    *   @brief mutates all the user input manually
    *   @param L @details value to be written onto _L
    *   @param R @details value to be written onto _R
    *   @param A @details value to be written onto _A
    *   @param B @details value to be written onto _B
    *   @param X @details value to be written onto _X
    *   @param Y @details value to be written onto _Y
    *   @param mapped_x @details value to be written onto _mapped_coord.x
    *   @param mapped_y @details value to be written onto _mapped_coord.y
    */
    void set_input(bool L, bool R, bool A, bool B, bool X, bool Y, float mapped_x, float mapped_y);
    /**
    *   @brief mutates _mapped_coord manually
    *   @param mapped_x @details value to be written onto _mapped_coord.x
    *   @param mapped_y @details value to be written onto _mapped_coord.y
    */
    void set_mapped_coord(float x, float y);
    
    // Methods
    /**
    *   @brief checks if the two entities a and b collide
    *   @param a @details entity a to be checked if colliding with entity  b
    *   @param b @details entity b to be checked if colliding with entity  a
    *   @return true if the two entities collide
    */
    bool entity_collision(Entity &a, Entity &b);
    /**
    *   @brief checks if the entity a collides with any entities in the entity array "array[]" if entity a moves in the x direction
    *   @param a @details entity a to be checked if colliding with any entity in the array[]
    *   @param array[] @details an array of entities to be check if colliding with a
    *   @param no_of_enemies @details constant length of enemies in the array[]
    *   @param current_entity @details the index of the enemy to be ignored if entity a is within array[]
    *   @param valid_enemies[] @details the array that defines which entities in array[] exists
    *   @return -1 or 1 if the entity a collides with any entities in the entity array "array[]" when entity a moves in the x direction depending if a's x pos is bigger than the colliding entity's x pos or not
    */
    float entity_move_check_x(Entity *a, Entity *array[], int no_of_enemies, int current_entity, bool valid_enemies[]);
    /**
    *   @brief checks if the entity a collides with any entities in the entity array "array[]" if entity a moves in the y direction
    *   @param a @details entity a to be checked if colliding with any entity in the array[]
    *   @param array[] @details an array of entities to be check if colliding with a
    *   @param no_of_enemies @details constant length of enemies in the array[]
    *   @param current_entity @details the index of the enemy to be ignored if entity a is within array[]
    *   @param valid_enemies[] @details the array that defines which entities in array[] exists
    *   @return -1 or 1 if the entity a collides with any entities in the entity array "array[]" when entity a moves in the y direction depending if a's x pos is bigger than the colliding entity's x pos or not
    */
    float entity_move_check_y(Entity *a, Entity *array[], int no_of_enemies, int current_entity, bool valid_enemies[]);
    
    /**
    *   @brief inflict any damage happening to any entities in the room
    */
    void check_damage();
    /**
    *   @brief inflict any damage happening to the player in the room
    */
    void check_damage_player();
    /**
    *   @brief inflict any damage happening to any enemies in the room
    */
    void check_damage_enemies();
    /**
    *   @brief delete any enemies that has it's health depleted
    *   @param number_of_enemies_killed @details increments whenever an enemy is successfully deleted
    */
    void check_enemies_death(int &number_of_enemies_killed);
    /**
    *   @brief undo movement of entity if the entity collides with the wall (not used in this version)
    */
    void check_walls_collision();
    
    /**
    *   @brief updates the positions of all entities
    */
    void move();
    /**
    *   @brief updates the positions of player based on the joystick and wall constraint
    */
    void move_player();
    /**
    *   @brief updates the positions of enemies based on their coded movement patterns, repulsion effect and wall constraint
    */
    void move_enemies();
    /**
    *   @brief updates the position of the player whenever the player has just exit the screen
    *   @param side @details the side the player exits the room from
    */
    void update_player_position(int side);
    
    /**
    *   @brief holds the loop and detection for when a player pauses
    *   @param lcd @details the screen where the paused screen is going to be displayed on
    *   @param gamepad @details the gamepad whose controls are being read
    */
    void pause_detection(N5110 &lcd, Gamepad &gamepad);
    /**
    *   @brief draws the pause screen onto lcd
    *   @param lcd @details the screen where the paused screen is going to be displayed on
    *   @param paused_screen @details the char array of the frozen screen when paused
    *   @param pause_timer @details the loop count to check if the pause sprite should appear or not for blink effect
    */
    void draw_pause_screen(N5110 &lcd, char * paused_screen, int &pause_timer);
    
    /**
    *   @brief draws the map, the entities and map overlays in the order of descending j
    *   @param lcd @details the screen where all entities are being drawn on
    */
    void draw(N5110 &lcd);
    /**
    *   @brief draws number of hp as hearts on the top left of the screen whenever the user holds button L
    *   @param lcd @details the screen where the hearts are being drawn on
    */
    void draw_health(N5110 &lcd);
    
};
#endif