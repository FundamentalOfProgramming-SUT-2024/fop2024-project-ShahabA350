#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include "main_menu.h"
#include"sign_in.h"
#include "setting_menu.h"
#include "theme_config.h"
#include "main_game.h"
#include "show_scoreboard.h"
extern int current_fg_color;
extern int current_bg_color;
void select_button() {
    int x, y;
    int selected_char;
     move(11,70);
    while (1) {
        getyx(stdscr, y, x);
        refresh();
        selected_char = getch();
        if (selected_char == '\n') {
            if (y == 11 && x == 70) {
                clear();
                refresh();
                play_game(0);
                break;
            } else if (y == 14 && x == 70&&forbid_continue==0) {
                play_game(2);
                break;
            } else if (y == 17 && x == 69) {
                //mvprintw(25, 70, "You selected My profile");
            } else if (y == 20 && x == 69) {
                clear();
                board(15);
                break;
            } else if (y == 23 && x == 70) {
                display_setting_menu();
                break;
            }
        }

        switch (selected_char) {
            case KEY_UP:
                if (y == 14) {
                    mvprintw(14, 70, "Continue");
                    attron(A_REVERSE);
                    mvprintw(11, 70, "New game");
                    attroff(A_REVERSE);
                    move(11, 70);
                } else if (y == 17) {
                    mvprintw(17, 69, "My profile");
                    attron(A_REVERSE);
                    mvprintw(14, 70, "Continue");
                    attroff(A_REVERSE);
                    move(14, 70);
                } else if (y == 20) {
                    mvprintw(20, 69, "ScoreBoard");
                    attron(A_REVERSE);
                    mvprintw(17, 69, "My profile");
                    attroff(A_REVERSE);
                    move(17, 69);
                } else if (y == 23) {
                    mvprintw(23, 70, "Setting");
                    attron(A_REVERSE);
                    mvprintw(20, 69, "ScoreBoard");
                    attroff(A_REVERSE);
                    move(20, 69);
                }
                break;
            case KEY_DOWN:
                if (y == 11) {
                    mvprintw(11, 70, "New game");
                    attron(A_REVERSE);
                    mvprintw(14, 70, "Continue");
                    attroff(A_REVERSE);
                    move(14, 70);
                } else if (y == 14) {
                    mvprintw(14, 70, "Continue");
                    attron(A_REVERSE);
                    mvprintw(17, 69, "My profile");
                    attroff(A_REVERSE);
                    move(17, 69);
                } else if (y == 17) {
                    mvprintw(17, 69, "My profile");
                    attron(A_REVERSE);
                    mvprintw(20, 69, "ScoreBoard");
                    attroff(A_REVERSE);
                    move(20, 69);
                } else if (y == 20) {
                    mvprintw(20, 69, "ScoreBoard");
                    attron(A_REVERSE);
                    mvprintw(23, 70, "Setting");
                    attroff(A_REVERSE);
                    move(23, 70);
                }
                break;
            default:
                break;
        }

        refresh();
    }
}

void display_main_menu() {
    initscr();
    clear();
    refresh();
    keypad(stdscr, TRUE);
    draw_horizontal_line(24, 60, 30);
    draw_horizontal_line(9, 59, 31);
    draw_vertical_line(10, 89, 15);
    draw_vertical_line(10, 59, 15);
      mvprintw(3, 65, "          T~~");
    mvprintw(4, 65, "          |");
    mvprintw(5, 65, "         /\"\\ ");
    mvprintw(6, 65, "  T~~    |'|     T~~");  
    mvprintw(7, 65, "  |     /\"~\"\\    |");
    mvprintw(8, 65, " /\"\\   |     |  /\"\\");
    mvprintw(9, 65, "_|_|___|_____|_|_'_|");

    mvprintw(11, 70, "New game");
    mvprintw(14, 70, "Continue");
    mvprintw(17, 69, "My profile");
    mvprintw(20, 69, "ScoreBoard");
    mvprintw(23, 70, "Setting");
    move(11, 70);
    attron(A_REVERSE);
    mvprintw(11, 70, "New game");
    attroff(A_REVERSE);

    refresh();
    select_button();

    endwin();
}
