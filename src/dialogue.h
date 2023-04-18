/*
@file dialogue.h
@author entire team
@date 4/16/2023
@brief 
*/

#ifndef DIALOGUE_H
#define DIALOGUE_H

void set_text(uchar index,uchar charNameIndex);
void set_char_sprite(uchar charSpriteIndex, uchar pos);
void advance_text();
void setupTextBox();
void play_scene(uchar index);

#endif
