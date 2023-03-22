#ifndef LEVELDATA_H
#define LEVELDATA_H

const uchar winCondition_global[5] = {WIN_IF_ENEMY_DEFEAT,WIN_IF_ENEMY_DEFEAT,
WIN_IF_ENEMY_DEFEAT,WIN_IF_ENEMY_DEFEAT,WIN_IF_ENEMY_DEFEAT};

/*
Ideas for condition to progress to next level:
move to space for boss
defeat all enemies
survive # of turns
*/

//todo: enemy stuff

/*
new tiles:

*/

uchar MAPS[5][WIDTH][HEIGHT] = {
    //MAP0 - SMALL VILLIAGE
    {{TREE, PATH, GRASS, TREE, GRASS, GRASS, FENCE, HOUSE, FENCE, PATH, CAVE, FENCE},
    {TREE, PATH, START, START, GRASS, GRASS, FENCE, GRASS, FENCE, PATH, GRASS, GRASS},
    {TREE, PATH, START, GRASS, CAVE, CHEST, GRASS, GRASS, HOUSE, PATH, GRASS, GRASS},
    {TREE, PATH, GRASS, GRASS, GRASS, GRASS, PATH, PATH, GRASS, PATH, TREE, TREE},
    {TREE, PATH, PATH,  PATH,  PATH,  PATH,  PATH,  GRASS, GRASS, PATH, TREE, TREE},
    {TREE, GRASS, PATH, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, TREE, TREE},
    {TREE, GRASS, PATH, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, PATH, TREE, TREE},
    {TREE, GRASS, PATH, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, PATH, TREE, TREE},
    {TREE, HOUSE, PATH, PATH, PATH, HOUSE, TREE, HOUSE, GRASS, PATH, TREE, TREE},
    {TREE, TREE, HOUSE, HOUSE, PATH, TREE, HOUSE, TREE, GRASS, PATH, TREE, TREE},
    {TREE, TREE, TREE, HOUSE, PATH, HOUSE, TREE, HOUSE, GRASS, PATH, TREE, TREE},
    {TREE, TREE, GRASS, GRASS, PATH, CHEST, GRASS, GRASS, GRASS, PATH, GRASS, GRASS}},

    //MAP1 - BANDIT HIDEOUT
    {{HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, HOUSE, PATH, FENCE, CAVE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, GRASS, GRASS},
    {HOUSE, GRASS, GRASS, GRASS, CAVE, CHEST, GRASS, GRASS, HOUSE, PATH, GRASS, GRASS},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, START, END},
    {HOUSE, GRASS, HOUSE, HOUSE, HOUSE, GRASS, HOUSE, HOUSE, HOUSE, PATH, TREE, TREE},
    {HOUSE, PATH, PATH, PATH, PATH, FENCE, GRASS, TREE, TREE, PATH, TREE, TREE},
    {HOUSE, HOUSE, HOUSE, HOUSE, PATH, PATH, PATH, PATH, PATH, GRASS, TREE, TREE},
    {HOUSE, GRASS, GRASS, GRASS, CAVE, CHEST, GRASS, GRASS, PATH, PATH, GRASS, CAVE}},

    //MAP2 - RIVER PLAINS
    {{WATER, PATH, PATH, PATH, WATER, GRASS, GRASS, GRASS, WATER, PATH, CAVE, FENCE},
    {WATER, WATER, WATER, BRIDGE, GRASS, GRASS, WATER, GRASS, BRIDGE, PATH, GRASS, GRASS},
    {HOUSE, WATER, WATER, GRASS, FENCE, CHEST, FENCE, GRASS, HOUSE, PATH, GRASS, GRASS},
    {TREE, PATH, PATH, PATH, BRIDGE, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, TREE},
    {TREE, HOUSE, TREE, FENCE, FENCE, WATER, GRASS, GRASS, PATH, PATH, PATH, GRASS},
    {HOUSE, TREE, TREE, GRASS, WATER, WATER, GRASS, GRASS, HOUSE, PATH, TREE, GRASS},
    {HOUSE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, TREE, GRASS},
    {CAVE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, HOUSE, PATH, START, END},
    {HOUSE, GRASS, GRASS, HOUSE, WATER, HOUSE, HOUSE, HOUSE, PATH, PATH, PATH, GRASS},  
    {HOUSE, GRASS, HOUSE, HOUSE, WATER, HOUSE, HOUSE, WATER, WATER, PATH, TREE, TREE},
    {PATH, BRIDGE, WATER, WATER, WATER, HOUSE, HOUSE, HOUSE, WATER, PATH, TREE, TREE},
    {PATH, PATH, PATH, CHEST, WATER, CHEST, GRASS, GRASS, WATER, WATER, GRASS, GRASS}},

    //MAP3 - ENCHANTED FOREST
    {{TREE, FOREST, FOREST, FOREST, FOREST, TREE, TREE, FOREST, FOREST, FOREST, FOREST, FOREST},
    {HOUSE, HOUSE, FOREST, FOREST, FOREST, FOREST, FOREST, FOREST, FOREST, TREE, TREE, FOREST},
    {FOREST, FOREST, FOREST, TREE, TREE, FOREST, TREE, TREE, FOREST, FOREST, TREE, FOREST},
    {FOREST, TREE, FOREST, FOREST, TREE, FOREST, FOREST, FOREST, HOUSE, FOREST, FOREST, FOREST},
    {FOREST, FOREST, FOREST, HOUSE, TREE, TREE, TREE, TREE, FOREST, FOREST, TREE, FOREST},
    {FOREST, TREE, FOREST, FOREST, TREE, FOREST, FOREST, FOREST, FOREST, FOREST, FOREST, FOREST},
    {TREE, FOREST, TREE, TREE, TREE, FOREST, TREE, CHEST, TREE, FOREST, TREE, TREE},
    {FOREST, FOREST, FOREST, FOREST, FOREST, FOREST, FOREST, FOREST, TREE, FOREST, FOREST, FOREST},
    {FOREST, TREE, TREE, FOREST, TREE, TREE, TREE, TREE, FOREST, TREE, CHEST, FOREST},
    {FOREST, TREE, FOREST, FOREST, FOREST, FOREST, FOREST, FOREST, TREE, FOREST, TREE, FOREST},
    {FOREST, TREE, TREE, TREE, TREE, FOREST, FOREST, FOREST, TREE, FOREST, TREE, FOREST},
    {FOREST, FOREST, FOREST, TREE, FOREST, FOREST, FOREST, FOREST, FOREST, FOREST, FOREST, FOREST}}, 

    //MAP4 - WIZARD'S FORTRESS
    {{WALL, ROCK, WALL, WALL, PATH, PATH, PATH, PATH, ROCK, ROCK, WALL, WALL},
    {WALL, PATH, PATH, PATH, PATH, PATH, PATH, PATH, PATH, PATH, PATH, WALL},
    {WALL, PATH, PATH, PATH, PATH, ROCK, ROCK, PATH, PATH, PATH, PATH, WALL},
    {WALL, PATH, PATH, WALL, WALL, WALL, WALL, WALL, WALL, PATH, PATH, WALL},
    {WALL, ROCK, PATH, WALL, CHEST, WALL, WALL, PATH, WALL, ROCK, PATH, WALL},
    {WALL, PATH, PATH, WALL, PATH, PATH, PATH, PATH, WALL, PATH, PATH, WALL},
    {WALL, PATH, ROCK, WALL, WALL, PATH, PATH, WALL, WALL, PATH, PATH, WALL},
    {WALL, PATH, PATH, PATH, PATH, PATH, PATH, PATH, PATH, PATH, ROCK, WALL},
    {WALL, PATH, PATH, WALL, WALL, PATH, PATH, WALL, WALL, PATH, PATH, WALL},
    {WALL, PATH, PATH, WALL, WATER, BRIDGE, BRIDGE, WATER, WALL, PATH, WALL, WALL},
    {WALL, PATH, PATH, WALL, WATER, START, START, WATER, WALL, PATH, CHEST, WALL},
    {WALL, WALL, WALL, WALL, WATER, START, START, WATER, WALL, WALL, WALL, WALL}}
};

#endif