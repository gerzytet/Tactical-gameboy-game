\/*
@file bigsprites.h
@author entire team
@date 3/22/2023
@brief Large sprite boiler-plate code
*/


#ifndef BIGSPRITES_H
#define BIGSPRITES_H

#define internal_display_bigsprite(slot, tile)\
    set_sprite_tile((slot)*2, (tile)*4);\
    set_sprite_tile((slot)*2+1, (tile)*4+2);\

#define internal_move_bigsprite(slot, x, y)\
    move_sprite((slot)*2, (x), (y));\
    move_sprite((slot)*2+1, (x)+8, (y));

#define move_bigsprite(slot, x_, y_)\
    bigsprites[slot].x = (x_);\
    bigsprites[slot].y = (y_);

#define display_bigsprite(slot, tile)\
    bigsprites[slot].sprite = (tile);


void set_bigsprite_color(uchar bigsprite, uchar color);
void process_bigsprites();
void init_bigsprites();

uchar bigspriteCounts[16];

struct Bigsprite {
    uchar y;
    uchar x;
    uchar sprite;
    //uchar color; or something
};

struct Bigsprite bigsprites[20];

extern void display_bigsprites();


#endif