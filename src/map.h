/*
@file map.h
@author entire team
@date 4/5/2023
@brief Main game framework
*/

#ifndef MAP_H
#define MAP_H

void setup_background_palletes();
void setup_background();
void update_hover_character();
void check_cursor_movement();
void move_cursor();
void update_camera();
void add_turn();
void update_gui();
void check_confirm_move();
void map_vblank_routine();
inline void render_second_cursor();
void check_enter_move_mode();
inline void hide_cursor();
void check_exit_move_mode();
void check_win();
void start_enemy_turn();
void advance_phase();
void post_manual_action();
void post_move();
void update_select_attacker_cursor();
void remove_character(uchar index);
void check_confirm_battle();
void check_cancel_battle();
void update_characters();
void update_cursor_color();
void play_game();

#endif