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
    uchar inventory[5];
};

typedef struct {
    uchar lastMapCompleted;
    uchar inventory[10];
    uchar characterStats[6]; //store stats for 6 different player characters
} SaveData;

uchar joy = 0;
uchar joy_impulse = 0;

#define SPACE_LETTER 22 * 2

#define WIN_IF_ENEMY_DEFEAT 0
#define WIN_IF_PLAYER_ON_SPACE 1
//WIN_IF_SURVIVE_X_TURNS x+1

uchar mapIndex = 0;

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
#define WALL 7
#define WATER 8
#define BRIDGE 9
#define ROCK 10
#define FOREST 11

#define START 12
#define END 13

#define NUM_TILES (END + 1)

#endif