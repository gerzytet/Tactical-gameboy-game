/*
@file tactics.c
@author entire team
@date 3/22/2023
@brief Main driver code
*/

#include <gb/gb.h>
#include <gb/cgb.h>
#include "../music_includes/hUGEDriver.h"
#include "common.h"
#include "bigsprites.h"
#include "main_menu.h"
#include "leveldata.h"
#include "dialogue.h"
#include "options.h"
#include "credits.h"
#include "battle.h"
#include "multiplayer.h"
#include "map_window.h"
#include "map.h"
#include "banked_graphics.h"
/*#include "../audio/menu_bgm.h"
#include "../audio/battle_bgm.h"
#include "../audio/plains_bgm.h"
#include "../audio/forest_bgm.h"
#include "../audio/fortress_bgm.h"*/

//fixed width: 6 characters

#define NAME_LENGTH 6

//Including textbox tiles:
#define NUM_LETTERS 27

#define TILEMAP_START 0x9800
#define WIN_TILEMAP_START 0x9C00

void vblank_routine(){
    switch(game_mode){
        case(MODE_MAP):
            map_vblank_routine();
            break;
        case(MODE_MAIN_MENU):
            menu_vblank_routine();
            break;
        case(MODE_BATTLE):
            break;
    }
    if (game_mode == MODE_MAP && enemyMoveMode == enemyMoveLink){
        joy_impulse = joy;
        joy = remote_joypad();
        joy_impulse = ~joy_impulse & joy;
    }
    else {
        joy_impulse = joy;
        joy = joypad();
        joy_impulse = ~joy_impulse & joy;
    }
    return;
}

void save_game(){
    SaveData *saveData = (SaveData *)0xA000;
    saveData->lastMapCompleted = mapIndex; //fix to be more accurate
    for (int i = 0; i < 10; ++i){
        saveData->inventory[i] = 0; //fix to write inventory
    }
    for (int i = 0; i < 6; ++i){
        saveData->characterStats[i] = 0; //fix to pull from uncreated variables
    }
}

void load_game(){
    SaveData *saveData = (SaveData *)0xA000;
}

//Post game handling
void game_over(){
    if (winState == PLAYER_WON){
        //save_game();
        menu_option = 255;
        set_overlay_text("VICTORY   ", 10);
    }
    else if (winState == PLAYER_LOST){
        menu_option = 255; //go to main menu
        set_overlay_text("DEFEAT    ", 10);
    }

    VBK_REG = VBK_BANK_1;
    vmemset((volatile uchar *) TILEMAP_START, 0, 32 * 32);
    VBK_REG = VBK_BANK_0;

    winState = 0;
    HIDE_SPRITES;
    for (uchar i = 0; i < 32; ++i){
        for (uchar j = 0; j < 32; ++j){
            set_bkg_tile_xy(i,j,0);
        }
    }
}

//Initialze the map with parameters before map is generated
void play_map(uchar num){
    //todo: initialize map with params
    
    if (_is_GBA == GBA_DETECTED){
        add_VBL(vblank_routine);
    }
    
    mapIndex = num;
    //enemies

    winCondition = winCondition_global[num];
    play_game();
}

//Plays the Story Mode from start to finish
void start_story(uchar startFrom){
    enemyMoveMode = enemyMoveAuto;
    switch(startFrom){
        case (0):
            play_scene(0);
            play_scene(1);
            play_map(0);
            play_scene(2);
        case (1):
            play_scene(3);
            play_map(1);
            play_scene(4);
        case (2):
            play_scene(5);
            play_map(2);
            play_scene(6);
        case (3):
            play_scene(7);
            play_map(3);
            play_scene(8);
        case (4):
            play_scene(9);
            play_map(4);
            play_scene(10);
            play_scene(11);
            play_credits();
    }     
}

//extern const hUGESong_t forest_bgm;

void main() {
    //An uncompleted campaign exists
    //Do you wish to continue from the last save?
    //Y/N
    if (_is_GBA == GBA_NOT_DETECTED){
        add_VBL(vblank_routine);
    }
    IE_REG = IEF_VBLANK;
    enable_interrupts();
    
    NR52_REG = 0x80; //turns on channels
    NR51_REG = 0xFF; //select which channels to output sound
    NR50_REG = 0x77; //sets volume, max 0x77

    /*__critical {
        hUGE_init_banked(&main_bgm, 2);
        add_VBL(hUGE_dosound_banked);
    }*/

    /*__critical{
        hUGE_init(&menu_bgm);
        add_VBL(hUGE_dosound);
    }*/
    
    menu_option = 255;
    while (1){
        switch (menu_option){
            case 255:
                mainmenu();
                break;
            case 0:
                enemyMoveMode = enemyMoveAuto;
                play_game();
                break;
            case 1:
                start_story(0);
                break;
            case 2:
                multiplayer();
                break;
            case 3:
                options_menu();
                break;
        }
    }
}