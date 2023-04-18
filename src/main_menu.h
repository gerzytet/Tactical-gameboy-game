/*
@file main_menu.h
@author entire team
@date 4/16/2023
@brief 
*/

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

void menu_text_anim();
void change_menu_text(const uchar *text, uchar length);
void update_menu_text();
void optionscroll(uchar dir);
void menu_vblank_routine();
void mainmenu();

#endif