/*
@file main_menu.c
@author entire team
@date 3/22/2023
@brief Main menu animation
*/

#include <gb/gb.h>
#include <gb/cgb.h>
#include "common.h"
#include "graphics/Menu_BG.c"
#include "graphics/Menu_BG_Map.c"
#include "graphics/palletes.c"
#include "graphics/Letters.h"
#include "graphics/Game_Logo.c"
#include "graphics/Game_Logo_Map.c"

uchar menu_option = 0;
#define MAX_OPTION 4
#define MAX_LETTERS 12

uchar menu_text_baseline = (17)*8;
uchar menu_text_length;
const uchar *menu_text;

const int8_t menu_text_position_table[8] = {0, -1, -2, -1, 0, 1, 2, 1};

//Changes the y-coordinate of the letters
// based on the animation frame
void menu_text_anim() {
    static uchar frame = 0;
    frame++;
    frame %= 8;
    for (uchar i = 0; i < MAX_LETTERS; ++i){
        if (menu_text[i] == ' ') {
            continue;
        }
        move_sprite(i, ((i+11)*8-menu_text_length*4), menu_text_baseline + menu_text_position_table[(frame+i)%8]);
    }
}

//Update the text to the given string
void change_menu_text(const uchar *text, uchar length){
    if (text == NULL) {
        return;
    }
    menu_text_length = length;
    menu_text = text;

    for (uchar i = 0; i < MAX_LETTERS; ++i){
        uchar tile = text[i]-'A';
        if (i < length && text[i] != ' ') {
            set_sprite_tile(i, letter_table[tile]);
        } else {
            move_sprite(i, 0, 0);
        }
    }
}

//Updates the menu text based on the current menu_option
void update_menu_text(){
    switch (menu_option){
        case 0:
            change_menu_text("DEMO        ", 4);
            break;
        case 1:
            change_menu_text("STORY       ", 5);
            break;
        case 2:
            change_menu_text("MULTILINK   ", 9);
            break;
        case 3:
            change_menu_text("SETTINGS    ", 8);
            break;
        default:
            change_menu_text("PRESS START ", 11);
    }
}

//Animates the scrolling options left/right
void optionscroll(uchar dir){
    change_menu_text("            ", 0);
    for (uchar i = 0; i < 40; ++i){
        if (dir == 1){
            scroll_bkg(1, 0);
        }
        else{
            scroll_bkg(-1, 0);
        }
        wait_vbl_done();
    } 
    update_menu_text();
}

uchar logoWindowBuffer[2][32];

void menu_vblank_routine(){
    //LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJOFF | LCDCF_WIN9C00 | LCDCF_WINON | LCDCF_OBJ16;
    SHOW_WIN;
    while (LY_REG != 8 * 8) ;
    HIDE_WIN;
    //LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_WINOFF | LCDCF_OBJ16;
}

void mainmenu(){
    game_mode = MODE_MAIN_MENU;
    hide_sprite(5);
    set_bkg_palette(0, 1, colors);
    set_bkg_data(0, 19, Menu_BG);
    set_bkg_tiles(0, 11, 10, 4, Menu_BG_Map);
    set_bkg_tiles(10, 11, 10, 4, Menu_BG_Map);
    move_bkg(0,0);
    scroll_bkg(-64, 0);
    set_bkg_data(19, 111, game_logo_data);
    set_win_tiles(0, 0, 20, 8, game_logo_map);
    set_sprite_data(0, 46, Letters); //46 tiles, 23 letters

    VBK_REG = VBK_BANK_0;

    SPRITES_8x16;
    set_sprite_palette(0, 4, colors_objects);
    menu_option = MAX_OPTION;
    update_menu_text();
    
    SHOW_SPRITES;
    SHOW_BKG;
    SHOW_WIN;
    
    DISPLAY_ON;
    wait_vbl_done();

    uchar anim_frame = 0;
    uchar anim_delay = 0;
    while (1) {
        
        if (anim_delay == 0){
            menu_text_anim();   
        }
        ++anim_delay;
        anim_delay %=8;

        if (joy_impulse & J_START && menu_option == MAX_OPTION){
            menu_option = 0;
            update_menu_text();
        }
        else if (joy_impulse & J_A && menu_option < MAX_OPTION){
            HIDE_WIN;
            return;
        }
        else if (joy_impulse & J_RIGHT && menu_option < MAX_OPTION - 1){
            ++menu_option;
            optionscroll(1);
        } 
        else if (joy_impulse & J_LEFT && menu_option > 0 && menu_option < MAX_OPTION){
            --menu_option;
            optionscroll(2);
        }
        SHOW_BKG;
        wait_vbl_done();
    }
}