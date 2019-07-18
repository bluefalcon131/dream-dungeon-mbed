#include "Title.h"

Title::Title()
{
    _title_count = 0;
    _cursor_timer = 20;
    _title_option = 0;
}

int Title::get_seed()
{
    return _title_count;
}

void Title::main(N5110 &lcd, Gamepad &gamepad, float &global_contrast)
{
    Player player(5, 36);
    while(1){  // Title Screen Loop
        _title_option = 0;
        while(!gamepad.check_event(Gamepad::A_PRESSED)){ 
            lcd.clear();
            draw_title_screen(lcd);
            lcd.refresh();
            title_options_joystick(gamepad);
            _title_count++;
            wait_ms(1000/40); // 1s/framerate
        }
        while(gamepad.check_event(Gamepad::A_PRESSED)){}
        
        if(_title_option == 0) { break;  // Start game, exit title loop
        } else if (_title_option == 1) { title_option_option(lcd, gamepad, player, global_contrast);
        } else if (_title_option == 2) { title_option_credit(lcd, gamepad);
        } else if (_title_option == 3) { title_option_tutorial(lcd, gamepad);
        }
    }
    player.~Player();
}

void Title::draw_title_screen(N5110 &lcd)
{
    lcd.drawSprite(11, 4, 15, 44, (char *)title_name_0);
    lcd.drawSpriteTransparent(19, 14, 17, 53, (char *)title_name_1);
    lcd.drawCircle(79, 7, 10, FILL_BLACK);
    lcd.drawCircle(81, 5, 8, FILL_WHITE);
    lcd.drawSprite(56, 6, 11, 5, (char *)star_sprite[abs(((_title_count/20) % 7) - 3)]);
    lcd.drawSprite(12, 34, 8, 8, (char *)button_A_sprite);
    lcd.drawSprite(22, 37, 3, 2, (char *)arrow_left_sprite);
    lcd.drawSprite(59, 37, 3, 2, (char *)arrow_right_sprite);
    lcd.drawSprite(69, 31, 12, 6, (char *)sprite_player[(_title_count/40) % 4][(_title_count/10) % 4]);
    lcd.drawSprite(26, 35, 9, 32, (char *)title_options_sprite[_title_option]);
}

void Title::title_options_joystick(Gamepad &gamepad)
{
    if ((gamepad.get_direction() == 3) && (_cursor_timer > 20)) {    // Detect Joystick going right
        _cursor_timer = 0;
        if (_title_option >= 3) {
            _title_option = 0;
        } else {
            _title_option++;
        }
    } else if ((gamepad.get_direction() == 7) && (_cursor_timer > 20)) { // Detect Joystick going left
        _cursor_timer = 0;
        if (_title_option <= 0) {
            _title_option = 3;
        } else {
            _title_option--;
        }
    }
    _cursor_timer++;
}

void Title::title_option_option(N5110 &lcd, Gamepad &gamepad, Player &player, float &global_contrast)
{
    while(!gamepad.check_event(Gamepad::A_PRESSED)) {
        global_contrast = gamepad.read_pot();
        lcd.setContrast(global_contrast);
        lcd.clear();
        lcd.printString("Set contrast", 0, 0);
        lcd.printString("using the", 0, 1);
        lcd.printString("potentiometer", 0, 2);
        player.draw(lcd);
        player.draw_bullets(lcd, player.get_pos_y() + 2);
        lcd.refresh();
        player.move(1, 0, (char *)level_map[0][0], (bool *)sprite_transparent_player);  // Adding animation of walking
        player.undo_move_x(true);   // Keeping the player in place
        player.buttons(false, true, false, false);  // Instructing player to shoot right
        player.delete_out_of_bounds_bullets((char *)level_map[0][0], (bool *)sprite_transparent_player);  // Move the bullets and delete those out of the screen
        wait_ms(1000/40);
    }
    wait(0.05);
    while(gamepad.check_event(Gamepad::A_PRESSED)) {}
}

void Title::title_option_credit(N5110 &lcd, Gamepad &gamepad)
{
    lcd.clear();
    lcd.printString("Made by:", 0, 0);
    lcd.printString("Steven Mahasin", 0, 1);
    lcd.printString("201192939", 0, 2);
    lcd.refresh();
    wait(0.05);
    while(!gamepad.check_event(Gamepad::A_PRESSED)) {
    }
    wait(0.05);
    while(gamepad.check_event(Gamepad::A_PRESSED)) {
    }
}

void Title::title_option_tutorial(N5110 &lcd, Gamepad &gamepad)
{
    print_tutorial_page_0(lcd);                         // print page 0 and wait for button toggle
    wait(0.05);
    while(!gamepad.check_event(Gamepad::A_PRESSED)) {}
    wait(0.05);
    while(gamepad.check_event(Gamepad::A_PRESSED)) {}
    print_tutorial_page_1(lcd);                         // print page 1 and wait for button toggle
    wait(0.05);
    while(!gamepad.check_event(Gamepad::A_PRESSED)) {}
    wait(0.05);
    while(gamepad.check_event(Gamepad::A_PRESSED)) {}
    print_tutorial_page_2(lcd);                         // print page 2 and wait for button toggle
    wait(0.05);
    while(!gamepad.check_event(Gamepad::A_PRESSED)) {}
    wait(0.05);
    while(gamepad.check_event(Gamepad::A_PRESSED)) {}
}

void Title::print_tutorial_page_0(N5110 &lcd)
{
    lcd.clear();
    lcd.printString("Use the joypad", 0, 0);
    lcd.printString("to move the", 0, 1);
    lcd.printString("player", 0, 2);
    lcd.printString("Use buttons", 0, 3);
    lcd.printString("ABXY to shoot", 0, 4);
    lcd.printString("directionally", 0, 5);
    lcd.refresh();
}

void Title::print_tutorial_page_1(N5110 &lcd)
{
    lcd.clear();
    lcd.printString("Hold L to", 0, 0);
    lcd.printString("show player", 0, 1);
    lcd.printString("health", 0, 2);
    lcd.printString("Hold R to", 0, 3);
    lcd.printString("view explored", 0, 4);
    lcd.printString("minimap", 0, 5);
    lcd.refresh();
}

void Title::print_tutorial_page_2(N5110 &lcd)
{
    lcd.clear();
    lcd.printString("Press Start", 0, 0);
    lcd.printString("to pause", 0, 1);
    lcd.printString("the game", 0, 2);
    lcd.refresh();
}