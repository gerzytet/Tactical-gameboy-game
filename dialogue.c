/*
@file dialogue.c
@author entire team
@date 3/22/2023
@brief Dialogue system
*/

#include <gb/gb.h>
#include <gb/cgb.h>
#include "common.h"
#include "graphics/TextBox.h"
#include "graphics/TextBoxMap.h"
#include "graphics/Numbers.h"
#include "graphics/Symbols.h"

#include "graphics/character_art/guard_text_data.h"
#include "graphics/character_art/guard_text_map.h"
#include "graphics/character_art/elf_text_data.h"
#include "graphics/character_art/elf_text_map_left.h"
//todo: rest of cast

#define TILEMAP_START 0x9800
#define WIN_TILEMAP_START 0x9C00

const uchar* script[20] = {
    "MEET FREDRIK, A ", "FIERCE WARRIOR  ", "WITH A STRONG   ", "REPUTATION,     ",
    "MARIE, A        ", "MYSTERIOUS WOMAN", "WITH HIDDEN     ", "POWERS,         ",
    "AND BOSTON, AN  ", "EX-SOLDIER WITH ", "A POWERFUL      ", "MACHINE GUN.    ",
    "YOU WILL HAVE TO", "TRAVEL TO       ", "DISTANT LANDS   ", "AND OVERCOME    ",
    "MANY CHALLENGES ", "ON YOUR QUEST TO", "OVERCOME THE    ", "FORCES OF EVIL. "
};

const uchar* script2[16] = {
    "PRESS THE A     ", "BUTTON ON THE   ", "CHARACTER YOU   ", "WOULD LIKE TO   ",
    "MOVE, AND PRESS ", "A AGAIN TO      ", "CONFIRM         ", "YOUR MOVE.      ",
    "YOU CAN ATTACK  ", "AN ENEMY OR PICK", "UP AN ITEM      ", "AFTER MOVING.   ",
    "FOR THIS MAP,   ", "YOU WILL HAVE TO", "STAY ALIVE UNTIL", "BACKUP ARRIVES. ",
};

const uchar* dialogueCharNames[3] = {"FREDRIK", "MARIE", "BOSTON"};

const uchar sceneTextLength[12] = {10,8,5,5,5,5,5,5,5,5,5,5};
const uchar image[10] = {0,0,0,0,0,0,0,0,0,0};

//remove
const uchar imageLeft[12] = {5,5,5,5,5};
const uchar imageRight[12] = {5,5,5,5,5};

uchar dialogueIndex = 0;
uchar dialogueSceneIndex = 0;

void set_text(const uchar *textLine1, const uchar *textLine2 ,uchar charNameIndex){
    if (textLine1 == NULL) {
        return;
    }
    volatile uchar *tilemap = (uchar *)TILEMAP_START;
    static uchar tile;
    charNameIndex = charNameIndex;
    
    for (uchar i = 0; i < 16; ++i){
        switch(textLine1[i])
        {
            case (' '):
                tile = (uchar)(SPACE_LETTER+128);
                break;
            case (','):
                tile = 34; 
                break;
            case ('.'):
                tile = 36;
                break;

            case ('!'):
                tile = 38;
                break;

            case ('?'):
                tile = 40;
                break;

            case ('-'):
                tile = 42;
                break;

            case ('~'):
                tile = 44;
                break;

            default:
                tile = letter_table[textLine1[i] - 'A']+128;
        }
        tilemap[i+418] = tile;
        tile++;
        tilemap[(i+450)] = tile;
        wait_vbl_done();
    }

    if (textLine2 == NULL) {
        return;
    }
    for (uchar i = 0; i < 16; ++i){
        switch(textLine2[i])
        {
            case (' '):
                tile = (uchar)(SPACE_LETTER+128);
                break;
            case (','):
                tile = 34;
                break;
            case ('.'):
                tile = 36;
                break;

            case ('!'):
                tile = 38;
                break;

            case ('?'):
                tile = 40;
                break;

            case ('-'):
                tile = 42;
                break;

            case ('~'):
                tile = 44;
                break;

            default:
                tile = letter_table[textLine2[i] - 'A']+128;
        }
        tilemap[(i+482)] = tile;
        tile++;
        tilemap[(i+514)] = tile;
        wait_vbl_done();
    }

    return;
}

void set_char_sprite(uchar charSpriteIndex, uchar pos){
    charSpriteIndex = charSpriteIndex;
    pos = pos;
    //pos 0 center 1 left 2 right

    /*switch(charSpriteIndex){
        case(0):
            //f
            break;
        case(1):
            //m
            break;
        case(2):
            //b
            break;
        case(3):
            //bandit
            break;
        case(4):
            //elf
            switch(pos):
                case(2):
                    set_banked_bkg_data(58, 54, elf_text_data,2);
                    set_banked_bkg_tiles(12,3, 8, 9, elf_text_map_left,2);
                    break;
            break;
        case(5):
            //guard
            switch(pos):
                case(1):
                    set_banked_bkg_data(186, 68, guard_text_data,2);
                    set_banked_bkg_tiles(0,2, 8, 10, guard_text_map,2);
            break;
        case(6):
            //orallov
            break;
    }*/

    //set guard left
    set_banked_bkg_data(186, 68, guard_text_data,2);
    set_banked_bkg_tiles(0,2, 8, 10, guard_text_map,2);

    //set elf right
    set_banked_bkg_data(58, 54, elf_text_data,2);
    set_banked_bkg_tiles(12,3, 8, 9, elf_text_map_left,2);

    return;
}

//Advance the text after pressing the A Button
void advance_text(){
    if (dialogueIndex >= sceneTextLength[dialogueSceneIndex]){
        ++dialogueIndex;
        return;
    }
    
    if (dialogueIndex == 0 || imageLeft[dialogueIndex-1] != imageLeft[dialogueIndex-1]){
        set_char_sprite(image[dialogueIndex], 0);
    }
    /*if (dialogueIndex == 0 || imageRight[dialogueIndex-1] != imageRight[dialogueIndex-1]){
        set_char_sprite(imageRight[dialogueIndex], 2);
    }*/

    //fix later
    if (dialogueSceneIndex == 0){
        set_text(script[2*dialogueIndex], script[2*dialogueIndex+1],0);//dialogueCharNames[dialogueIndex]);
    }
    else{
        set_text(script2[2*dialogueIndex], script2[2*dialogueIndex+1],0);//dialogueCharNames[dialogueIndex]);
    }
    ++dialogueIndex;
}

void setupTextBox(){
    for (uchar i = 0; i < 20; ++i){
        set_bkg_tile_xy(i,11,0);
    }
    set_banked_bkg_data(0, 14, TextBox, 2);
    set_banked_bkg_tiles(0, 12, 20, 6, TextBoxMap, 2);

    set_banked_bkg_data(128, 46, Letters, 2); //letters. 46 tiles.  23 letters
    set_banked_bkg_data(14, 20, Numbers, 2); //numbers. 20 tiles. 10 numbers
    set_banked_bkg_data(34, 12, Symbols, 2); //symbols. 12 tiles. 6 symbols
    //set JQXZ
    //4 tiles leftover in bkg

    //hide "STORY" text
    for(int i = 0; i < 5; ++i){
        hide_sprite(i);
    }
}

//Initialize the dialogue scene
void play_scene(uchar index){
    game_mode = MODE_DIALOGUE;
    dialogueSceneIndex = index;
    //cls();
    set_bkg_palette(0, 1, colors);
    move_bkg(0,0);
    
    setupTextBox();
    //setup character art
    
    //intro anim
    DISPLAY_ON;

    wait_vbl_done();
    advance_text();
    while (dialogueIndex <= sceneTextLength[index]){		
        if (joy_impulse & J_A){
            advance_text();
        }
        wait_vbl_done();
    }
    dialogueIndex = 0;
    
    //outro anim
}
