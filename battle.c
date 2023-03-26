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
#include "graphics/Battle_Arrow.c"

#define TILEMAP_START 0x9800

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

    LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJOFF | LCDCF_WIN9C00 | LCDCF_WINOFF | LCDCF_OBJ8;

    vmemset((uchar *)TILEMAP_START, 128, 32*32);

    

    // cls();
    // HIDE_SPRITES;
    // HIDE_BKG;
    // HIDE_WIN;    

    //start battle scene
    //battleIntro();    

    //function to calculate advantage with uchar  
    //display arrow in top left
        
    //todo: fix to not go negative        
    //todo: edit the algorithm    

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

    while (1) {
        if (joy_impulse & J_A) {
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