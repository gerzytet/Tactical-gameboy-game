#include <gb/gb.h>
#include <gb/cgb.h>
#include "common.h"
#include "graphics/TextBox.h"
#include "graphics/TextBox.c"
#include "graphics/TextBoxMap.h"
#include "graphics/TextBoxMap.c"

#define TILEMAP_START 0x9800
#define WIN_TILEMAP_START 0x9C00

/*const uchar* dialogueText[8] = {
    "THIS IS SAMPLE TEXT", "THAT PROBABLY","DOESN'T WORK","HOPEFULLY IT WILL", "WORK IN THE FUTURE",
    "THIS GAME WILL BE", "THE BEST GAME AT THE", "GAME EXPO SPR 2023"
};*/

const uchar* script[20] = {
    "MEET FREDRIK, A  ", "FIERCE WARRIOR  ", "WITH A STRONG   ", "REPUTATION,     ",
    "MARIE, A         ", "MYSTERIOUS WOMAN", "WITH HIDDEN     ", "POWERS,         ",
    "AND BOSTON, AN   ", "EX-SOLDIER WITH ", "A POWERFUL      ", "MACHINE GUN.    ",
    "YOU WILL HAVE TO ", "TRAVEL TO       ", "DISTANT LANDS   ", "AND OVERCOME    ",
    "MANY CHALLENGES  ", "ON YOUR QUEST TO", "OVERCOME THE    ", "FORCES OF EVIL. "
};

const uchar* dialogueCharNames[3] = {"FREDRIK", "MARIE", "BOSTON"};

const uchar sceneTextLength[12] = {10,5,5,5,5,5,5,5,5,5,5,5};
const uchar imageLeft[12] = {5,5,5,5,5};
const uchar imageRight[12] = {5,5,5,5,5};

uchar dialogueIndex = 0;

void set_text(const uchar *textLine1, const uchar *textLine2 ,uchar charNameIndex){
    if (textLine1 == NULL) {
        return;
    }
    volatile uchar *tilemap = (uchar *)TILEMAP_START;
    static uchar tile;
    
    //todo: character name
    //set name dialogueCharNames[charNameIndex]
    for (uchar i = 0; i < 16; ++i){
        if (textLine1[i] == ' ') {
            tile = SPACE_LETTER + 14;
        } else {
            tile = letter_table[textLine1[i] - 'A']+ 14;
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
        if (textLine2[i] == ' ') {
            tile = SPACE_LETTER + 14;
        } else {
            tile = letter_table[textLine2[i] - 'A'] + 14;
        }
        tilemap[(i+482)] = tile;
        tile++;
        tilemap[(i+514)] = tile;
        wait_vbl_done();
    }

    return;
}

//do later
void set_char_sprite(uchar charSpriteIndex, uchar position){
    return;
}

//Advance the text after pressing the A Button
void advance_text(){
    if (dialogueIndex == 0 || imageLeft[dialogueIndex-1] != imageLeft[dialogueIndex-1]){
        set_char_sprite(imageLeft[dialogueIndex], 1);
    }
    if (dialogueIndex == 0 || imageRight[dialogueIndex-1] != imageRight[dialogueIndex-1]){
        set_char_sprite(imageRight[dialogueIndex], 2);
    }

    set_text(script[2*dialogueIndex], script[2*dialogueIndex+1],0);//dialogueCharNames[dialogueIndex]);
    ++dialogueIndex;
}

void setupTextBox(){
    set_bkg_data(0, 14, TextBox);
    set_bkg_tiles(0, 12, 20, 6, TextBoxMap);

    set_bkg_data(14, 46, Letters); //letters. 46 tiles.  23 letters
    //todo set_bkg_data(0,46, Symbols);
    set_bkg_data(60, 20, Numbers); //numbers. 20 tiles. 10 numbers

    //hide "STORY" text
    for(int i = 0; i < 5; ++i){
        hide_sprite(i);
    }
}

//Initialize the dialogue scene
void play_scene(uchar index){
    //cls();
    set_bkg_palette(0, 1, colors);
    move_bkg(0,0);
    
    setupTextBox();
    //setup character art
    
    //intro anim

    advance_text();
    while (dialogueIndex < sceneTextLength[index] - 1){
        //DURING FRAME:
		joy_impulse = joy;
		joy = joypad();
		joy_impulse = ~joy_impulse & joy;
		
        if (joy_impulse & J_A){
            advance_text();
        }
        wait_vbl_done();
    }
    dialogueIndex = 0;
    
    //outro anim
}
