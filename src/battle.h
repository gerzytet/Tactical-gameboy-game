/*
@file battle.h
@author entire team
@date 4/16/2023
@brief 
*/

#ifndef BATTLE_H
#define BATTLE_H

uchar determineAdvantage();
void set_attacker_image(uchar index);
void set_defender_image(uchar index);
uchar battle(uchar nAttacker, uchar nDefender);

#endif