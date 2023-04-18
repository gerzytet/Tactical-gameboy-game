/*
@file multiplayer.h
@author A.L. Seppala
@date 4/5/2023
@brief Multiplayer linking code
*/

#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

void send_joypad();
uint8_t remote_joypad();
void set_handshake_text(const uchar *text);
void multiplayer();

#endif