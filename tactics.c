#include <gb/gb.h>
#include <gb/cgb.h>
#include "graphics/2x2tiles.h"
#include "graphics/2x2tiles.c"
#include "graphics/Letters.h"
#include "graphics/Letters.c"
#include "graphics/palletes.c"

typedef unsigned char uchar;

#define FIRST_TILE_OFFSET_2x2 12
#define CHARACTER3 0
#define CHARACTER4 1
#define CHARACTER5 2
#define CHARACTER6 3

#define HOUSE 4
#define CAVE 5
#define CHEST 6
#define TREE 7
#define FENCE 8
#define GRASS 9
#define PATH 10
//WALL WATER ROCK FOREST BRIDGE

#define START 11
#define END 12
#define CURSOR1 13
#define CURSOR2 14

const uchar palleteTable[13] = {
    0, 0, 0, 0,
    2, 3, 2, 1,
    2, 1, 1, 0, 0
};

#define TILEMAP_START 0x9800
#define WIN_TILEMAP_START 0x9C00

const uchar* displayTexts[13] = {
    "GUY   ", "GUY   ", "GUY   ",
    "GUY   ", "HOUSE ", "CAVE  ", "CHEST ", "TREE  ",
    "FENCE ", "GRASS ", "PATH  ", "START ", "END   "
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
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, START, END},
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
    42, //y
    SPACE_LETTER //z
};

#define TEXT_OFFSET 2

uchar windowBuffer[2][32];

void change_text(uchar *text) {
    if (text == NULL) {
        return;
    }
    volatile uchar *tilemap = &windowBuffer[0][0];
    static uchar tile;
    for (uchar i = 0; i < 6; i++) {
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

// void copy_window_buffer() {
//    volatile uchar *tilemap = (uchar *)WIN_TILEMAP_START + TEXT_OFFSET;
//    for (uchar i = 0; i < 6; i++) {
//        tilemap[i] = windowBuffer[0][i];
//        tilemap[i|32] = windowBuffer[1][i];
//    }
// }

void setup_background_palletes() {
    VBK_REG = VBK_BANK_1;

    volatile uchar *tilemap = (uchar *)TILEMAP_START;
    for (uchar r = 0; r < HEIGHT * 2; r++) {
        for (uchar c = 0; c < WIDTH * 2; c++) {
            uchar tile = MAP[r/2][c/2];
            uchar pal = palleteTable[tile];
            tilemap[r*32 + c] = pal;
        }
    }

    VBK_REG = VBK_BANK_0;
}

extern void copy_window_buffer();

void main() {
    wait_vbl_done();
    display_off();
    LCDC_REG = 0x00;
    set_bkg_data(48, 60, Tiles); //tiles.  15 big tiles, 60 small tiles
    set_bkg_data(0, 46, Letters); //letters. 46 tiles.  23 letters

    volatile uchar *tilemap = (uchar *)TILEMAP_START;
    for (uchar r = 0; r < HEIGHT * 2; r++) {
        for (uchar c = 0; c < WIDTH * 2; c++) {
            uchar map = (MAP[r/2][c/2] + FIRST_TILE_OFFSET_2x2)*4;
            uchar value = map + (r&1) + (c&1)*2;
            tilemap[r*32 + c] = value;
        }
    }
    set_sprite_data(0, 8, Tiles + (CURSOR1 * 16 * 4));
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);

    vmemset((uchar *)WIN_TILEMAP_START, SPACE_LETTER, 32*32);

    change_text("FOREST");

    static uchar x = 0;
    static uchar y = 0;

    static uchar cursorTimer = 0;
    static uchar joyTimer = 0;

    static uchar cameraX = 0;
    static uchar cameraY = 0;

    //screen brightness
    //BGP_REG = 0b11100100;

    setup_background_palletes();

    set_bkg_palette(0, 8, colors);
    set_sprite_palette(0, 1, colors);
    set_sprite_prop(0, 0);

    IE_REG = IEF_VBLANK;
    enable_interrupts();
    
    LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00;
    while (1) {
        //DURING FRAME:
        if (joyTimer > 0) {
            joyTimer--;
        } else {
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

        uchar coord = MAP[y][x];
        uchar *text = (uchar *)displayTexts[coord];
        change_text(text);

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

        static uchar target_scy;
        target_scy = cameraY * 16;
        static uchar target_scx;
        target_scx = cameraX * 16;

        __asm__("halt");

        //VBLANK:

        if ((uchar)(SCY_REG + 16) < target_scy) {
            SCY_REG += 2;
        } else if ((uchar)(SCY_REG + 16) > target_scy) {
            SCY_REG -= 2;
        }
        if (SCX_REG < target_scx) {
            SCX_REG += 2;
        } else if (SCX_REG > target_scx) {
            SCX_REG -= 2;
        }

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

        copy_window_buffer();
        //while (LY_REG != 0) ;
        LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_WINON;
        while (LY_REG != 16) ;
        LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_WINOFF;
    }
}