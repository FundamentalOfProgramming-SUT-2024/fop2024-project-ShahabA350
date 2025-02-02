#ifndef MUSIC_H
#define MUSIC_H

#include <ncurses.h>
void print_music_menu( int starty,int startx,int highlight, char **choices, int n_choices);
char* display_music();
void display_music_menu();
void play_music(const char *filepath);

#endif
