/*
@file pathfinding.h
@author entire team
@date 4/16/2023
@brief 
*/

#ifndef PATHFINDING_H
#define PATHFINDING_H

uchar pathfind(uchar startX, uchar startY, uchar endX, uchar endY, uchar dist, uchar consider_adjacent);
uchar move_entity_after_pathfinding(uchar entity, uchar maxMovement, uchar consider_adjacent);
void setup_passable_matrix();

#endif