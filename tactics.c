#include <gb/gb.h>
#include <gb/cgb.h>
#include "graphics/2x2tiles.h"
#include "graphics/2x2tiles.c"
#include "graphics/Letters.h"
#include "graphics/Letters.c"


typedef unsigned char uchar;

#define CHARACTER3 12
#define CHARACTER4 13
#define CHARACTER5 14
#define CHARACTER6 15

#define HOUSE 16
#define CAVE 17
#define CHEST 18
#define TREE 19
#define FENCE 20
#define GRASS 21
#define PATH 22
#define LETTER2_START 23
//WALL WATER ROCK FOREST BRIDGE

#define START 28
#define END 29
#define CURSOR1 30
#define CURSOR2 31



#define TILEMAP_START 0x9800

const uchar* displayTexts[30] = {
    "      ", "      ", "      ", "      ", "      ",
    "      ", "      ", "      ", "      ", "      ",
    "GUY   ", "GUY   ", "GUY   ", "GUY   ", "GUY   ",
    "GUY   ", "HOUSE ", "CAVE  ", "CHEST ", "TREE  ",
    "FENCE ", "GRASS ", "PATH  ", NULL, NULL,
    NULL, NULL, NULL, "START ", "END   "
};

#define WIDTH 12
#define HEIGHT 12

const uchar MAP[12][12] = {
    {HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, PATH, CAVE, FENCE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, CHARACTER3, CHARACTER4},
    {HOUSE, GRASS, GRASS, GRASS, CAVE, CHEST, GRASS, GRASS, HOUSE, PATH, CHARACTER5, CHARACTER6},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, PATH, TREE, TREE},
    {HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, PATH, TREE, TREE},
    {HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, CAVE, CHEST, GRASS, GRASS, HOUSE, PATH, CHARACTER5, CHARACTER6}
};

#define SPACE_LETTER 22 * 2

uchar letter_table[26] = {
    0, //a
    2, //b
    4, //c
    6, //d
    8, //e
    10, //f
    12, //g
    14, //h
    16, //i
    SPACE_LETTER, //j
    18, //k
    20, //l
    22, //m
    24, //n
    26, //o
    28, //p
    SPACE_LETTER, //q
    30, //r
    32, //s
    34, //t
    36, //u
    38, //v
    40, //w
    SPACE_LETTER, //x
    44, //y
    SPACE_LETTER //z
};

#define TEXT_OFFSET 1

void change_text(uchar *text) {
    if (text == NULL) {
        return;
    }
    volatile uchar *tilemap = (uchar *)TILEMAP_START;
    static uchar tile;
    tilemap += TEXT_OFFSET;
    for (int i = 0; i < 6; i++) {
        
        if (text[i] == ' ') {
            tile = SPACE_LETTER;
        } else {
            tile = letter_table[text[i] - 'A'];
        }
        tilemap[i] = tile;
        tile++;
        tilemap[i|32] = tile;
    }
}

void main() {
    wait_vbl_done();
    display_off();
    LCDC_REG = 0x00;
    set_bkg_data(0, 128, Tiles);
    set_bkg_data(0, 46, Letters); //letters part 1. 46 tiles.  23 letters

    volatile uchar *tilemap = (uchar *)TILEMAP_START;
    for (uchar r = 0; r < HEIGHT * 2; r++) {
        for (uchar c = 0; c < WIDTH * 2; c++) {
            uchar map = MAP[r/2][c/2]*4;
            uchar value = map + (r&1) + (c&1)*2;
            tilemap[r*32 + c + 64] = value;
        }
    }
    for (uchar r = 0; r < 2; r++) {
        for (uchar c = 0; c < WIDTH * 2; c++) {
            tilemap[r*32 + c] = SPACE_LETTER;
        }
    }
    set_sprite_data(0, 8, Tiles + (16 * CURSOR1 * 4));
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);

    change_text("FOREST");

    static uchar x = 0;
    static uchar y = 0;

    static uchar cursorTimer = 0;
    static uchar joyTimer = 0;

    static uchar cameraX = 0;
    static uchar cameraY = 0;

    //screen brightness
    BGP_REG = 0b11100100;

    LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON;
    while (1) {
        if (x < cameraX) {
            cameraX--;
        } else if (x >= cameraX + 10) {
            cameraX++;
        }

        if (y < cameraY) {
            cameraY--;
        } else if (y > cameraY + 7) {
            cameraY++;
        }

        SCY_REG = 0;
        SCX_REG = 0;

        cameraY *= 16;
        cameraX *= 16;

        while (LY_REG != 16) ;
        while (STAT_REG & 0x03 != 0) ;
        
        SCY_REG = cameraY;
        SCX_REG = cameraX;
        cameraY /= 16;
        cameraX /= 16;

        wait_vbl_done();

        move_sprite(0, (x - cameraX)*16 + 8, (y-cameraY)*16 + 32);
        move_sprite(1, (x - cameraX)*16 + 8,  (y-cameraY)*16 + 40);
        move_sprite(2, (x - cameraX)*16 + 16, (y-cameraY)*16 + 32);
        move_sprite(3, (x - cameraX)*16 + 16, (y-cameraY)*16 + 40);

        cursorTimer++;
        if (cursorTimer == 30) {
            cursorTimer = 0;
            set_sprite_tile(0, 0);
            set_sprite_tile(1, 1);
            set_sprite_tile(2, 2);
            set_sprite_tile(3, 3);
        } else if (cursorTimer == 15) {
            set_sprite_tile(0, 4);
            set_sprite_tile(1, 5);
            set_sprite_tile(2, 6);
            set_sprite_tile(3, 7);
        }
        uchar coord = MAP[y][x];
        uchar *text = (uchar *)displayTexts[coord];
        change_text(text);

        if (joyTimer > 0) {
            joyTimer--;
            continue;
        } 

        uchar joy = joypad();
        if (joy & J_LEFT) {
            if (x > 0) {
                x--;
            }
        } else if (joy & J_RIGHT) {
            if (x < WIDTH - 1) {
                x++;
            }
        } else if (joy & J_UP) {
            if (y > 0) {
                y--;
            }
        } else if (joy & J_DOWN) {
            if (y < HEIGHT - 1) {
                y++;
            }
        }
        if (joy != 0) {
            joyTimer = 10;
        }
    }
}