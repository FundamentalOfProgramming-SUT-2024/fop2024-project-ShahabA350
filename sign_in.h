#ifndef SIGN_IN_H
#define SIGN_IN_H
#include <ncurses.h>
#include "user_data.h"
void draw_vertical_line(int y, int x, int length);
void draw_horizontal_line(int y, int x, int length);
void select_button_signin(struct user_data* user);
void display_sign_in(struct user_data* user);

#endif
