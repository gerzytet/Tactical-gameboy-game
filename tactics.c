/*
@file tactics.c
@author entire team
@date 3/22/2023
@brief Main driver code
*/

#include <gb/gb.h>
#include <gb/cgb.h>
#include "common.h"
#include "bigsprites.h"
#include <stdio.h>
#include "main_menu.c"
#include "leveldata.h"
#include "dialogue.c"
#include "options.c"
#include "credits.c"
#include "battle.c"
#include "multiplayer.c"
#include "map_window.c"
#include "map.c"

//fixed width: 6 characters

#define NAME_LENGTH 6

//Including textbox tiles:
#define NUM_LETTERS 27

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
    joy_impulse = joy;
    joy = joypad();
    joy_impulse = ~joy_impulse & joy;
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
        save_game();
    }
    else if (winState == PLAYER_LOST){
        menu_option = 255; //go to main menu
    }
}

//Initialze the map with parameters before map is generated
void play_map(uchar num){
    //todo: initialize map with params
    mapIndex = num;
    //enemies

    winCondition = winCondition_global[num];
    play_game();
}

//Plays the Story Mode from start to finish
void start_story(uchar startFrom){
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

void main() {
    //An uncompleted campaign exists
    //Do you wish to continue from the last save?
    //Y/N

    add_VBL(vblank_routine);
    IE_REG = IEF_VBLANK;
    enable_interrupts();

    if (_is_GBA == GBA_DETECTED){
        printf("GBA detected\n");
    }
    menu_option = 255;
    while (1){
        switch (menu_option){
            case 255:
                mainmenu();
                break;
            case 0:
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