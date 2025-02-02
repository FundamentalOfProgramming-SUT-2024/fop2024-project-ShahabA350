#ifndef SIGN_UP_H
#define SIGN_UP_H
#include <ncurses.h>
#include "user_data.h"
int validate_email(char* email);
int validatr_username(char *username);
int validate_password(char* password) ;
void select_button_signup(struct user_data* user);
void display_sign_up(struct user_data* user);

#endif
