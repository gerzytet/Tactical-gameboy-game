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

uchar joy = 0;
uchar joy_impulse = 0;

#define SPACE_LETTER 22 * 2

const uchar letter_table[36] = {
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