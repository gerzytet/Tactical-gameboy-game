/*
@file entities.h
@author entire team
@date 4/16/2023
@brief 
*/

#ifndef ENTITIES_H
#define ENTITIES_H

#include "entities.c"

void paletteswap(uchar entity, uchar color);
void palette_refresh(uchar entity);
void setup_characters();
uchar is_party_exist(uchar party);
uchar * get_adj_entities(uchar entity);
uchar * get_adj_interact_spaces(uchar entity);

#endif