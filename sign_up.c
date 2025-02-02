#include "sign_up.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "main_menu.h"
#include "sign_in.h"
#include<regex.h>
#include "theme_config.h"
#include<time.h>
extern int current_fg_color;
extern int current_bg_color;
void generate_password(char* password) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$-^&*=+.;:,`~";
    int ok = 0;
    srand(time(NULL));
    while (!ok) { 
        int passwordlen = (rand() % 7) + 7;
        for (int i = 0; i < passwordlen; i++) {
            password[i] = charset[rand() % (sizeof(charset) - 1)];
        }
        password[passwordlen] = '\0';
        ok = validate_password(password);
    }
}

int validate_password(char* password) {
    int len = strlen(password), up = 0, low = 0, num = 0;
    if (len < 7) { return 0; }
    for (int i = 0; i < len; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            up = 1;
        } else if (password[i] >= '0' && password[i] <= '9') {
            num = 1;
        } else if (password[i] >= 'a' && password[i] <= 'z') {
            low = 1;
        }
    }
    return (up && low && num);
}
char filepath[200];
int validatr_username(char *username){
    snprintf(filepath, sizeof(filepath), "/mnt/c/shahab/c-test/project/USERS/%s.txt", username);
    FILE *file = fopen(filepath, "r");
    if (file) {
        fclose(file);
        return 0;
    } else {
        file = fopen(filepath, "w");
        return 1;
    }
}
int validate_email(char* email) {
    regex_t regex;
    int reti;
    reti = regcomp(&regex, "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }
    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    }
}

void select_button_signup(struct user_data* user) {
    int x, y;
    int selected_char;

    while (1) {
        getyx(stdscr, y, x);
        refresh();
        selected_char = getch();
        if (selected_char == '\n') {
            break;
        }
        switch (selected_char) {
            case KEY_UP:
                if (y == 23) {
                    mvprintw(23, 31, "Generate Password");
                    mvprintw(23, 120, "Sign In");
                    attron(A_REVERSE);
                    mvprintw(20, 48, " ");
                    attroff(A_REVERSE);
                    move(20, 48);
                } else if (y == 16) {
                    mvprintw(16, 51, " ");
                    attron(A_REVERSE);
                    mvprintw(12, 51, " ");
                    attroff(A_REVERSE);
                    move(12, 51);
                } else if (y == 20) {
                    mvprintw(20, 48, " ");
                    attron(A_REVERSE);
                    mvprintw(16, 51, " ");
                    attroff(A_REVERSE);
                    move(16, 51);
                }
                break;
            case KEY_DOWN:
                if (y == 12) {
                    mvprintw(12, 51, " ");
                    attron(A_REVERSE);
                    mvprintw(16, 51, " ");
                    attroff(A_REVERSE);
                    move(16, 51);
                } else if (y == 20) {
                    mvprintw(20, 48, " ");
                    attron(A_REVERSE);
                    mvprintw(23, 31, "Generate Password");
                    attroff(A_REVERSE);
                    move(23, 31);
                } else if (y == 16) {
                    mvprintw(16, 51, " ");
                    attron(A_REVERSE);
                    mvprintw(20, 48, " ");
                    attroff(A_REVERSE);
                    move(20, 48);
                }
                break;
            case KEY_LEFT:
                if (y == 23 && x == 120) {
                    mvprintw(23, 120, "Sign In");
                    attron(A_REVERSE);
                    mvprintw(23, 31, "Generate Password");
                    attroff(A_REVERSE);
                    move(23, 31);
                }
                break;
            case KEY_RIGHT:
                if (y == 23 && x == 31) {
                    mvprintw(23, 31, "Generate Password");
                    attron(A_REVERSE);
                    mvprintw(23, 120, "Sign In");
                    attroff(A_REVERSE);
                    move(23, 120);
                }
                break;
            default:
                break;
        }
        refresh();
    }
}

void display_sign_up(struct user_data* user) {
    initscr();
    keypad(stdscr, TRUE);
    draw_horizontal_line(24, 30, 100);
    draw_horizontal_line(9, 30, 101);
    draw_vertical_line(10, 130, 15);
    draw_vertical_line(10, 30, 15);
    mvprintw(12, 31, "Enter your username:");
    mvprintw(16, 31, "Enter your password:");
    mvprintw(20, 31, "Enter your email:");
    mvprintw(23, 31, "Generate Password");
    mvprintw(23, 120, "Sign In");
    attron(A_REVERSE);
    mvprintw(12, 51, " ");
    attroff(A_REVERSE);
    move(12, 50);
    refresh();
    noecho();
    select_button_signup(user);
    echo();
    int x = 0, y = 0;
    getyx(stdscr, y, x);
    
    if (y == 12) {
        move(12, 51);
        echo();
        getstr(user->user_name);
        while(!validatr_username(user->user_name)) {
            mvprintw(12, 51, "                                              ");
            mvprintw(14, 31, "Username is already in use. Try again");
            move(12, 51);
            getstr(user->user_name);
        }
        mvprintw(14, 31, "                                                   ");
        move(16, 51);
        getstr(user->user_password);
        while (!validate_password(user->user_password)) {
            mvprintw(16, 51, "                                              ");
            mvprintw(18, 31, "Invalid password. Enter again");
            move(16, 51);
            getstr(user->user_password);
        }
        mvprintw(18, 31, "                                              ");
        move(20, 48);
        echo();
        getstr(user->user_email);
        while (!validate_email(user->user_email)) {
            mvprintw(20, 48, "                                               ");
            mvprintw(22, 31, "Invalid email. Enter again");
            move(20, 48);
            getstr(user->user_email);
        }
        mvprintw(22, 31, "                                               ");
        FILE *file=fopen(filepath,"w");
        fprintf(file, "%s\n",user->user_name);
        fprintf(file, "%s\n", user->user_password);
        fprintf(file, "%s\n",user->user_email);
        fclose(file);
        display_sign_in(user);
    } else if (y == 16) {
        mvprintw(16, 51, " ");
        move(16, 51);
        getstr(user->user_password);
        while (!validate_password(user->user_password)) {
            mvprintw(16, 51, "                                               ");
            mvprintw(18, 31, "Invalid password. Enter again");
            move(16, 51);
            getstr(user->user_password);
        }
        mvprintw(18,51, "                                              ");
        move(12, 51);
        echo();
        getstr(user->user_name);
        while(!validatr_username(user->user_name)) {
            mvprintw(12, 51, "                                               ");
            mvprintw(14, 31, "Username is already in use. Try again");
            move(12, 51);
            getstr(user->user_name);
        }
         mvprintw(14, 51, "                                        ");
        move(20, 48);
        echo();
        getstr(user->user_email);
        while (!validate_email(user->user_email)) {
            mvprintw(20, 48, "                                               ");
            mvprintw(22, 31, "Invalid email. Enter again");
            move(20, 48);
            getstr(user->user_email);
        }
        mvprintw(22, 31, "                                         ");
        FILE *file=fopen(filepath,"w");
        fprintf(file, "%s\n",user->user_name);
        fprintf(file, "%s\n", user->user_password);
        fprintf(file, "%s\n",user->user_email);
        fclose(file);
        display_sign_in(user);
    } else if (y == 20) {
        move(20, 48);
        echo();
        getstr(user->user_email);
        while (!validate_email(user->user_email)) {
            mvprintw(20, 48, "                                               ");
            mvprintw(22, 31, "Invalid email. Enter again");
            move(20, 48);
            getstr(user->user_email);
        }
        mvprintw(22, 31, "                                               ");
        move(12, 51);
        echo();
        getstr(user->user_name);
        while(!validatr_username(user->user_name)) {
            mvprintw(12, 51, "                                              ");
            mvprintw(14, 31, "Username is already in use. Try again");
            move(12, 51);
            getstr(user->user_name);
        }
        mvprintw(14, 31, "                                               ");
        move(16, 51);
        getstr(user->user_password);
        while (!validate_password(user->user_password)) {
            mvprintw(16, 51, "                                                 ");
            mvprintw(18, 31, "Invalid password. Enter again");
            move(16, 51);
            getstr(user->user_password);
        }
        mvprintw(18, 31, "                                               ");
        FILE *file=fopen(filepath,"w");
        fprintf(file, "%s\n",user->user_name);
        fprintf(file, "%s\n", user->user_password);
        fprintf(file, "%s\n",user->user_email);
        fclose(file);
        display_sign_in(user);
    } else if (y == 23 && x == 31) {
        generate_password(user->user_password);
        mvprintw(16, 51, "%s", user->user_password);
        refresh();
        move(12, 51);
        echo();
        getstr(user->user_name);
        while(!validatr_username(user->user_name)) {
            mvprintw(12, 51, "                                              ");
            mvprintw(14, 31, "Username is already in use. Try again");
            move(12, 51);
            getstr(user->user_name);
        }
        mvprintw(14, 31, "                                               ");
        move(20, 48);
        echo();
        getstr(user->user_email);
        while (!validate_email(user->user_email)) {
            mvprintw(20, 48, "                                               ");
            mvprintw(22, 31, "Invalid email. Try again");
            move(20, 48);
            getstr(user->user_email);
        }
        mvprintw(22, 31, "                                               ");
        FILE *file=fopen(filepath,"w");
        fprintf(file, "%s\n",user->user_name);
        fprintf(file, "%s\n", user->user_password);
        fprintf(file, "%s\n",user->user_email);
        fclose(file);
        display_sign_in(user);
    } else if (y == 23 && x == 120) {
        display_sign_in(user);
    }
    refresh();
}
