#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include "main_game.h"
void display_lock() {
    initscr();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(11, COLOR_WHITE, COLOR_RED);
    init_pair(12, COLOR_WHITE, COLOR_YELLOW);
    init_pair(13, COLOR_WHITE, COLOR_GREEN);
    init_pair(14,COLOR_RED,COLOR_BLACK);
    WINDOW *lock_win = newwin(40, 150, 2, 3);
    keypad(lock_win, TRUE);
    box(lock_win, 0, 0);
    refresh();
    wrefresh(lock_win);
    int x=60,y=5;
    mvwprintw(lock_win,y++, x, "._____________________.");
    mvwprintw(lock_win,y++, x, "|  _________________  |");
    mvwprintw(lock_win,y++, x, "| |                 | |");
    mvwprintw(lock_win,y++, x, "| |                 | |");
    mvwprintw(lock_win,y++, x, "| |                 | |");
    mvwprintw(lock_win,y++, x, "| |                 | |");
    mvwprintw(lock_win,y++, x, "| |                 | |");
    mvwprintw(lock_win,y++, x, "| |_________________| |");
    mvwprintw(lock_win,y++, x, "|                     |");
    mvwprintw(lock_win,y++, x, "|                     |");
    mvwprintw(lock_win,y++, x, "| |__|__|__|__|__|__| |");
    mvwprintw(lock_win,y++, x, "| |__|__|__|__|__|__| |");
    mvwprintw(lock_win,y++, x, "| |__|__|__|__|__|__| |");
    mvwprintw(lock_win,y++, x, "| |__|__|__|__|__|__| |");
    mvwprintw(lock_win,y++, x, "| |__|__|__|__|__|__| |");
    mvwprintw(lock_win,y++, x, "|  ___ ___ ___   ___  |");
    mvwprintw(lock_win,y++, x, "| | 7 | 8 | 9 | |ENT| |");
    mvwprintw(lock_win,y++, x, "| |___|___|___| |___| |");
    mvwprintw(lock_win,y++, x, "| | 4 | 5 | 6 | |DLT| |");
    mvwprintw(lock_win,y++, x, "| |___|___|___| |___| |");
    mvwprintw(lock_win,y++, x, "| | 1 | 2 | 3 | |CNS| |");
    mvwprintw(lock_win,y++, x, "| |___|___|___| |___| |");
    mvwprintw(lock_win,y++, x, "| | . | 0 | = | |RST| |");
    mvwprintw(lock_win,y++, x, "| |___|___|___| |___| |");
    mvwprintw(lock_win,y++, x, "|_____________________|");
    wrefresh(lock_win);
    getch(); 
    endwin();
}
 
    
