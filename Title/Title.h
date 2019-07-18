#ifndef TITLE_H
#define TITLE_H

#include "Player.h"
#include "N5110.h"
#include "Gamepad.h"
/**Title Class
@author Steven Mahasin
@brief Handles all Title Screen Interractions
@date May 2019
*/
class Title
{
private:
    // Member Variables
    /**
    *   @brief a counter that increments per loop, used to detect delays
    */
    int _title_count;
    /**
    *   @brief a delay period for the joystick to update another right or left input
    */
    int _cursor_timer;
    /**
    *   @brief an integer that stores which option the cursor is on
    *   @note 0 = Start, 1 = Options, 2 = Credits, 3 = Tutorial
    */
    int _title_option;
    
    // Methods
    /**
    *   @brief This function is used to draw the title screen along with the animations
    *   @param lcd @details the screen the title screen is drawn on
    */
    void draw_title_screen(N5110 &lcd);
    /**
    *   @brief This function is used to read the gamepad buttons and joystick, interracting with the member variable _title_option 
    *   @param gamepad @details the gamepad the input is being read from
    */
    void title_options_joystick(Gamepad &gamepad);
    
    /**
    *   @brief This function is called when the user chooses the title option "Option"
    *   @param lcd @details the screen the Options screen is drawn on
    *   @param gamepad @details the gamepad used to read the potentiometer
    *   @param player @details the player that is being used as a demo for the options screen
    *   @param global_contrast @details the global contrast that is being varried to be set for the whole game
    */
    void title_option_option(N5110 &lcd, Gamepad &gamepad, Player &player, float &global_contrast);
    /**
    *   @brief This function is called when the user chooses the title option "Credit"
    *   @param lcd @details the screen the credits is being displayed on
    *   @param gamepad @details the gamepad is used to read when the user decides to exit the credit page (button A)
    */
    void title_option_credit(N5110 &lcd, Gamepad &gamepad);
    /**
    *   @brief This function is called when the user chooses the title option "Tutorial"
    *   @param lcd @details the screen tutotrial is being displayed on
    *   @param gamepad @details the gamepad is used to read when the user decides to go to the next tutorial page (button A)
    */
    void title_option_tutorial(N5110 &lcd, Gamepad &gamepad);
    
    /**
    *   @brief This function is displays tutorial page 0
    *   @param lcd @details the screen the credits is being displayed on
    */
    void print_tutorial_page_0(N5110 &lcd);
    /**
    *   @brief This function is displays tutorial page 1
    *   @param lcd @details the screen the credits is being displayed on
    */
    void print_tutorial_page_1(N5110 &lcd);
    /**
    *   @brief This function is displays tutorial page 2
    *   @param lcd @details the screen the credits is being displayed on
    */
    void print_tutorial_page_2(N5110 &lcd);
    
public:
    /** Constructor */
    Title();
    
    // Accessor
    /** @brief to get the seed for rand()
    * @returns _title_count
    */
    int get_seed();
    
    // Functions
    /** @brief This function runs the whole Title screen, it contains the title loop and calls for the rest of the methods
    *   @param lcd @details the screen the Title screen is being displayed on
    *   @param gamepad @details the input the Title screen processes
    *   @param global_contrast @details the variable that is varied by the Title screen to chance screen contrast
    */
    void main(N5110 &lcd, Gamepad &gamepad, float &global_contrast);
};
    
#endif