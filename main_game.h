#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <ncurses.h>
#include <wchar.h>
extern int k;
extern int cx, cy;
extern int map[5][200][200];
extern int revealed[5][200][200];
extern int centers[10][2];
extern int revealed_path[200][200];
int end();
extern int g;
extern int l;
extern int stairs;
extern int coin;
extern int score;
extern int unlocked;
extern int password;
extern int password2;
extern int error;
extern int done;
extern int picked_gun;
extern int diff;
extern int akey,bkey;
extern int potion_stack[3];
extern int gun_stack[5];
extern int potions,allcoin;
extern int themed[5][200][200];
extern int sword,heal_boost,damage_boost,speed_boost,heal_boost,eaten,forbid_continue;
extern int picked_potion,endisnear,xp,finished,health_bar[10],food_stack[5],hunger_bar[60],levels[5];
void draw_rectangle(int l, int w, int map[5][200][200], int index);
void create_path(int x1, int y1, int x2, int y2);
void create_junction(int x1, int y1, int x2, int y2, int x3, int y3);
void reveal_map(int map[5][200][200], int cy, int cx);
void reveal_path(int map[5][200][200], int cy, int cx, int pery, int perx);
void move_hero(int cy, int cx);
void play_game(int continue_game);
void damage();
#endif
