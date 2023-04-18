/*
@file dialogue.c
@author entire team
@date 3/22/2023
@brief Dialogue system
*/

#include <gb/gb.h>
#include <gb/cgb.h>
#include "common.h"
#include "../graphics/palettes.c"
#include "../graphics/TextBox.h"
#include "../graphics/TextBoxMap.h"
#include "../graphics/Letters.h"
#include "../graphics/Numbers.h"
#include "../graphics/Symbols.h"
#include "../graphics/Letters_Extra.h"

#include "../graphics/character_art/guard_text_data.h"
#include "../graphics/character_art/guard_text_map.h"
#include "../graphics/character_art/elf_text_data.h"
#include "../graphics/character_art/elf_text_map_left.h"
//todo: rest of cast

#define TILEMAP_START 0x9800
#define WIN_TILEMAP_START 0x9C00

const uchar* script[158] = {
    //text 0
    "LONG AGO IN THE ", "LAND OF MERPROV,", "A RUTHLESS RULER", "FORGED THE      ",
    "CHRONO STONE,   ", "WHICH HAD THE   ", "POWER TO TRADE  ", "ANOTHER'S YOUTH ",
    "FOR GAINING IT  ", "THEMSELVES.     ", "THE RULER WAS   ", "NOT STRONG      ",
    "ENOUGH TO DEFEND", "AGAINST THE     ", "HORDES SEEKING  ", "TO KILL HIM AND ",
    "SIEZE THE       ", "CHRONO STONE.   ", "BEFORE HE DIED, ", "HE HID THE STONE",
    "BEHIND POWERFUL,", "FOREIGN MAGIC   ", "AND NO ONE WAS  ", "ABLE TO FIND IT.",
    "MEET FREDRIK, A ", "FIERCE WARRIOR  ", "WITH A STRONG   ", "REPUTATION,     ",
    "MARIE, A        ", "MYSTERIOUS WOMAN", "WITH HIDDEN     ", "POWERS,         ",
    "AND BOSTON, AN  ", "EX-SOLDIER WITH ", "A POWERFUL      ", "MACHINE GUN.    ",
    "YOU WILL HAVE TO", "TRAVEL TO       ", "DISTANT LANDS   ", "AND OVERCOME    ",
    "MANY CHALLENGES ", "ON YOUR QUEST TO", "OVERCOME THE    ", "FORCES OF EVIL. ",

    //text 1
    "A VILLIAGE WHERE", "OUR HEROES HAVE ", "BEEN LODGING HAS", "JUST BEEN       ",
    "ATTACKED BY     ", "BANDITS!        ", "FREDERIK, MARIE,", "AND BOSTON FEEL ",
    "UNPREPARED FOR  ", "THE TASK BUT    ", "AREN'T SURE IF  ", "ANYONE ELSE IS  ",
    "ABLE TO DEFEND  ", "THE PEOPLE.     ", "THEY EACH GRAB  ", "THEIR WEAPONS   ",
    "AND RUSH TO THE ", "SCENE OF BATTLE.",
    "PRESS THE A     ", "BUTTON ON THE   ", "CHARACTER YOU   ", "WOULD LIKE TO   ",
    "MOVE, AND PRESS ", "A AGAIN TO      ", "CONFIRM         ", "YOUR MOVE.      ",
    "YOU CAN ATTACK  ", "AN ENEMY OR PICK", "UP AN ITEM      ", "AFTER MOVING.   ",
    "FOR THIS MAP,   ", "YOU WILL HAVE TO", "STAY ALIVE UNTIL", "BACKUP ARRIVES. "

    //text 2
    "THE IMPERIAL    ", "ARMY FINALLY    ", "ARRIVE, HOWEVER,", "THE BANDITS HAVE",
    "ALREADY BEEN    ", "DEFEATED.       ", "OUR HEROES HAVE ", "GAINED THE TRUST",
    "AND RESPECT FROM", "THANK YOU FOR   ", "SAVING US FROM  ", "THOSE BANDITS!  ",
    "HERE, HAVE SOME ", "HEALTH POTIONS  ", "AND WEAPONS.    ", "MARIE, DID YOU  ",
    "SEE THE STRANGE ", "MARKINGS ON     ", "THAT BANDIT'S   ", "CLOTHING?       ",
    "I BELIEVE I'VE  ", "READ SOMETHING  ", "ABOUT THOSE     ", "IN THE LIBRARY. ",
    "THEY SEEM TO BE ", "CALLED THE      ", "BLOOD RAVAGERS, ", "AND HAVE A MAIN ",
    "FORTRESS JUST   ", "SOUTH OF HERE.  ", "THERE ARE NOT   ", "MANY OF THEM,   ",
    "BUT THE PEOPLE  ", "DO NOT HAVE     ", "ADEQUATE        ", "SUPPLIES TO     ",
    "FIGHT THEM      ", "THEMSELVES.     ", "DO YOU THINK WE ", "CAN DRIVE THEM  ",
    "OUT FOR GOOD?   ", "                ", "POSSIBLY, BUT   ", "WE WILL NEED TO ",
    "PLAN OUR ATTACK ", "CAREFULLY AND   ", "NOT ATTACK THEM ", "ALL AT ONCE.    ",
    
    //text 3
    "OUR HEROES      ", "ARRIVE AT THE   ", "BLOOD RAVAGERS' ", "FORTRESS.       ",
    "THERE ARE NOT   ", "MANY ON PATROL  ", "TONIGHT, BUT    ", "MORE MAY COME   ",
    "IF YOU ARE NOT  ", "CAREFUL.        ",

    //text 4
    "OUR HEROES HAVE ", "DEFEATED THE    ", "BLOOD RAVAGERS, ", "AND LEARN THAT  ",
    "THE BANDITS     ", "WERE SENT BY    ", "THE SORCERESS   ", "ORALLOV SO      ",
    "THAT THE PEOPLE ", "WILL TRUST THE  ", "ARMY THAT       ", "DELIVERED THEM. ",
    "AS THE BANDITS  ", "AND SOLDIERS    ", "MAKE THEIR WAY  ", "THROUGH THE     ",
    "TOWNS, OUR      ", "HEROES DECIDE   ", "TO ESCAPE       ", "ACROSS THE SEA  ",
    "TO THE COUNTRY  ", "OF GRANDUEL.    "
    
    //text 5
    //text 6
    //text 7
    //text 8
    //text 9
    //text 10
    //text 11



};

const uchar* dialogueCharNames[3] = {"FREDRIK", "MARIE", "BOSTON"};

const uchar sceneTextLength[12] = {22,17,24,5,11,5,5,5,5,5,5,5};
const uchar sceneTextOffset[12] = {0,22,39,63,68,79,0,0,0,0,0,0};
const uchar image[10] = {0,0,0,0,0,0,0,0,0,0};

//remove
const uchar imageLeft[12] = {5,5,5,5,5};
const uchar imageRight[12] = {5,5,5,5,5};

uchar dialogueIndex = 0;
uchar dialogueSceneIndex = 0;

void set_text(uchar index,uchar charNameIndex){
    const uchar *textLine1 = script[index*2];
    const uchar *textLine2 = script[index*2+1];

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

            case ('J'):
                tile = 46;
                break;
        
            case ('Q'):
                tile = 48;
                break;

            case ('X'):
                tile = 50;
                break;

            case ('Z'):
                tile = 52;
                break;


            default:
                tile = letter_table[textLine1[i] - 'A']+128;
        }
        tilemap[i+418] = tile;
        tile++;
        tilemap[i+450] = tile;
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

            case ('J'):
                tile = 46;
                break;
        
            case ('Q'):
                tile = 48;
                break;

            case ('X'):
                tile = 50;
                break;

            case ('Z'):
                tile = 52;
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
    set_banked_bkg_data(186, 68, guard_text_data,3);
    set_banked_bkg_tiles(0,2, 8, 10, guard_text_map,3);

    //set elf right
    set_banked_bkg_data(58, 54, elf_text_data,3);
    set_banked_bkg_tiles(12,3, 8, 9, elf_text_map_left,3);

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

    set_text(dialogueIndex+sceneTextOffset[dialogueSceneIndex],0);
    
    ++dialogueIndex;
}

void setupTextBox(){
    for (uchar i = 0; i < 20; ++i){
        set_bkg_tile_xy(i,11,0);
    }
    set_banked_bkg_data(0, 14, TextBox, 3);
    set_banked_bkg_tiles(0, 12, 20, 6, TextBoxMap, 3);

    set_banked_bkg_data(128, 46, Letters, 2); //letters. 46 tiles.  23 letters
    set_banked_bkg_data(14, 20, Numbers, 3); //numbers. 20 tiles. 10 numbers
    set_banked_bkg_data(34, 12, Symbols, 3); //symbols. 12 tiles. 6 symbols
    set_banked_bkg_data(46, 8, Letters_Extra, 3); //extra letters. 8 tiles. 4 letters
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
