#include <gb/gb.h>
#include <gb/cgb.h>
#include "graphics/2x2tiles.h"
#include "graphics/2x2tiles.c"
#include "graphics/Letters.h"
#include "graphics/Letters.c"
#include "graphics/palletes.c"
#include "graphics/Sprites.h"
#include "graphics/Sprites.c"

typedef unsigned char uchar;

#define FIRST_TILE_OFFSET_2x2 12

#define HOUSE 0
#define CAVE 1
#define CHEST 2
#define TREE 3
#define FENCE 4
#define GRASS 5
#define PATH 6
//WALL WATER ROCK FOREST BRIDGE

#define START 7
#define END 8

#define NUM_TILES (END + 1)

#define CURSOR1 13
#define CURSOR2 14

const uchar palleteTable[NUM_TILES] = {
    2, 3, 2, 1,
    2, 1, 1, 0, 0
};

#define TILEMAP_START 0x9800
#define WIN_TILEMAP_START 0x9C00

const uchar* displayTexts[NUM_TILES] = {
    "HOUSE ", "CAVE  ", "CHEST ", "TREE  ",
    "FENCE ", "GRASS ", "PATH  ", "START ", "END   "
};

#define WIDTH 12
#define HEIGHT 12

const uchar MAP[12][12] = {
    {HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, PATH, CAVE, FENCE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, GRASS, GRASS},
    {HOUSE, GRASS, GRASS, GRASS, CAVE, CHEST, GRASS, GRASS, HOUSE, PATH, GRASS, GRASS},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, START, END},
    {HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, PATH, TREE, TREE},
    {HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, PATH, TREE, TREE},
    {HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, CAVE, CHEST, GRASS, GRASS, HOUSE, PATH, GRASS, GRASS}
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
    set_bkg_palette(0, 8, colors);
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

void setup_background() {
    set_bkg_data(48, NUM_TILES * 4, Tiles); //tiles.  15 big tiles, 60 small tiles
    set_bkg_data(0, 46, Letters); //letters. 46 tiles.  23 letters

    volatile uchar *tilemap = (uchar *)TILEMAP_START;
    for (uchar r = 0; r < HEIGHT * 2; r++) {
        for (uchar c = 0; c < WIDTH * 2; c++) {
            uchar map = (MAP[r/2][c/2] + FIRST_TILE_OFFSET_2x2)*4;
            uchar value = map + (r&1) + (c&1)*2;
            tilemap[r*32 + c] = value;
        }
    }
}

uchar cursorX = 0, cursorY = 0, cameraX = 0, cameraY = 0;

#define display_bigsprite(slot, tile)\
    set_sprite_tile((slot)*4, (tile)*4);\
    set_sprite_tile((slot)*4+1, (tile)*4+1);\
    set_sprite_tile((slot)*4+2, (tile)*4+2);\
    set_sprite_tile((slot)*4+3, (tile)*4+3);

#define move_bigsprite(slot, x, y)\
    move_sprite((slot)*4, (x), (y));\
    move_sprite((slot)*4+1, (x), (y)+8);\
    move_sprite((slot)*4+2, (x)+8, (y));\
    move_sprite((slot)*4+3, (x)+8, (y)+8);

void move_cursor() {
    static uchar cursorTimer = 0;

    cursorTimer++;
    if (cursorTimer == 50) {
        cursorTimer = 0;
        display_bigsprite(0, 0);
    } else if (cursorTimer == 25) {
        display_bigsprite(0, 1);
    }

    move_bigsprite(0, (cursorX - cameraX)*16 + 8, (cursorY-cameraY)*16 + 32);
}

uchar joyTimer = 0;

void check_cursor_movement() {
    if (joyTimer > 0) {
        joyTimer--;
    } else {
        uchar joy = joypad();
        if (joy & J_LEFT) {
            if (cursorX > 0) {
                cursorX--;
            }
        } else if (joy & J_RIGHT) {
            if (cursorX < WIDTH - 1) {
                cursorX++;
            }
        } else if (joy & J_UP) {
            if (cursorY > 0) {
                cursorY--;
            }
        } else if (joy & J_DOWN) {
            if (cursorY < HEIGHT - 1) {
                cursorY++;
            }
        }
        if (joy != 0) {
            joyTimer = 10;
        }
    }
}

uchar target_scx = 0, target_scy = 0;
uchar scx = 0, scy = 0;

void update_camera() {
    if (cursorX < cameraX) {
        cameraX--;
    } else if (cursorX >= cameraX + 10) {
        cameraX++;
    }

    if (cursorY < cameraY) {
        cameraY--;
    } else if (cursorY >= cameraY + 8) {
        cameraY++;
    }

    target_scy = cameraY * 16;
    target_scx = cameraX * 16;

    if ((uchar)(SCY_REG + 16) < target_scy) {
        scy += 2;
    } else if ((uchar)(SCY_REG + 16) > target_scy) {
        scy -= 2;
    }
    if (SCX_REG < target_scx) {
        scx += 2;
    } else if (SCX_REG > target_scx) {
        scx -= 2;
    }
}

struct Character {
    uchar x;
    uchar y;
    uchar sprite;
};

#define CHARACTER_BIGTILE_START 2
#define BOSTON 0
#define MARIE 1

uchar *characterNames[3] = {
    "BOSTON",
    "MARIE ",
    NULL
};

struct Character characters[4];
uchar numCharacters;

void setup_characters() {
    numCharacters = 2;
    characters[0].x = 6 * 16;
    characters[0].y = 6 * 16;
    characters[0].sprite = BOSTON;
    display_bigsprite(1, CHARACTER_BIGTILE_START + BOSTON * 2);

    characters[1].x = 7 * 16;
    characters[1].y = 7 * 16;
    characters[1].sprite = MARIE * 2;
    display_bigsprite(2, CHARACTER_BIGTILE_START + MARIE * 2);
}

#define CHARACTER_ANIMATION_DELAY  15

uchar characterAnimationTimer = CHARACTER_ANIMATION_DELAY;

void update_characters() {
    for (uchar i = 0; i < numCharacters; i++) {
        move_bigsprite(i + 1, characters[i].x - scx + 8, characters[i].y - scy + 16);
    }

    characterAnimationTimer--;
    if (characterAnimationTimer == 0) {
        characterAnimationTimer = CHARACTER_ANIMATION_DELAY;
        for (uchar i = 0; i < numCharacters; i++) {
            characters[i].sprite ^= 1;
            display_bigsprite(i + 1, CHARACTER_BIGTILE_START + characters[i].sprite);
        }
    }
}

//this is 255 if we are not hovering over a character, otherwise it is the index of the character
uchar hoverCharacter = 255;

void update_gui() {
    if (hoverCharacter == 255) {
        uchar coord = MAP[cursorY][cursorX];
        uchar *text = (uchar *)displayTexts[coord];
        change_text(text);
    } else {
        change_text(characterNames[hoverCharacter]);
    }
}

void main() {
    wait_vbl_done();
    display_off();
    LCDC_REG = 0x00;

    vmemset((uchar *)WIN_TILEMAP_START, SPACE_LETTER, 32*32);

    setup_background_palletes();
    setup_background();
    change_text("      ");

    set_sprite_palette(0, 1, colors);
    set_sprite_prop(0, 0);

    set_sprite_data(0, 24, Sprites);
    display_bigsprite(0, 0);
    setup_characters();

    IE_REG = IEF_VBLANK;
    enable_interrupts();
    
    LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00;
    while (1) {
        //DURING FRAME:

        check_cursor_movement();
        update_camera();

        update_characters();
        hoverCharacter = 255;
        for (uchar i = 0; i < numCharacters; i++) {
            if (cursorX == characters[i].x / 16 && cursorY == characters[i].y / 16) {
                hoverCharacter = i;
                break;
            }
        }
        update_gui();

        __asm__("halt");

        //VBLANK:

        move_cursor();

        SCX_REG = scx;
        SCY_REG = scy;

        copy_window_buffer();
        //while (LY_REG != 0) ;
        LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_WINON;
        while (LY_REG != 16) ;
        LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_WINOFF;
    }
}