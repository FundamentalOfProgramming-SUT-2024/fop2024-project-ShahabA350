#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include "sign_in.h"
#include "setting_menu.h"
#include "theme_menu.h"
#include "theme_config.h"
extern int current_fg_color;
extern int current_bg_color;
int mapp_theme=0;
void select_button_theme() {
    int x, y;
    
    // extern int map_theme=0;
    int selected_char;
    move(17,70);

    while (1) {
        getyx(stdscr, y, x);
        refresh();

        selected_char = getch();
        if (selected_char == '\n') {
            if (y == 17 && x == 70) {
                set_theme(0);                
                display_setting_menu();
            } else if (y == 20 && x == 70) {
                set_theme(1); 
                mapp_theme=1;             
                display_setting_menu();
            } else if (y == 23 && x == 70) {
                set_theme(2);              
                display_setting_menu();
            } else if (y == 26 && x == 70) {
                set_theme(3);              
                display_setting_menu();
            }
            break;
        }

        switch (selected_char) {
            case KEY_UP:
                if (y == 20) {
                    mvprintw(20, 70, "Grey");
                    attron(A_REVERSE);
                    mvprintw(17, 70, "White");
                    attroff(A_REVERSE);
                    move(17, 70);
                } else if (y == 23) {
                    mvprintw(23, 70, "Gold");
                    attron(A_REVERSE);
                    mvprintw(20, 70, "Grey");
                    attroff(A_REVERSE);
                    move(20, 70);
                } else if (y == 26) {
                    mvprintw(26, 70, "Light Blue");
                    attron(A_REVERSE);
                    mvprintw(23, 70, "Gold");
                    attroff(A_REVERSE);
                    move(23, 70);
                }
                break;
            case KEY_DOWN:
                if (y == 17) {
                    mvprintw(17, 70, "White");
                    attron(A_REVERSE);
                    mvprintw(20, 70, "Grey");
                    attroff(A_REVERSE);
                    move(20, 70);
                } else if (y == 20) {
                    mvprintw(20, 70, "Grey");
                    attron(A_REVERSE);
                    mvprintw(23, 70, "Gold");
                    attroff(A_REVERSE);
                    move(23, 70);
                } else if (y == 23) {
                    mvprintw(23, 70, "Gold");
                    attron(A_REVERSE);
                    mvprintw(26, 70, "Light Blue");
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

void display_theme_menu() {
    initscr();
    clear();
    refresh();
    keypad(stdscr, TRUE);
    draw_horizontal_line(28, 60, 30);
    draw_horizontal_line(15, 59, 31);
    draw_vertical_line(16, 89, 13);
    draw_vertical_line(16, 59, 13);
    mvprintw(17, 70, "White");
    mvprintw(20, 70, "Grey");
    mvprintw(23, 70, "Gold");
    mvprintw(26, 70, "Light Blue");
    move(17, 70);
    attron(A_REVERSE);
    mvprintw(17, 70, "White");
    attroff(A_REVERSE);

    refresh();
    select_button_theme();

    endwin();
}