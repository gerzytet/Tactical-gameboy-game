#include <gb/gb.h>
#include <gb/cgb.h>
#include "common.h"
#include "graphics/2x2tiles.h"
#include "graphics/2x2tiles.c"
#include "graphics/Letters.h"
#include "graphics/Letters.c"
#include "graphics/palletes.c"
#include "graphics/Sprites.h"
#include "graphics/Sprites.c"
#include "graphics/Top_textbox.h"
#include "graphics/Top_textbox.c"
#include "pathfinding.c"
#include "bigsprites.h"

#define CURSOR1 13
#define CURSOR2 14

const uchar palleteTable[NUM_TILES] = {
    4, 3, 2, 1,
    3, 1, 3, 0, 0
};

#define TILEMAP_START 0x9800
#define WIN_TILEMAP_START 0x9C00

//fixed width: 6 characters
const uchar* displayTexts[NUM_TILES] = {
    "HOUSE ", "CAVE  ", "CHEST ", "TREE  ",
    "FENCE ", "GRASS ", "PATH  ", "START ", "END   "
};

#define SPACE_LETTER 22 * 2

#define NAME_LENGTH 6

#define PARTY_FRIEND 0
#define PARTY_ENEMY 1
#define PARTY_OTHER 2

uchar party_current;
uchar turn_cntr;

uchar letter_table[36] = {
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
    SPACE_LETTER, //z
    44, //0
    46, //1
    48, //2
    50, //3
    52, //4
    54, //5
    56, //6
    58, //7
    60, //8
    62 //9
};

//number of tiles from the left the text should be displayed
#define TEXT_OFFSET 1

uchar windowBuffer[2][32];

void change_text(const uchar *text) {
    if (text == NULL) {
        return;
    }
    volatile uchar *tilemap = &windowBuffer[0][0];
    tilemap += TEXT_OFFSET;
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

void add_turn(){
    ++turn_cntr;
    party_current = 0;
    
    const uchar *text;
    text = "TURN";

    volatile uchar *tilemap = &windowBuffer[0][0];
    static uchar tile;
    for (uchar i = 0; i < 4; i++) {
        if (text[i] == ' ') {
            tile = SPACE_LETTER;
        } else {
            tile = letter_table[text[i] - 'A'];
        }
        tilemap[i+13] = tile;
        tile++;
        tilemap[i+13|32] = tile;
    }

    //then print the turn #
    if (turn_cntr < 10) {
        tile = SPACE_LETTER;
    } else {
        tile = letter_table[turn_cntr/10 - '0' + 44];
    }
    tilemap[17] = tile;
    tile++;
    tilemap[17|32] = tile;
    
    tile = letter_table[turn_cntr%10 - '0' + 44];
    tilemap[18] = tile;
    tile++;
    tilemap[18|32] = tile;    
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

//Including textbox tiles!
#define NUM_LETTERS 25
#define TEXTBOX_END 23
#define TEXTBOX_MIDDLE 24

#define FIRST_TILE_OFFSET_2x2 (NUM_LETTERS + 1) / 2

void setup_background() {
    set_bkg_data(FIRST_TILE_OFFSET_2x2 * 4, NUM_TILES * 4, Tiles); //tiles.  15 big tiles, 60 small tiles
    set_bkg_data(0, 46, Letters); //letters. 46 tiles.  23 letters
    set_bkg_data(46, 4, Top_textbox);

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
uchar cursorX = 0, cursorY = 0;

//unit: pixels relative to top right of map (not actual SCX/SCY)
uchar target_scx = 0, target_scy = 0;

void move_cursor() {
    static uchar cursorTimer = 0;

    cursorTimer++;
    if (cursorTimer == 50) {
        cursorTimer = 0;
        display_bigsprite(0, 0);
    } else if (cursorTimer == 25) {
        display_bigsprite(0, 1);
    }

    move_bigsprite(0, cursorX*16 - target_scx + 8, cursorY*16 - target_scy + 32);
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

uchar scx = 0, scy = 0;

void update_camera() {
    uchar cameraX = target_scx / 16;
    uchar cameraY = target_scy / 16;
    if (cursorX < cameraX) {
        target_scx -= 16;
    } else if (cursorX >= cameraX + 10) {
        target_scx += 16;
    }

    if (cursorY < cameraY) {
        target_scy -= 16;
    } else if (cursorY >= cameraY + 8) {
        target_scy += 16;
    }

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

#define CHARACTER_BIGTILE_START 2
#define CHARACTER_SPRITE_SLOT_START 2
#define BOSTON 0
#define MARIE 1
#define FRED 2
#define ENEMY 3

void setup_characters() {
    numCharacters = 4;
    entities[0].x = 6 * 16;
    entities[0].y = 6 * 16;
    entities[0].sprite = BOSTON * 2;
    entities[0].name = "BOSTON";
    entities[0].party = PARTY_FRIEND;
    entities[0].moved = 0;
    display_bigsprite(CHARACTER_SPRITE_SLOT_START, CHARACTER_BIGTILE_START + BOSTON * 2);

    entities[1].x = 7 * 16;
    entities[1].y = 6 * 16;
    entities[1].sprite = MARIE * 2;
    entities[1].name = "MARIE ";
    entities[1].party = PARTY_FRIEND;
    entities[1].moved = 0;
    display_bigsprite(CHARACTER_SPRITE_SLOT_START + 1, CHARACTER_BIGTILE_START + MARIE * 2);

    entities[2].x = 3 * 16;
    entities[2].y = 6 * 16;
    entities[2].sprite = FRED * 2;
    entities[2].name = "FRED  ";
    entities[2].party = PARTY_FRIEND;
    entities[2].moved = 0;
    display_bigsprite(CHARACTER_SPRITE_SLOT_START + 2, CHARACTER_BIGTILE_START + FRED * 2);

    entities[3].x = 2 * 16;
    entities[3].y = 6 * 16;
    entities[3].sprite = ENEMY * 2;
    entities[3].name = "ENEMY ";
    entities[3].party = PARTY_ENEMY;
    entities[3].moved = 0;
    display_bigsprite(CHARACTER_SPRITE_SLOT_START + 2, CHARACTER_BIGTILE_START + ENEMY * 2);
}

#define CHARACTER_ANIMATION_DELAY 15

uchar characterAnimationTimer = CHARACTER_ANIMATION_DELAY;

void update_characters() {
    for (uchar i = 0; i < numCharacters; i++) {
        move_bigsprite(i + CHARACTER_SPRITE_SLOT_START, entities[i].x - scx + 8, entities[i].y - scy + 16);
    }

    characterAnimationTimer--;
    if (characterAnimationTimer == 0) {
        characterAnimationTimer = CHARACTER_ANIMATION_DELAY;
        for (uchar i = 0; i < numCharacters; i++) {
            entities[i].sprite ^= 1;
            display_bigsprite(i + CHARACTER_SPRITE_SLOT_START, CHARACTER_BIGTILE_START + entities[i].sprite);
        }
    }
}

void post_move(){
    //check objective

    for (int i = 0; i < numCharacters; ++i){
        if ((entities[i].party == party_current) && (entities[i].moved == 0)){
            return;
        }
    }

    for (int i = 0; i < numCharacters; ++i){
        if (entities[i].moved == 1){
            entities[i].moved = 0;
        }
    }

    //change later
    party_current = (party_current + 1)%2;
    if (party_current == 0){
        add_turn();
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
        if (cursorX == entities[i].x / 16 && cursorY == entities[i].y / 16) {
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
        change_text(entities[hoverCharacter].name);
    }
}

void check_enter_move_mode() {
    if (joy_impulse & J_A) {
        if (hoverCharacter != 255 && entities[hoverCharacter].party == party_current && entities[hoverCharacter].moved == 0) {
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

inline void render_second_cursor() {
    move_bigsprite(1, secondCursorX * 16 - scx + 8, secondCursorY * 16 - scy + 16);
}

void vblank_routine() {
    move_cursor();

    SCX_REG = scx;
    SCY_REG = scy;

    copy_window_buffer();
    //while (LY_REG != 0) ;
    LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJOFF | LCDCF_WIN9C00 | LCDCF_WINON | LCDCF_OBJ16;
    set_bkg_palette_entry(0, 0, RGB_BLACK);
    while (LY_REG != 1) ;
    set_bkg_palette_entry(0, 0, RGB_WHITE);
    while (LY_REG != 13) ;
    set_bkg_palette_entry(0, 0, RGB_BLACK);
    while (LY_REG != 15) ;
    set_bkg_palette_entry(0, 0, RGB_WHITE);
    LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_WINOFF | LCDCF_OBJ16;
}

void check_confirm_move() {
    if (joy & J_A) {
        uchar x = cursorX;
        uchar y = cursorY;
        if (hoverCharacter != 255) {
            return;
        }

        uchar found = pathfind(secondCursorX, secondCursorY, cursorX, cursorY, 5);
        if (found) {
            state = STATE_MOVE;
        }
    }
}

void setup_gui_textbox() {
    volatile uchar *tilemap = (uchar *) WIN_TILEMAP_START;
    tilemap[0] = TEXTBOX_END * 2;
    tilemap[0 + 32] = TEXTBOX_END * 2 + 1;
    tilemap[NAME_LENGTH + 1] = TEXTBOX_MIDDLE * 2;
    tilemap[NAME_LENGTH + 1 + 32] = TEXTBOX_MIDDLE * 2 + 1;
}

void main() {
    wait_vbl_done();
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
    


    set_sprite_palette(0, 1, colors);
    set_sprite_prop(0, 0);

    set_sprite_data(0, 40, Sprites);
    display_bigsprite(0, 0);
    

    add_VBL(vblank_routine);
    IE_REG = IEF_VBLANK;
    enable_interrupts();

    party_current = 0;
    turn_cntr = 0;
    add_turn();
    
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
            if (move_entity_after_pathfinding(selectedCharacter)){
                state = STATE_LOOK;
                move_bigsprite(1, 0, 0);
                post_move();
            }
        }

        process_bigsprites();
        __asm__("halt");
    }
}