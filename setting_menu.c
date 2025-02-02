#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include "main_menu.h"
#include "sign_in.h"
#include "setting_menu.h"
#include "theme_menu.h"
#include "difficulty_menu.h"
#include "theme_config.h"
#include "music.h"
extern int current_fg_color;
extern int current_bg_color;
void select_button_setting() {
    int x, y;
    int selected_char;
    move(17, 70);
    while (1) {
        getyx(stdscr, y, x);
        refresh();

        selected_char = getch();
        if (selected_char == '\n') {
            if (y == 17 && x == 70) {
                display_theme_menu();
            } else if (y == 20 && x == 70) {
                clear();
                display_music_menu();
            } else if (y == 23 && x == 70) {
                display_difficulty_menu();
            } else if (y == 26 && x == 70) {
                display_main_menu();
                break;
            }
            break;
        }

        switch (selected_char) {
            case KEY_UP:
                if (y == 20) {
                    mvprintw(20, 70, "Music");
                    attron(A_REVERSE);
                    mvprintw(17, 70, "Theme");
                    attroff(A_REVERSE);
                    move(17, 70);
                } else if (y == 23) {
                    mvprintw(23, 70, "Difficulty");
                    attron(A_REVERSE);
                    mvprintw(20, 70, "Music");
                    attroff(A_REVERSE);
                    move(20, 70);
                } else if (y == 26) {
                    mvprintw(26, 70, "Exit");
                    attron(A_REVERSE);
                    mvprintw(23, 70, "Difficulty");
                    attroff(A_REVERSE);
                    move(23, 70);
                }
                break;
            case KEY_DOWN:
                if (y == 17) {
                    mvprintw(17, 70, "Theme");
                    attron(A_REVERSE);
                    mvprintw(20, 70, "Music");
                    attroff(A_REVERSE);
                    move(20, 70);
                } else if (y == 20) {
                    mvprintw(20, 70, "Music");
                    attron(A_REVERSE);
                    mvprintw(23, 70, "Difficulty");
                    attroff(A_REVERSE);
                    move(23, 70);
                } else if (y == 23) {
                    mvprintw(23, 70, "Difficulty");
                    attron(A_REVERSE);
                    mvprintw(26, 70, "Exit");
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

void display_setting_menu() {
    initscr();
    start_color(); 
    init_pair(1, current_fg_color, current_bg_color); 
    bkgd(COLOR_PAIR(1));
    clear();
    refresh();
    keypad(stdscr, TRUE);
    draw_horizontal_line(28, 60, 30);
    draw_horizontal_line(15, 59, 31);
    draw_vertical_line(16, 89, 13);
    draw_vertical_line(16, 59, 13);
    mvprintw(9, 66, " _   _   _   _   _");
    mvprintw(10, 66, "  |_| |_| |_| |_|");
    mvprintw(11, 66, "            '  ");
    mvprintw(12, 66, "       `       -  ");
    mvprintw(5, 61, " __  __ ");
    mvprintw(6, 61, " ||__|| ");
    mvprintw(7, 61, " |   '| ");
    mvprintw(8, 61, " | '  | ");
    mvprintw(9, 61, " |____| ");
    mvprintw(10,61, "  |  |__");
    mvprintw(11,61, "  | '|  ");
    mvprintw(12,61, "  |  |  ");
    mvprintw(13,61, "  | '|  ");
    mvprintw(14,61, "  |' |  ");
    mvprintw(15,61, "__|__|__");
    mvprintw(5, 81, " __  __ ");
    mvprintw(6, 81, " ||__|| ");
    mvprintw(7, 81, " |    | ");
    mvprintw(8, 81, " |  ' | ");
    mvprintw(9, 81, " |____| ");
    mvprintw(10,81, "__|  |  ");
    mvprintw(11,81, "  |' |  ");
    mvprintw(12,81, "  |  |  ");
    mvprintw(13,81, "  | '|  ");
    mvprintw(14,81, "  |' |  ");
    mvprintw(15,81, "__|__|__");
    mvprintw(17, 70, "Theme");
    mvprintw(20, 70, "Music");
    mvprintw(23, 70, "Difficulty");
    mvprintw(26, 70, "Exit");
    move(17, 70);
    attron(A_REVERSE);
    mvprintw(17, 70, "Theme");
    attroff(A_REVERSE);

    refresh();
    select_button_setting();

    endwin();
}
