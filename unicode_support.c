#include <wchar.h>
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>

void display_trap(int cy,int cx) {
    setlocale(LC_ALL, "");

    initscr();
    noecho();
    cbreak();
    wchar_t trap = L'∧';
    char mbstr[MB_CUR_MAX];
    int len = wctomb(mbstr, trap);

    if (len != -1) {
        mvprintw(cy, cx, "%s", mbstr);mvprintw(cy,cx,"      ");
    }

    refresh();
    getch();
    endwin();
}
