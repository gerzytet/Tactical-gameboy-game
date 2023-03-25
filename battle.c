#include <gb/gb.h>
#include <gb/cgb.h>
#include "common.h"
#include "leveldata.h"
#include "tile_definitions.h"

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

    //cls();
    HIDE_SPRITES;
    HIDE_BKG;
    HIDE_WIN;
    set_bkg_tiles(0, 0, 20, 18, blank_tile);
    set_win_tiles(0, 0, 20, 18, blank_tile);

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

   uchar result = 0;
    //attacker attacks
     entities[defender].health = (entities[defender].health >= 5) ? 
         entities[defender].health - 5 : 
         0;
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
    
    //draw the map again
    //might want to make this its own f'n
    /*wait_vbl_done();
    SCY_REG = 0;
    SCX_REG = 0;
    display_off();
    LCDC_REG = 0x00;
    init_bigsprites();

    vmemset((uchar *)WIN_TILEMAP_START, SPACE_LETTER, 32*32);

    setup_background_palletes();
    setup_background();

    setup_characters();
    setup_passable_matrix();
    setup_gui_textbox();
    change_text("      ");

    set_sprite_palette(0, 4, colors_objects);
    set_sprite_prop(0, 0);
    set_sprite_data(0, 40, Sprites);
    display_bigsprite(0, 0);

    add_VBL(vblank_routine);
    IE_REG = IEF_VBLANK;
    enable_interrupts();
    //finish draw the map again
    */
    return result;

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