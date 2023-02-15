#ifndef COMMON_H
#define COMMON_H

typedef unsigned char uchar;

#define WIDTH 12
#define HEIGHT 12

struct Entity {
    //unit: pixels relative to the top left of the map
    uchar x;
    uchar y;
    uchar sprite;
    const uchar * name;
    uchar party;
    uchar moved;
    uchar health;
    uchar maxHealth;
};

struct Entity entities[18];

uchar numCharacters;

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

const uchar MAP[WIDTH][HEIGHT] = {
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

#endif