#include "common.h"
#include <gb/gb.h>
#include <gb/cgb.h>
#include "../graphics/palettes.c"
#include "../graphics/Sprites.h"
#include "tile_definitions.h"
#include "../graphics/2x2tiles.h"
#include "../graphics/Letters.h"
#include "../graphics/Top_textbox.h"
#include "../graphics/Numbers.h"
#include "pathfinding.h"
#include "leveldata.h"
#include "entities.h"

//

#define CURSOR1 13
#define CURSOR2 14

uchar hoverCharacter = 255;
uchar scx = 0, scy = 0;

//unit: bigtiles
uchar cursorX = 0, cursorY = 0;
uchar secondCursorX = 0, secondCursorY = 0;


uchar selectedCharacter = 255;

enum TurnState {
    STATE_LOOK = 0,
    STATE_CHOOSE_MOVE = 1,
    STATE_MOVE = 2,
    STATE_CHOOSE_ATTACKER = 3,
    STATE_AUTO_TURN = 4
};

uchar phase_state = STATE_LOOK;

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
    set_banked_bkg_data(FIRST_TILE_OFFSET_2x2 * 4, NUM_TILES * 4, Tiles, 2); //tiles.  15 big tiles, 60 small tiles
    VBK_REG = VBK_BANK_0;
    set_banked_bkg_data(128, 46, Letters, 2); //letters. 46 tiles.  23 letters
    set_banked_bkg_data(46, 10, Top_textbox, 2);
    set_banked_bkg_data(56, 20, Numbers, 2);

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

        uchar found = pathfind(secondCursorX, secondCursorY, cursorX, cursorY, 5, 0);
        if (found) {
            phase_state = STATE_MOVE;
        }
    }
}

uchar last_selected;

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
            phase_state = STATE_CHOOSE_MOVE;
            secondCursorX = cursorX;
            secondCursorY = cursorY;
            display_bigsprite(1, 0);
            selectedCharacter = hoverCharacter;
        }
    }
}

inline void hide_cursor() {
    move_bigsprite(0, 0, 0);
    move_bigsprite(1, 0, 0);
}

void check_exit_move_mode() {
    if (joy & J_B) {
        phase_state = STATE_LOOK;
        hide_cursor();
    }
}

void check_win(){

    //0 continue
    //1 player win
    //2 enemy win

    if (is_party_exist(PARTY_FRIEND) == 0){
        winState = PLAYER_LOST;
    }
    else if (is_party_exist(PARTY_ENEMY) == 0 && winCondition == WIN_IF_ENEMY_DEFEAT){
        winState = PLAYER_WON;
    }
    else if (winCondition > 1 && turn_cntr >= winCondition){
        winState = PLAYER_WON;
    }
    return;
}

uchar currEntity = 0;
uchar pathfinding_done = 0;
void start_enemy_turn() {
    currEntity = 0;
    pathfinding_done = 0;
}

void advance_phase(){
    //todo: check_win() during attack phase

    //currently it checks all chars
    //  1 time from player to enemy, enemy to other
    //  2 times from player to other, other to player
    //  3 times from enemy to player, (other to enemy, impossible case)

    check_win(); //uncomment to test game_over()

    do{
         party_current++;
    }while(party_current <= 2 && !is_party_exist(party_current));
    
    if (party_current > 2){
         //player can be assumed to be alive, this check is done in check win
         party_current = 0;
         add_turn();
    }

    //this is not the proper place to put this
    //if it is, checks should be done to check which turn it is 
    //as well as the MoveMode (fixed)
    if (party_current == PARTY_ENEMY) {
        start_enemy_turn();
        if (enemyMoveMode == enemyMoveMan){
            phase_state = STATE_LOOK;
        } else if (enemyMoveMode = enemyMoveAuto) {
            phase_state = STATE_AUTO_TURN;
        }
    } else {
        phase_state = STATE_LOOK;
    }
}

void post_manual_action() {
    //if any characters have not yet moved, return
    for (uchar i = 0; i < numCharacters; ++i){
        if ((entities[i].party == party_current) && (entities[i].moved == 0)){
            phase_state = STATE_LOOK;
            return;
        }
    }

    for (uchar i = 0; i < numCharacters; ++i){
        if (entities[i].moved == 1){
            entities[i].moved = 0;
        }
        //set palette to party color
        palette_refresh(i);
    }

    advance_phase();
}

void post_move(){
    uchar * adj_entities = get_adj_entities(selectedCharacter);
    uchar * adj_interact_spaces = get_adj_interact_spaces(selectedCharacter);

    uchar adj_found = 0;
    for (uchar i = 0; i < 4; ++i){
        if (adj_entities[i] != 255 || adj_interact_spaces[i] == 255){
            adj_found = 1;
            last_selected = i;
            
            switch(i){
                case(NORTH):
                    cursorX = entities[selectedCharacter].x / 16;
                    cursorY = (entities[selectedCharacter].y-1) / 16;
                    break;
                case(EAST):
                    cursorX = (entities[selectedCharacter].x+1) / 16;
                    cursorY = entities[selectedCharacter].y / 16;
                    break;
                case(SOUTH):
                    cursorX = entities[selectedCharacter].x / 16;
                    cursorY = (entities[adj_entities[i]].y+1) / 16;
                    break;
                case(WEST):
                    cursorX = (entities[selectedCharacter].x-1) / 16;
                    cursorY = entities[selectedCharacter].y / 16;
                    break;
            }
            break;
        }
    }

    //set selectedCharacter palette to greyscale
    //PALETTESWAP:palette_refresh(selectedCharacter);
    palette_refresh(selectedCharacter);

    if (adj_found) {
        
        phase_state = STATE_CHOOSE_ATTACKER;
        secondCursorX = entities[selectedCharacter].x / 16;
        secondCursorY = entities[selectedCharacter].y / 16;
    } else {
        post_manual_action();
    }

    check_win();
}

#define CHARACTER_ANIMATION_DELAY 15

uchar characterAnimationTimer = CHARACTER_ANIMATION_DELAY;

void update_select_attacker_cursor() {
    uchar centerX = entities[selectedCharacter].x / 16;
    uchar centerY = entities[selectedCharacter].y / 16;
    if (joy_impulse & J_UP && centerY > 0) {
        last_selected = NORTH;
        cursorX = centerX;
        cursorY = centerY - 1;
    } else if (joy_impulse & J_DOWN && centerY < WIDTH - 1) {
        last_selected = SOUTH;
        cursorX = centerX;
        cursorY = centerY + 1;
    } else if (joy_impulse & J_LEFT && centerX > 0) {
        last_selected = WEST;
        cursorX = centerX - 1;
        cursorY = centerY;
    } else if (joy_impulse & J_RIGHT && centerX < WIDTH - 1) {
        last_selected = EAST;
        cursorX = centerX + 1;
        cursorY = centerY;
    }
}

void remove_character(uchar index){
    entities[index] = entities[numCharacters-1];
    entities[numCharacters-1].moved = 3;
    move_bigsprite(numCharacters-1 + CHARACTER_SPRITE_SLOT_START,0,0);
    palette_refresh(index);
    --numCharacters;
}

void check_confirm_interact() {
    if (joy_impulse & J_A) {
        uchar *adj_entities = get_adj_entities(selectedCharacter);

        if (adj_entities[last_selected] != 255) {
            uchar target = adj_entities[last_selected];
            
            if (debug_instakill == 0){
                battle(selectedCharacter, target);
            }
            else{
                remove_character(target);
            }
            post_manual_action();
        }
        //todo:
        //else if adj interact space is interactable
        //interact
    }
}

void check_cancel_interact() {
    if (joy_impulse & J_B) {
        phase_state = STATE_LOOK;
    }
}

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

void update_cursor_color() {
    set_bigsprite_color(0, phase_state == STATE_CHOOSE_ATTACKER ? 2 : 0);
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
        set_banked_sprite_data(0, 40, Sprites, 2);
        display_bigsprite(0, 0);

        add_turn(); 
        LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_OBJ16;
    }
    while (1) {
        if (phase_state == STATE_LOOK || phase_state == STATE_CHOOSE_MOVE) {
            check_cursor_movement();
        }
        update_camera();
        
        update_characters();
        update_hover_character();
        update_gui();
        update_cursor_color();

        if (phase_state == STATE_AUTO_TURN) {
            hide_cursor();
        chooseEnemy:
            if (currEntity >= numCharacters) {
                advance_phase();
                    goto end;
            }
            while (entities[currEntity].party != party_current){
                currEntity++;
                pathfinding_done = 0;
                if (currEntity >= numCharacters){
                    advance_phase();
                    goto end;
                }
            }

            if (!pathfinding_done) {
                uchar result = pathfind(entities[currEntity].x / 16, entities[currEntity].y / 16, entities[0].x / 16, entities[0].y / 16, 10, 1);
                if (!result) {
                    currEntity++;
                    goto chooseEnemy;
                }
                pathfinding_done = 1;
            }

            if (move_entity_after_pathfinding(currEntity, 3, 1)) {
                currEntity++;
                goto chooseEnemy;
            }
        } else if (phase_state == STATE_LOOK) {
            check_enter_move_mode();
            if (joy_impulse & J_SELECT && phase_state == STATE_LOOK){
                advance_phase();
            }
        } else if (phase_state == STATE_CHOOSE_MOVE) {
            render_second_cursor();
            check_confirm_move();
            check_exit_move_mode();
        } else if (phase_state == STATE_MOVE) {
            if (move_entity_after_pathfinding(selectedCharacter, 255, 0)){
                phase_state = STATE_LOOK; //this might get undone by post_move
                hide_cursor();
                post_move();
                if (joy_impulse & J_START && phase_state == STATE_LOOK){
                    break;
                }
                if (winState != 0){
                    goto endgame; //gameover
                }
            }
        } else if (phase_state == STATE_CHOOSE_ATTACKER) {
            update_select_attacker_cursor();
            check_confirm_interact();
            check_cancel_interact();
            //check win
        }
        end:

        move_cursor();
        
        process_bigsprites();
        __asm__("halt");
    }

    endgame:
    game_over();
}