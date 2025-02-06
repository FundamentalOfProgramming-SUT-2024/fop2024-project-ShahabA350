#ifndef SAVE_GAME_STATE_H
#define SAVE_GAME_STATE_H
#include <stdlib.h>
#include <time.h>  
#include "sign_up.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "user_data.h"
#include <stdio.h>
#include "main_menu.h"
#include "sign_in.h"
void save_game_state(struct user_data user, int map[6][200][200], int revealed[6][200][200], int revealed_path[200][200], int centers[10][2], int health_bar[10], int food_stack[5], int hunger_bar[60], int cx, int cy,int l,int levels[5]);

#endif 
