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
    4, 3, 2, 1,
    3, 1, 3, 0, 0
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

//unit: bigtiles
uchar cursorX = 0, cursorY = 0, cameraX = 0, cameraY = 0;

#define display_bigsprite(slot, tile)\
    set_sprite_tile((slot)*2, (tile)*4);\
    set_sprite_tile((slot)*2+1, (tile)*4+2);\

#define move_bigsprite(slot, x, y)\
    move_sprite((slot)*2, (x), (y));\
    move_sprite((slot)*2+1, (x)+8, (y));\

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
uchar joy = 0;
uchar joy_impulse = 0;

void check_cursor_movement() {
    if (joyTimer > 0) {
        joyTimer--;
    } else {
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
#define CHARACTER_SPRITE_SLOT_START 2
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
    display_bigsprite(CHARACTER_SPRITE_SLOT_START, CHARACTER_BIGTILE_START + BOSTON * 2);

    characters[1].x = 7 * 16;
    characters[1].y = 7 * 16;
    characters[1].sprite = MARIE * 2;
    display_bigsprite(CHARACTER_SPRITE_SLOT_START + 1, CHARACTER_BIGTILE_START + MARIE * 2);
}

#define CHARACTER_ANIMATION_DELAY  15

uchar characterAnimationTimer = CHARACTER_ANIMATION_DELAY;

void update_characters() {
    for (uchar i = 0; i < numCharacters; i++) {
        move_bigsprite(i + CHARACTER_SPRITE_SLOT_START, characters[i].x - scx + 8, characters[i].y - scy + 16);
    }

    characterAnimationTimer--;
    if (characterAnimationTimer == 0) {
        characterAnimationTimer = CHARACTER_ANIMATION_DELAY;
        for (uchar i = 0; i < numCharacters; i++) {
            characters[i].sprite ^= 1;
            display_bigsprite(i + CHARACTER_SPRITE_SLOT_START, CHARACTER_BIGTILE_START + characters[i].sprite);
        }
    }
}

#define STATE_LOOK 0
#define STATE_CHOOSE_MOVE 1
#define STATE_MOVE 2

uchar state = STATE_LOOK;

//this is 255 if we are not hovering over a character, otherwise it is the index of the character
uchar hoverCharacter = 255;
uchar secondCursorX = 0, secondCursorY = 0;
uchar selectedCharacter = 255;

void update_hover_character() {
    hoverCharacter = 255;
    for (uchar i = 0; i < numCharacters; i++) {
        if (cursorX == characters[i].x / 16 && cursorY == characters[i].y / 16) {
            hoverCharacter = i;
            break;
        }
    }
}

void update_gui() {
    if (hoverCharacter == 255) {
        uchar coord = MAP[cursorY][cursorX];
        uchar *text = (uchar *)displayTexts[coord];
        change_text(text);
    } else {
        change_text(characterNames[hoverCharacter]);
    }
}

void check_enter_move_mode() {
    if (joy_impulse & J_A) {
        if (hoverCharacter != 255) {
            state = STATE_CHOOSE_MOVE;
            secondCursorX = cursorX;
            secondCursorY = cursorY;
            display_bigsprite(1, 0);
            selectedCharacter = hoverCharacter;
        }
    }
}

void check_exit_move_mode() {
    if (joy & J_B) {
        state = STATE_LOOK;
        move_bigsprite(1, 0, 0);
    }
}

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

//255 = no traceback
uchar traceback[16][16];

//1 bit for each tile
uchar visited[16][2];

uchar xQueue[256];
uchar yQueue[256];

uchar diff = 0;

const uchar shiftTable[16] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};

void pathfind(uchar startX, uchar startY, uchar endX, uchar endY, uchar dist) {
    for (uchar i = 0; i < 16; i++) {
        visited[i][0] = 0;
        visited[i][1] = 0;
    }
    static uchar queueStart;
    queueStart = 0;
    static uchar queueEnd;
    queueEnd = 2;
    static uchar myDist;
    myDist = dist;
    xQueue[0] = startX;
    yQueue[0] = startY;
    xQueue[1] = 255;
    yQueue[1] = 255;
    traceback[startY][startX] = 255;
    traceback[endY][endX] = 255;
    //255 in the queue means we are done with this level of the queue, so decrement the dist
    while (1) {
        static uchar x;
        x = xQueue[queueStart];
        queueStart++;
        if (x == 255) {
            myDist--;
            if (myDist == 255) {
                break;
            }
            xQueue[queueEnd] = 255;
            yQueue[queueEnd] = 255;
            queueEnd++;
            continue;
        }

        if (queueEnd == queueStart) {
            return;
        }

        static uchar y;
        y = yQueue[queueStart - 1];

        visited[y][x/8] |= shiftTable[x];
        
        diff = 0;
        if (x > endX) {
            diff = x - endX;
        } else {
            diff = endX - x;
        }

        if (y > endY) {
            diff += y - endY;
        } else {
            diff += endY - y;
        }

        if (diff > myDist) {
            continue;
        }

        if (diff == 0) {
            return;
        }

        #define EXPLORE_HORIZ(DIR) if (~x & 16 && ~visited[y][x/8] & shiftTable[x]) {\
            traceback[y][x] = DIR;\
            xQueue[queueEnd] = x;\
            yQueue[queueEnd] = y;\
            queueEnd++;\
        }

        x++;
        EXPLORE_HORIZ(WEST);

        x -= 2;
        EXPLORE_HORIZ(EAST);

        x++;

#define EXPLORE_VERT(DIR) if (~y & 16 && ~visited[y][x/8] & shiftTable[x]) {\
    traceback[y][x] = DIR;\
    xQueue[queueEnd] = x;\
    yQueue[queueEnd] = y;\
    queueEnd++;\
}

        y++;
        EXPLORE_VERT(NORTH);

        y -= 2;
        EXPLORE_VERT(SOUTH);
    }
}

inline void render_second_cursor() {
    move_bigsprite(1, secondCursorX * 16 - scx + 8, secondCursorY * 16 - scy + 16);
}

void vblank_routine() {
    move_cursor();

    SCX_REG = scx;
    SCY_REG = scy;

    copy_window_buffer();
    //while (LY_REG != 0) ;
    LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_WINON | LCDCF_OBJ16;
    while (LY_REG != 16) ;
    LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_WINOFF | LCDCF_OBJ16;
}

void check_confirm_move() {
    if (joy & J_A) {
        uchar x = cursorX;
        uchar y = cursorY;
        if (hoverCharacter != 255) {
            return;
        }

        pathfind(secondCursorX, secondCursorY, cursorX, cursorY, 5);
        for (uchar i = 0; i < 10; i++) {
            if (x == secondCursorX && y == secondCursorY) {
                state = STATE_MOVE;
                return;
            }
            if (traceback[y][x] == 255) {
                return;
            }
            if (traceback[y][x] == NORTH) {
                y--;
            } else if (traceback[y][x] == SOUTH) {
                y++;
            } else if (traceback[y][x] == EAST) {
                x++;
            } else if (traceback[y][x] == WEST) {
                x--;
            }
        }
    }
    
}

void move_character_after_pathfinding() {
    characters[selectedCharacter].x = cursorX * 16;
    characters[selectedCharacter].y = cursorY * 16;
    state = STATE_LOOK;
    move_bigsprite(1, 0, 0);
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

    add_VBL(vblank_routine);
    IE_REG = IEF_VBLANK;
    enable_interrupts();
    
    LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_OBJ16;
    while (1) {
        //DURING FRAME:

        joy_impulse = joy;
        joy = joypad();
        joy_impulse = ~joy_impulse & joy;
        if (state == STATE_LOOK || state == STATE_CHOOSE_MOVE) {
            check_cursor_movement();
        }
        update_camera();

        update_characters();
        update_hover_character();
        update_gui();

        if (state == STATE_LOOK) {
            check_enter_move_mode();
        } else if (state == STATE_CHOOSE_MOVE) {
            render_second_cursor();
            check_confirm_move();
            check_exit_move_mode();
        } else if (state == STATE_MOVE) {
            move_character_after_pathfinding();
        }

        __asm__("halt");

        
    }
}