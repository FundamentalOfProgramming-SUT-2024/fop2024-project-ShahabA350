#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include "main_game.h"
#include "potion_menu.h"

void display_potion_menu(int n, int potion_stack[3]) {
    initscr();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(14, COLOR_RED, COLOR_BLACK); 
    WINDOW *potion_win = newwin(20, 80, 10, 35);
    keypad(potion_win, TRUE);
    box(potion_win, 0, 0);
    refresh();
    wrefresh(potion_win);
    char buttons[3];
    int c = 0;

    while (1) {
        if (picked_potion == 1) {
            mvwprintw(potion_win, 15, 32, "PICKED POTION: 🧉 ");
        } else if (picked_potion == 2) {
            mvwprintw(potion_win, 15, 32, "PICKED POTION: 🧪 ");
        } else if (picked_potion == 3) {
            mvwprintw(potion_win, 15, 32, "PICKED POTION: 🔮 ");
        }
        
        for (int i = 0; i < 3; i++) {
            if (i == c) {
                wattron(potion_win, A_REVERSE);
            }
            if (potion_stack[i]%10 == 1) {
                mvwprintw(potion_win, 10, 20 + i * 10, "🧉 ");
                mvwprintw(potion_win, 7, 16 + i * 10, "HEAL SPELL");
                mvwprintw(potion_win, 5, 21 + i * 10, "%d",potion_stack[i]/10);

            } else if (potion_stack[i]%10 == 2) {
                mvwprintw(potion_win, 10, 30 + i * 10, "🧪 ");
                mvwprintw(potion_win, 7, 26 + i * 10, "SPEED SPELL");
                mvwprintw(potion_win, 5, 31 + i * 10, "%d",potion_stack[i]/10);
            } else if (potion_stack[i]%10 == 3) {
                mvwprintw(potion_win, 10, 40 + i * 10, "🔮 ");
                mvwprintw(potion_win, 7, 35 + i * 10, "DAMAGE SPELL");
                mvwprintw(potion_win, 5, 41 + i * 10, "%d",potion_stack[i]/10);
            } else {
                mvwprintw(potion_win, 10, 20 + i * 10, "  ");
            }
            if (i == c) {
                wattroff(potion_win, A_REVERSE);
            }
        }

        wrefresh(potion_win);
        int selected_char = wgetch(potion_win);
        if (selected_char == 'o' || selected_char == 'O') {
            return;
        }

        if (selected_char == '\n') {     
            picked_potion = potion_stack[c]%10;
        }

        switch (selected_char) {
            case KEY_LEFT:
                c = (c + n - 1) % n;
                break;
            case KEY_RIGHT:
                c = (c + 1) % n;
                break;
            default:
                break;
        }
    }

    delwin(potion_win);
    clear();
    endwin();
}
