#ifndef MAP_WINDOW_C
#define MAP_WINDOW_C

#include "common.h"
#include <gb/gb.h>
#include <gb/cgb.h>

uchar windowBuffer[2][32];

#define WIN_TILEMAP_START 0x9C00

const uchar number_table[10] = {
    56, //0
    58, //1
    60, //2
    62, //3
    64, //4
    66, //5
    68, //6
    70, //7
    72, //8
    74 //9
};

void add_turn_gui() {
    static uchar ones_digit = 0;
    static uchar tens_digit = 0;

    ones_digit++;
    if (ones_digit >= 10) {
        ones_digit -= 10;
        tens_digit++;
        if (tens_digit >= 10) {
            tens_digit -= 10;
        }
    }
    
    const uchar *text;
    text = "TURN";

    volatile uchar *tilemap = &windowBuffer[0][0];
    static uchar tile;
    for (uchar i = 0; i < 4; i++) {
        if (text[i] == ' ') {
            tile = (uchar)(SPACE_LETTER+128);
        } else {
            tile = letter_table[text[i] - 'A']+128;
        }
        tilemap[i+13] = tile;
        tile++;
        tilemap[i+13|32] = tile;
    }

    //then print the turn #
    if (tens_digit == 0) {
        tile = (uchar)(SPACE_LETTER+128);
    } else {
        tile = number_table[tens_digit];
    }
    tilemap[17] = tile;
    tile++;
    tilemap[17|32] = tile;
    
    tile = number_table[ones_digit];
    tilemap[18] = tile;
    tile++;
    tilemap[18|32] = tile;
}

//number of tiles from the left the text should be displayed
#define TEXT_OFFSET 1


void change_text(const uchar *text) {
    if (text == NULL) {
        return;
    }
    volatile uchar *tilemap = &windowBuffer[0][0];
    tilemap += TEXT_OFFSET;
    static uchar tile;
    for (uchar i = 0; i < 6; i++) {
        if (text[i] == ' ') {
            tile = (uchar)(SPACE_LETTER+128);
        } else {
            tile = letter_table[text[i] - 'A']+128;
        }
        tilemap[i] = tile;
        tile++;
        tilemap[i|32] = tile;
    }
}

void set_overlay_text(const uchar *text, uchar length) {
    length = length; //use this to center text
    if (text == NULL) {
        return;
    }
    volatile uchar *tilemap = &windowBuffer[0][0];
    volatile uchar *tilemap = (uchar *)WIN_TILEMAP_START;
    tilemap += TEXT_OFFSET;
    static uchar tile;
    for (uchar i = 0; i < 10; i++) {
        if (text[i] == ' ') {
            tile = (uchar)(SPACE_LETTER+128);
        } else {
            tile = letter_table[text[i] - 'A']+128;
        }
        tilemap[i+192] = tile;
        tile++;
        tilemap[i|32+192] = tile;
    }
    showOverlayText = 1;
    for (uchar i = 0; i < 5; ++i){
        for (uchar j = 0; j < 60; ++j){
            wait_vbl_done();
        }
    }
    showOverlayText = 0;
}

#define HFLIP 0b00100000
#define VFLIP 0b01000000

#define HEALTHBAR_START 7
#define HEALTHBAR_END 12

#define HEALTHBAR_PAL 5

#define HEALTHCOL0 TEXTBOX_MIDDLE
#define HEALTHCOL1 48
#define HEALTHCOL2 49
#define HEALTHCOL1REV 50
#define HEALTH0 51
#define HEALTH1 52
#define HEALTH2 53
#define HEALTH3 54
#define HEALTH4 55

//unit: small tiles
#define TEXTBOX_END 46
#define TEXTBOX_MIDDLE 47


void setup_gui_textbox() {
    volatile uchar *tilemap = (uchar *) WIN_TILEMAP_START;
    tilemap[0] = TEXTBOX_END;
    tilemap[0 + 32] = TEXTBOX_END;
    tilemap[HEALTHBAR_START] = TEXTBOX_MIDDLE;
    tilemap[HEALTHBAR_START | 32] = TEXTBOX_MIDDLE;
    tilemap[HEALTHBAR_END] = TEXTBOX_MIDDLE;
    tilemap[HEALTHBAR_END | 32] = TEXTBOX_MIDDLE;
    tilemap[19] = TEXTBOX_END;
    tilemap[19 + 32] = TEXTBOX_END;

    for (uchar i = HEALTHBAR_START + 1; i < HEALTHBAR_END; i++) {
        tilemap[i] = HEALTH0;
        tilemap[i | 32] = HEALTH0;
    }

    VBK_REG = VBK_BANK_1;
    tilemap[0 + 32] = VFLIP;

    for (uchar i = HEALTHBAR_START; i <= HEALTHBAR_END; i++) {
        tilemap[i | 32] = VFLIP;
        tilemap[i] |= HEALTHBAR_PAL;
        tilemap[i | 32] |= HEALTHBAR_PAL;
    }

    tilemap[HEALTHBAR_END | 32] |= HFLIP;
    tilemap[HEALTHBAR_END] |= HFLIP;

    tilemap[19] = HFLIP;
    tilemap[19 | 32] = VFLIP | HFLIP;
    VBK_REG = VBK_BANK_0;
}

void reset_window() {
    CRITICAL {
        VBK_REG = VBK_BANK_1;
        vmemset((volatile uchar *) WIN_TILEMAP_START, 0, 32 * 2);
        VBK_REG = VBK_BANK_0;
        vmemset((uchar *)WIN_TILEMAP_START, (uchar)(SPACE_LETTER+128), 32*2);

        setup_gui_textbox();
    }
}

//health level is a number from 0 to 20
void render_health(uchar healthLevel) {
    volatile uchar *tilemap = &windowBuffer[0][0];
    uchar tile;
    if (healthLevel > 2) {
        tile = HEALTHCOL2;
        healthLevel -= 2;
    } else {
        tile = HEALTHCOL0 + healthLevel;
        healthLevel = 0;
    }
    tilemap[HEALTHBAR_START] = tile;
    tilemap[HEALTHBAR_START | 32] = tile;

    for (uchar i = HEALTHBAR_START+1; i < HEALTHBAR_END; i++) {
        if (healthLevel > 4) {
            tile = HEALTH4;
            healthLevel -= 4;
        } else {
            tile = HEALTH0 + healthLevel;
            healthLevel = 0;
        }
        tilemap[i] = tile;
        tilemap[i | 32] = tile;
    }
    
    if (healthLevel == 0) {
        tile = HEALTHCOL0;
    } else if (healthLevel == 1) {
        tile = HEALTHCOL1REV;
    } else {
        tile = HEALTHCOL2;
    }
    tilemap[HEALTHBAR_END] = tile;
    tilemap[HEALTHBAR_END | 32] = tile;
}

void setup_window() {
    vmemset((uchar *)WIN_TILEMAP_START, (uchar)(SPACE_LETTER+128), 32*32);
}

#endif