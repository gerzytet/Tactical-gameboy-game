#ifndef TILE_DEFINITIONS_H
#define TILE_DEFINITIONS_H
#include "common.h"

//display text, palette index, passable, advantage
#define TILE_MASTER_TABLE \
    X("HOUSE ", 4, 0, 255) \
    X("CAVE  ", 3, 0, 255) \
    X("CHEST ", 2, 0, 255) \
    X("TREE  ", 1, 0, 255) \
    X("FENCE ", 3, 0, 255) \
    X("GRASS ", 1, 1, 3) \
    X("PATH  ", 3, 1, 5) \
    X("WALL  ", 0, 0, 255) \
    X("WATER ", 0, 0, 255) \
    X("BRIDGE", 0, 1, 2) \
    X("ROCK  ", 0, 0, 255) \
    X("FOREST", 0, 0, 255) \
    X("START ", 0, 1, 1) \
    X("END   ", 0, 1, 1)

#define X(display, palette, passable, advantage) advantage,
const uchar advantageTable[NUM_TILES] = {
    TILE_MASTER_TABLE
};
#undef X

#define X(display, palette, passable, advantage) display,
const uchar* displayTexts[NUM_TILES] = {
    TILE_MASTER_TABLE
};
#undef X

#define X(display, palette, passable, advantage) palette,
const uchar paletteTable[NUM_TILES] = {
    TILE_MASTER_TABLE
};
#undef X

#define X(display, palette, passable, advantage) passable,
const uchar passable_table[NUM_TILES] = {
    TILE_MASTER_TABLE
};

#endif