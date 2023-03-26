#include "common.h"
#include <gb/gb.h>
#include <gb/cgb.h>
#include "graphics/palletes.c"
#include "graphics/Sprites.h"
#include "graphics/Sprites.c"
#include "tile_definitions.h"
#include "graphics/2x2tiles.h"
#include "graphics/2x2tiles.c"
#include "graphics/Letters.h"
#include "graphics/Letters.c"
#include "graphics/Top_textbox.h"
#include "graphics/Top_textbox.c"
#include "graphics/Numbers.h"
#include "graphics/Numbers.c"
#include "pathfinding.c"
#include "leveldata.h"
#include "entities.c"

#define CURSOR1 13
#define CURSOR2 14

uchar hoverCharacter = 255;
uchar scx = 0, scy = 0;

//unit: bigtiles
uchar cursorX = 0, cursorY = 0;
uchar secondCursorX = 0, secondCursorY = 0;


uchar selectedCharacter = 255;

enum State {
    STATE_LOOK = 0,
    STATE_CHOOSE_MOVE = 1,
    STATE_MOVE = 2
};
uchar state = STATE_LOOK;

#define TILEMAP_START 0x9800
#define FIRST_TILE_OFFSET_2x2 0

void setup_background_palletes() {
    set_bkg_palette(0, 8, colors);
    VBK_REG = VBK_BANK_1;

    volatile uchar *tilemap = (uchar *)TILEMAP_START;
    for (uchar r = 0; r < HEIGHT * 2; r++) {
        for (uchar c = 0; c < WIDTH * 2; c++) {
            uchar tile = MAPS[mapIndex][r/2][c/2];
            uchar pal = paletteTable[tile];
            tilemap[r*32 + c] = pal | 0b00001000; /*set vram bank to 1*/
        }
    }

    VBK_REG = VBK_BANK_0;
}

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
            uchar map = (MAPS[mapIndex][r/2][c/2] + FIRST_TILE_OFFSET_2x2)*4;
            uchar value = map + (r&1) + (c&1)*2;
            tilemap[r*32 + c] = value;
        }
    }
}

//this is 255 if we are not hovering over a character, otherwise it is the index of the character
void update_hover_character() {
    hoverCharacter = 255;
    for (uchar i = 0; i < numCharacters; i++) {
        if (cursorX == entities[i].x / 16 && cursorY == entities[i].y / 16) {
            hoverCharacter = i;
            break;
        }
    }
}

uchar joyTimer = 0;
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

uchar turn_cntr = 0;
void add_turn(){
    ++turn_cntr;
    party_current = 0;
    add_turn_gui();
}

void update_gui() {
    if (hoverCharacter == 255) {
        uchar coord = MAPS[mapIndex][cursorY][cursorX];
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

void map_vblank_routine() {
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

inline void render_second_cursor() {
    move_bigsprite(1, secondCursorX * 16 - scx + 8, secondCursorY * 16 - scy + 16);
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

void check_win(){

    //0 continue
    //1 player win
    //2 enemy win

    if (is_party_exist(PARTY_FRIEND) == 0){
        winState = PLAYER_LOST;
    }
    else if (is_party_exist(PARTY_ENEMY) == 0){
        if (winCondition == WIN_IF_ENEMY_DEFEAT){
            winState = PLAYER_WON;
        }
        else if (winCondition > 1 && turn_cntr >= winCondition){
            winState = PLAYER_WON; 
        }    
    }
    return;
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
        check_win(); //uncomment to test game_over()
        add_turn();
    }
}

void post_move(uchar selectedCharacter){
    uchar * adj_entities = get_adj_entities(selectedCharacter);
    uchar * adj_interact_spaces = get_adj_interact_spaces(selectedCharacter);

    for (uchar i = 0; i < 4; ++i){
        if (adj_entities[i] != 255 /*|| adj_interact_spaces[i] != 255*/){
            //flash palette of adj entities/spaces
            //use dpad to select which or A to skip

            //DURING FRAME:

            //animation for palettes                

            //if statement to check whether to battle or interact?

            battle(selectedCharacter, 255);

            /*
            Once moved, display four adjacent squares for interacting or battling
            If no interactables or enemies are adjacent, quit post_move
            */

           /*
           if(no enemies or interactables)
           {
                //quit post move
                return;
           }
           else if(up tile selected and something there)
           {
                battle(selectedCharacter, adj_entities[0]);                        
                //start battle animation
           }
           else if(right tile selected and something there)
           {
                battle(selectedCharacter, adj_entities[1]);                        
                //start battle animation
           }
           else if(down tile selected and something there)
           {
                battle(selectedCharacter, adj_entities[2]);                        
                //start battle animation
           }
           else if(left tile selected and something there)
           {
                battle(selectedCharacter, adj_entities[3]);                        
                //start battle animation
           }
           */

            // if (joy_impulse & J_UP) {                                       
            //     if (adj_entities[0] != 255) {                        
            //         battle(selectedCharacter, adj_entities[0]);                        
            //         goto PALETTESWAP;
            //     }
            // }
            // else if (joy_impulse & J_RIGHT) {
            //     if (adj_entities[1] != 255) {
            //         battle(selectedCharacter, adj_entities[1]);
            //         goto PALETTESWAP;
            //     }
            // }
            // else if (joy_impulse & J_DOWN) {
            //     if (adj_entities[2] != 255) {
            //         battle(selectedCharacter, adj_entities[2]);
            //         goto PALETTESWAP;
            //     }
            // }
            // else if (joy_impulse & J_LEFT) {
            //     if (adj_entities[3] != 255) {                        
            //         battle(selectedCharacter, adj_entities[3]);
            //         goto PALETTESWAP;
            //     }
            // }
        }
    }

    //set selectedCharacter palette to greyscale
    PALETTESWAP:paletteswap(selectedCharacter, 0);

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

void play_game(){
    __asm__("halt");
    LCDC_REG = 0x00;
    game_mode = MODE_MAP;
    CRITICAL {
        SCY_REG = 0;
        SCX_REG = 0;
        init_bigsprites();

        setup_window();

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

        add_turn(); 
        LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_OBJ16;
    }
    while (1) {
        if (state == STATE_LOOK || state == STATE_CHOOSE_MOVE) {
            check_cursor_movement();
        }
        update_camera();
        
        update_characters();
        update_hover_character();
        update_gui();

        /*if (joy_impulse & J_START && state == STATE_LOOK){
            break;
        }*/

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
                if (joy_impulse & J_START && state == STATE_LOOK){
                    break;
                }
                if (winState != 0){
                    break; //gameover
                }
            }
        }

        move_cursor();
        
        process_bigsprites();
        __asm__("halt");
    }

    game_over();
}