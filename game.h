
#ifndef GAME_H
#define GAME_H

#include "main.h"

void init_game(void);
void game_handler(int type, int data, BYTE state);

#define MODE_ATTRACT	0
#define MODE_TEST		1
#define MODE_PAUSE		2
#define MODE_CONFUSION	3


#endif // GAME_H
