#ifndef MAP_REVEAL_H
#define MAP_REVEAL_H
extern int l;
#include <ncurses.h>
void reveal_map(int map[5][200][200], int cy, int cx);
void reveal_path(int map[5][200][200], int cy, int cx, int pery, int perx);
#endif
