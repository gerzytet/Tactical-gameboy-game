/*
@file credits.c
@author entire team
@date 3/22/2023
@brief Placeholder, but will be the end credits
*/

#include "common.h"
#include "gb/gb.h"
#include "gb/cgb.h"
#include "../graphics/palettes.c"

void play_credits(){
	game_mode = MODE_CREDITS;
	set_bkg_palette(0, 1, colors);
	move_bkg(0,0);
	
	printf("Thank you for playing our game!\nHope you enjoyed it!");

    while(1){
		if (joy_impulse & J_B){
			return;
		}
	}
}