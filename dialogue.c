#include <gb/gb.h>
#include <gb/cgb.h>
#include "common.h"
#include "graphics/TextBox.h"
#include "graphics/TextBox.c"
#include "graphics/TextBoxMap.h"
#include "graphics/TextBoxMap.c"

/*const uchar* dialogueText[8] = {
    "THIS IS SAMPLE TEXT", "THAT PROBABLY","DOESN'T WORK","HOPEFULLY IT WILL", "WORK IN THE FUTURE",
    "THIS GAME WILL BE", "THE BEST GAME AT THE", "GAME EXPO SPR 2023"
};*/

const uchar* dialogueCharNames[3] = {"FREDRIK", "MARIE", "BOSTON"};

const uchar sceneTextLength[12] = {5,5,5,5,5,5,5,5,5,5,5,5};
const uchar imageLeft[12] = {5,5,5,5,5};
const uchar imageRight[12] = {5,5,5,5,5};

uchar dialogueIndex = 0;

void set_text(const uchar *text, uchar charNameIndex){
    //set name dialogueCharNames[charNameIndex]
    return;
}

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

    //set_text("TEST", dialogueCharNames[dialogueIndex]);
}

//Initialize the dialogue scene
void play_scene(uchar index){
    set_bkg_palette(0, 1, colors);
    set_bkg_data(0, 6, TextBox);
    set_bkg_tiles(0, 12, 20, 6, TextBoxMap);
    move_bkg(0,0);
    
    //setup character art
    
    //intro anim

    while (dialogueIndex < sceneTextLength[index]){
        if (joy_impulse & J_A){
            advance_text();
        }
    }
    
    //outro anim
}
