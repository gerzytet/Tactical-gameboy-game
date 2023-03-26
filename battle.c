/*
@file battle.c
@author entire team
@date 3/22/2023
@brief Battle mechanics
*/


#include <gb/gb.h>
#include <gb/cgb.h>
#include "common.h"
#include "leveldata.h"
#include "tile_definitions.h"
#include "graphics/Battle_Arrow.h"
#include "map_window.c"

#define TILEMAP_START 0x9800
#define WIN_TILEMAP_START 0x9C00

//todo

uchar attacker = 0;
uchar defender = 0;

const unsigned char blank_tile[1] = {0x00};

//intro anim
/*void battleIntro() {

}
//outro anim
void battleOutro() {

}
//battle anim
void battleAnimation() {

}*/

uchar determineAdvantage() {
    //advantage type of space
    uchar attackerPriority = advantageTable[MAPS[mapIndex][entities[attacker].x*16][entities[attacker].y*16]];
    uchar defenderPriority = advantageTable[MAPS[mapIndex][entities[defender].x*16][entities[defender].y*16]];

    //0-10 advantage    

    if(attackerPriority > defenderPriority) {
        return 7;
    }
    else {
        return 3;
    }       
}

void set_attacker_image(uchar index){
    index = index;
    return;
}

void set_defender_image(uchar index){
    index = index;
    return;
}

//Create base functions and logic for battling. Pokemon battle style
/*
    fire emblem confirm battle
    cue movie with sequence of random moves bewteen characters

    Battle Layout:
    characters
    box with health and character names
    arrows
*/

uchar battle(uchar nAttacker, uchar nDefender) {
    attacker = nAttacker;
    defender = nDefender;

    if (attacker == defender || entities[attacker].party == entities[defender].party){
        return 0;
    }

    game_mode = MODE_BATTLE;

    LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG9C00 | LCDCF_OBJOFF | LCDCF_WIN9C00 | LCDCF_WINOFF | LCDCF_OBJ8;
    __asm__("halt");
    TURN_THE_DISPLAY_OFF_RIGHT_NOW_WITHOUT_THE_GBDK_NONSENSE_THAT_TRIES_TO_WAIT_FOR_VBLANK_BUT_USUALLY_JUST_HANGS;
    CRITICAL {
        vmemset((uchar *)WIN_TILEMAP_START, 128, 32*32); 

        VBK_REG = VBK_BANK_1;
        vmemset((uchar *)WIN_TILEMAP_START, 0b00001000, 32*32); 
        set_banked_bkg_data(129, 4, Battle_Arrow, 2);
        VBK_REG = VBK_BANK_0;    

        SCX_REG = 0;
        SCY_REG = 0;
        set_bkg_tile_xy(0,0,0x81);
        set_bkg_tile_xy(1,0,0x82);
        //set_bkg_tile_xy(0,1,0x83);
        set_bkg_tile_xy(1,1,0x84);
    }
    DISPLAY_ON;

    //vmemset((uchar *)TILEMAP_START, 128, 32*32);

    // cls();
    // HIDE_SPRITES;
    // HIDE_BKG;
    // HIDE_WIN;    

    //start battle scene    

    //call function to calculate advantage with uchar  
    //display arrow in top left            

    /*
    fire emblem confirm battle
    cue movie with sequence of random moves bewteen characters
    */

   // get attack drawing from patrick   

   uchar result = 0;
    //attacker attacks
     entities[defender].health = (entities[defender].health >= 5) ? 
         entities[defender].health - 5 : 0;
     //entities[defender].health -= 5;

    if (entities[defender].health <= 0) {        
        //remove from map        
        result = 2;
    }    

    //defender counters
    entities[attacker].health = (entities[attacker].health >= 8) ? 
        entities[attacker].health - 8 : 0;


    //entities[attacker].health -= 8;

    if (entities[attacker].health <= 0) {              
        //remove from map        
        result = 1;
    }

    __asm__("halt");
    while (1) {
        __asm__("halt");
        if (joy_impulse & J_A) {
            game_mode = MODE_MAP;

            TURN_THE_DISPLAY_OFF_RIGHT_NOW_WITHOUT_THE_GBDK_NONSENSE_THAT_TRIES_TO_WAIT_FOR_VBLANK_BUT_USUALLY_JUST_HANGS
            reset_window();
            DISPLAY_ON;
            
            return result;
        }
    }
    
    

    //battleOutro();

    //if (entities[defender].health == 0 || entities[defender].health > entities[defender].maxHealth){
    //    entities[defender].health = 0;
    //    //remove from map
    //    return 2;
    //}
    ////defender counters
    //entities[attacker].health -= 8;
    //if (entities[attacker].health <= 0 || entities[attacker].health > entities[attacker].maxHealth){
    //    entities[attacker].health == 0;
    //    //remove from map
    //    return 1;
    //}    
}