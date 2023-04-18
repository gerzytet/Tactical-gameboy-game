#ifndef ENTITIES_C
#define ENTITIES_C

#include "common.h"
#include "leveldata.h"
#include "tile_definitions.h"

#define CHARACTER_BIGTILE_START 2
#define CHARACTER_SPRITE_SLOT_START 2
#define BOSTON 0
#define MARIE 1
#define FRED 2
#define ENEMY 3

#define BLANK 4

enum Party {
    PARTY_FRIEND = 0,
    PARTY_ENEMY = 1,
    PARTY_OTHER = 2
};

uchar party_current = PARTY_FRIEND;

void paletteswap(uchar entity, uchar color){
    //Swap palette of current tile
    set_bigsprite_color(entity + 2, color);
}

void palette_refresh(uchar entity){
    paletteswap(entity, (entities[entity].moved == 0)?(entities[entity].party + 1):0);
}

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

    entities[2].x = 3 * 16; //16, 16
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
        palette_refresh(i);
    }
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

uchar * get_adj_entities(uchar entity){
    static uchar adj_entities[4] = {255,255,255,255};
    for (uchar i = 0; i < 4; i++) {
        adj_entities[i] = 255;
    }
    
    //return adjacent spaces in clockwise fashion
    for (uchar i = 0; i < numCharacters; ++i) {
        if (i != entity && entities[entity].x == entities[i].x && entities[entity].y - 16 == entities[i].y) {
            adj_entities[NORTH] = i;
        }
    }

    for (uchar i = 0; i < numCharacters; ++i) {
        if (i != entity && entities[entity].x + 16 == entities[i].x && entities[entity].y == entities[i].y) {
            adj_entities[EAST] = i;
        }
    }

    for (uchar i = 0; i < numCharacters; ++i){
        if (i != entity && entities[entity].x == entities[i].x && entities[entity].y + 16 == entities[i].y){
            adj_entities[SOUTH] = i;
        }
    }
       
    for (uchar i = 0; i < numCharacters; ++i){
        if (i != entity && entities[entity].x - 16 == entities[i].x && entities[entity].y == entities[i].y){
            adj_entities[WEST] = i;
        }
    }

    return adj_entities;
}

uchar * get_adj_interact_spaces(uchar entity){
    static uchar adj_entities[4] = {255,255,255,255};

    //pixel: *16, map: no 16

    if (entities[entity].y > 0 && advantageTable[MAPS[mapIndex][entities[entity].x][entities[entity].y - 1]] != 255) {
        adj_entities[NORTH] = MAPS[mapIndex][entities[entity].x][entities[entity].y - 1];
    }
    if (entities[entity].x < WIDTH - 1 && advantageTable[MAPS[mapIndex][entities[entity].x + 1][entities[entity].y]] != 255) {
        adj_entities[EAST] = MAPS[mapIndex][entities[entity].x + 1][entities[entity].y];
    }
    if (entities[entity].y < HEIGHT-1 && advantageTable[MAPS[mapIndex][entities[entity].x][entities[entity].y+1]] != 255){
        adj_entities[SOUTH] = MAPS[mapIndex][entities[entity].x][entities[entity].y+1];
    }
    if (entities[entity].x > 0 && advantageTable[MAPS[mapIndex][entities[entity].x - 1][entities[entity].y]] != 255) {
        adj_entities[WEST] = MAPS[mapIndex][entities[entity].x - 1][entities[entity].y];
    }

    return adj_entities;
}

#endif