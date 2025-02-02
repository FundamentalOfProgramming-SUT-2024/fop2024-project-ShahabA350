#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include "sign_in.h"
#include "setting_menu.h"
#include "difficulty_menu.h"
#include "theme_config.h"
#include "main_game.h"
extern int current_fg_color;
extern int current_bg_color;
void select_button_difficulty() {
    int x, y;
    int selected_char;
    move(17,70);
    while (1) {
        getyx(stdscr, y, x);
        refresh();

        selected_char = getch();
        if (selected_char == '\n') {
            if (y == 17 && x == 70) {
                diff=1;
                display_setting_menu();
            } else if (y == 20 && x == 70) {
                diff=2;
                display_setting_menu();
            } else if (y == 23 && x == 70) {
                diff=3;
                display_setting_menu();
                
            } else if (y == 26 && x == 70) {
                diff=4;
                display_setting_menu();
                
            }
            break;
        }

        switch (selected_char) {
            case KEY_UP:
                if (y == 20) {
                    mvprintw(20, 70, "Easy");
                    attron(A_REVERSE);
                    mvprintw(17, 70, "Peaceful");
                    attroff(A_REVERSE);
                    move(17, 70);
                } else if (y == 23) {
                    mvprintw(23, 70, "Medium");
                    attron(A_REVERSE);
                    mvprintw(20, 70, "Easy");
                    attroff(A_REVERSE);
                    move(20, 70);
                } else if (y == 26) {
                    mvprintw(26, 70, "Hard");
                    attron(A_REVERSE);
                    mvprintw(23, 70, "Medium");
                    attroff(A_REVERSE);
                    move(23, 70);
                }
                break;
            case KEY_DOWN:
                if (y == 17) {
                    mvprintw(17, 70, "Peaceful");
                    attron(A_REVERSE);
                    mvprintw(20, 70, "Easy");
                    attroff(A_REVERSE);
                    move(20, 70);
                } else if (y == 20) {
                    mvprintw(20, 70, "Easy");
                    attron(A_REVERSE);
                    mvprintw(23, 70, "Medium");
                    attroff(A_REVERSE);
                    move(23, 70);
                } else if (y == 23) {
                    mvprintw(23, 70, "Medium");
                    attron(A_REVERSE);
                    mvprintw(26, 70, "Hard");
                    attroff(A_REVERSE);
                    move(26, 70);
                }
                break;
            default:
                break;
        }

        refresh();
    }
}

void display_difficulty_menu() {
    initscr();
    clear();
    refresh();
    keypad(stdscr, TRUE);
    draw_horizontal_line(28, 60, 30);
    draw_horizontal_line(15, 59, 31);
    draw_vertical_line(16, 89, 13);
    draw_vertical_line(16, 59, 13);
    mvprintw(17, 70, "Peaceful");
    mvprintw(20, 70, "Easy");
    mvprintw(23, 70, "Medium");
    mvprintw(26, 70, "Hard");
    move(17, 70);
    attron(A_REVERSE);
    mvprintw(17, 70, "Peaceful");
    attroff(A_REVERSE);

    refresh();
    select_button_difficulty();

    endwin();
}
