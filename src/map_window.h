/*
@file map_window.h
@author entire team
@date 4/16/2023
@brief 
*/

#ifndef MAP_WINDOW_H
#define MAP_WINDOW_H

void add_turn_gui();
void change_text(const uchar *text);
void set_overlay_text(const uchar *text, uchar length);
void setup_gui_textbox();
void reset_window();
void render_health(uchar healthLevel);
void setup_window();
extern void copy_window_buffer();

#endif