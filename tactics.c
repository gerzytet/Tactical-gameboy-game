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
#include "graphics/Numbers.h"
#include "graphics/Numbers.c"
#include <stdio.h>
#include "graphics/Menu_BG.c"
#include "graphics/Menu_BG_Map.c"

#define CURSOR1 13
#define CURSOR2 14

const uchar paletteTable[NUM_TILES] = {
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

uchar party_current = 0;
uchar turn_cntr = 0;

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
    SPACE_LETTER //z
};

uchar number_table[10] = {
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

uchar lettersmax = 12;

void change_menu_text(const uchar *text, uchar length){
    if (text == NULL) {
        return;
    }
    set_sprite_data(0, 46, Letters); //46 tiles, 23 letters

    for (uchar i = 0; i < lettersmax; ++i){
        uchar tile = text[i]-'A';
        if (i >= length || text[i] != ' ') {
            set_sprite_tile(i, letter_table[tile]);
            move_sprite(i, ((i+11)*8-length*4), (17)*8);
        }
    }
}

void menu_text_anim(uchar frame){
    for (uchar i = 0; i < lettersmax; ++i){
        if ((i+frame)%8 > 3){
            scroll_sprite(i, 0, 1);
        }
        else{
            scroll_sprite(i, 0, -1);
        }
    }
}

void add_turn(){
    ++turn_cntr;
    party_current = 0;
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
            tile = SPACE_LETTER;
        } else {
            tile = letter_table[text[i] - 'A'];
        }
        tilemap[i+13] = tile;
        tile++;
        tilemap[i+13|32] = tile;
    }

    //then print the turn #
    if (tens_digit == 0) {
        tile = SPACE_LETTER;
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

uchar is_party_exist(uchar party){
    //when enemies & others are defeated, they are removed from the char list
    //when players are defeated, they are set to .moved = 3 (2 is idle)
    //the .moved var here will be changed in the future to a new var to allow
    //  all characters to move independantly with preset algorithms
    
    for (uchar i = 0; i < numCharacters; ++i){
        if ((entities[i].party == party) && (entities[i].moved < 3)){
            return 1;
        }
    }

    return 0;
}

uchar win_condition = 0;
uchar win_state = 0;
//0 defeat enemy
//1 move to space
//x survive x-1 turns

uchar check_win(){

    //0 continue
    //1 player win
    //2 enemy win

    if (is_party_exist(0) == 1){
        win_state = 2;
    }
    else if (is_party_exist(1) == 1){
        if (win_condition == 0){
            win_state = 1;
        }
        else if (win_condition > 1 && turn_cntr >= win_condition){
            win_state = 1; 
        }    
    }
    return 0;
}

void advance_phase(){
    //todo: check_win() during attack phase

    //currently it checks all chars
    //  1 time from player to enemy, enemy to other
    //  2 times from player to other, other to player
    //  3 times from enemy to player, (other to enemy, impossible case)

    do{
        party_current++;
    }while(party_current <= 2 && !is_party_exist(party_current));
    
    if (party_current > 2){
        //player can be assumed to be alive, this check is done in check win
        party_current = 0;
        //check_win(); //uncomment to test gameover()
        add_turn();
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
            uchar pal = paletteTable[tile];
            tilemap[r*32 + c] = pal | 0b00001000; /*set vram bank to 1*/
        }
    }

    VBK_REG = VBK_BANK_0;
}

extern void copy_window_buffer();

//Including textbox tiles:
#define NUM_LETTERS 27

//unit: small tiles
#define TEXTBOX_END 46
#define TEXTBOX_MIDDLE 47

#define FIRST_TILE_OFFSET_2x2 0

void setup_background() {
    VBK_REG = VBK_BANK_1;
    set_bkg_data(FIRST_TILE_OFFSET_2x2 * 4, NUM_TILES * 4, Tiles); //tiles.  15 big tiles, 60 small tiles
    VBK_REG = VBK_BANK_0;
    set_bkg_data(0, 46, Letters); //letters. 46 tiles.  23 letters
    set_bkg_data(46, 10, Top_textbox);
    set_bkg_data(56, 20, Numbers);

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

void paletteswap(uchar entity, uchar color){
    //Swap palette of current tile
    uchar bigsprite = entity + 2;
    uchar sprite = bigsprite * 2;
    uchar bytenum = sprite * 4;

    volatile unsigned char* oam_data = &((unsigned char*)&shadow_OAM)[bytenum];
    oam_data[3] &= 0b11111000;
    oam_data[3] |= color;
    oam_data = &((unsigned char*)&shadow_OAM)[(sprite + 1)*4];
    oam_data[3] &= 0b11111000;
    oam_data[3] |= color;
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
    entities[0].health = 10;
    entities[0].maxHealth = 10;
    display_bigsprite(CHARACTER_SPRITE_SLOT_START, CHARACTER_BIGTILE_START + BOSTON * 2);

    entities[1].x = 7 * 16;
    entities[1].y = 6 * 16;
    entities[1].sprite = MARIE * 2;
    entities[1].name = "MARIE ";
    entities[1].party = PARTY_FRIEND;
    entities[1].moved = 0;
    entities[1].health = 4;
    entities[1].maxHealth = 20;
    display_bigsprite(CHARACTER_SPRITE_SLOT_START + 1, CHARACTER_BIGTILE_START + MARIE * 2);

    entities[2].x = 3 * 16;
    entities[2].y = 6 * 16;
    entities[2].sprite = FRED * 2;
    entities[2].name = "FRED  ";
    entities[2].party = PARTY_FRIEND;
    entities[2].moved = 0;
    entities[2].health = 1;
    entities[2].maxHealth = 20;
    display_bigsprite(CHARACTER_SPRITE_SLOT_START + 2, CHARACTER_BIGTILE_START + FRED * 2);

    entities[3].x = 2 * 16;
    entities[3].y = 6 * 16;
    entities[3].sprite = ENEMY * 2;
    entities[3].name = "ENEMY ";
    entities[3].party = PARTY_ENEMY;
    entities[3].moved = 0;
    entities[3].health = 19;
    entities[3].maxHealth = 20;
    display_bigsprite(CHARACTER_SPRITE_SLOT_START + 2, CHARACTER_BIGTILE_START + ENEMY * 2);

    for (uchar i = 0; i < numCharacters; ++i){
        paletteswap(i, entities[i].party + 1);
    }
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

uchar get_north_adj_entity(uchar entity);
uchar battle(uchar attacker, uchar defender);

void post_move(uchar selectedCharacter){

    if (get_north_adj_entity(selectedCharacter) != 255){
        battle(selectedCharacter, get_north_adj_entity(selectedCharacter));
    }

    //set selectedCharacter palette to greyscale
    paletteswap(selectedCharacter, 0);

    //if any characters have not yet moved, return
    for (uchar i = 0; i < numCharacters; ++i){
        if ((entities[i].party == party_current) && (entities[i].moved == 0)){
            return;
        }
    }

    for (uchar i = 0; i < numCharacters; ++i){
        if (entities[i].moved == 1){
            entities[i].moved = 0;
            //set palette to party color
            paletteswap(i, entities[i].party + 1);

        }
    }

    advance_phase();
    //check win?
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

void render_health(uchar healthLevel);

void update_gui() {
    if (hoverCharacter == 255) {
        uchar coord = MAP[cursorY][cursorX];
        uchar *text = (uchar *)displayTexts[coord];
        change_text(text);
    } else {
        change_text(entities[hoverCharacter].name);
    }
    if (hoverCharacter == 255) {
        render_health(0);
    } else {
        uchar healthLevel = ((uint16_t)entities[hoverCharacter].health * 20) / entities[hoverCharacter].maxHealth;
        render_health(healthLevel);
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

/*uchar[] get_adj_entities(){
    return NULL;
}*/

uchar get_north_adj_entity(uchar entity){

    for (uchar i = 0; i < numCharacters; ++i){
        if (i != entity && entities[entity].x == entities[i].x && entities[entity].y == entities[i].y +16){
            return i;
        }
    }
    return 255;
}

uchar battle(uchar attacker, uchar defender){
    if (attacker == defender || entities[attacker].party == entities[defender].party){
        return 0;
    }
    //start battle scene
    //attacker attacks
    //todo: fix to not go negative
    //todo: edit the algorithm
    entities[defender].health -= 5;
    if (entities[defender].health == 0 || entities[defender].health > entities[defender].maxHealth){
        entities[defender].health = 0;
        //remove from map
        return 2;
    }
    //defender counters
    entities[attacker].health -= 8;
    if (entities[attacker].health <= 0 || entities[attacker].health > entities[attacker].maxHealth){
        entities[attacker].health == 0;
        //remove from map
        return 1;
    }
    return 0;
}

void gameover(){
    //todo
    //set char lvl ups to mem if won
    //title screen if lost
}

void playgame(){
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

    set_sprite_palette(0, 4, colors_objects);
    set_sprite_prop(0, 0);
    set_sprite_data(0, 40, Sprites);
    display_bigsprite(0, 0);

    add_VBL(vblank_routine);
    IE_REG = IEF_VBLANK;
    enable_interrupts();

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
            if (joy_impulse & J_SELECT && state == STATE_LOOK){
                advance_phase();
            }
        } else if (state == STATE_CHOOSE_MOVE) {
            render_second_cursor();
            check_confirm_move();
            check_exit_move_mode();
        } else if (state == STATE_MOVE) {
            if (move_entity_after_pathfinding(selectedCharacter)){
                state = STATE_LOOK;
                move_bigsprite(1, 0, 0);
                post_move(selectedCharacter);
                if (win_state != 0){
                    break; //gameover
                }
            }
        }

        move_cursor();
        process_bigsprites();
        __asm__("halt");
    }

    //gameover()
}

//for *testing* GB linking
void multiplayer(){
    //loading..
    //joypad_init(2, /*pointer to struct*/);
    //connected
}

/*void startstory(){
    //playscene(0);
    //playscene(1);
    //playgame(0);
    //playscene(2);
    //playscene(3);
    //playgame(1);
    //playscene(4);
    //playscene(5);
    //playgame(2);
    //playscene(6);
    //playscene(7);
    //playgame(3);
    //playscene(8);
    //playscene(9);
    //playgame(4);
    //playscene(10);
    //playscene(11);
    //playcredits();
}*/

UINT8 scroll1, scroll2, scroll3;

/*void scrolleffect(){
    if (LYC_REG == 0x00){
        move_bkg(0, 0);
        LYC_REG = 0x60;
    }
    if (LYC_REG == 0x30){
        move_bkg(1, 0);
        LYC_REG = 0x64;
    }
    if (LYC_REG == 0x64){
        move_bkg(0, 0);
        LYC_REG = 0x00;
    }
}*/

uchar max_option = 4;
uchar menu_option = 0;

void update_menu_text(){
    switch (menu_option){
        case 0:
            change_menu_text("DEMO        ", 4);
            break;
        case 1:
            change_menu_text("STORY       ", 5);
            break;
        case 2:
            change_menu_text("MULTILINK   ", 9);
            break;
        case 3:
            change_menu_text("SETTINGS    ", 8);
            break;
        default:
            change_menu_text("PRESS START ", 11);
    }
}

void optionscroll(uchar dir){
    //STAT_REG = 0x45;
    //LYC_REG = 0x00;
    
    //disable_interrupts();
    //add_LCD(scrolleffect);
    //enable_interrupts();
    
    //set_interrupts(VBL_IFLAG | LCD_IFLAG);

    change_menu_text("            ", 0);
    for (uchar i = 0; i < 40; ++i){
        if (dir == 1){
            scroll_bkg(1, 0);
        }
        else{
            scroll_bkg(-1, 0);
        }
        wait_vbl_done();
    } 
    update_menu_text();
}

void mainmenu(){
    set_bkg_palette(0, 1, colors);
    set_bkg_data(0, 19, Menu_BG);
    set_bkg_tiles(0, 11, 10, 4, Menu_BG_Map);
    set_bkg_tiles(10, 11, 10, 4, Menu_BG_Map);
    scroll_bkg(-64, 0);

    VBK_REG = VBK_BANK_0;

    SPRITES_8x16;
    set_sprite_palette(0, 4, colors_objects);
    menu_option = max_option;
    update_menu_text();
    SHOW_SPRITES;

    SHOW_BKG;
    DISPLAY_ON;
    wait_vbl_done();

    uchar anim_frame = 0;
    uchar anim_delay = 0;
    while (1) {
        //DURING FRAME:
        joy_impulse = joy;
        joy = joypad();
        joy_impulse = ~joy_impulse & joy;
        
        if (anim_delay == 0){
            menu_text_anim(++anim_frame%8);    
        }
        ++anim_delay;
        anim_delay %=8;

        if (joy_impulse & J_START && menu_option == max_option){
            menu_option = 0;
            update_menu_text();
        }
        else if (joy_impulse & J_A && menu_option == 0){
            playgame();
        }
        /*else if (joy_impulse & J_A && menu_option == 1){
            //startstory();
        }*/
        /*else if (joy_impulse & J_A && menu_option == 2){
            //multiplayer();
        }*/
        else if (joy_impulse & J_RIGHT && menu_option < max_option - 1){
            //show gx
            ++menu_option;
            optionscroll(1);
        } 
        else if (joy_impulse & J_LEFT && menu_option > 0 && menu_option < max_option){
            //show gx
            --menu_option;
            optionscroll(2);
        }
        SHOW_BKG;
        wait_vbl_done();
    }
}

void main() {
    
    mainmenu();
}