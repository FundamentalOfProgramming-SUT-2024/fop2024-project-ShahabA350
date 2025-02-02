#include <stdio.h>
#include <ncurses.h>

void draw_triangle(int start_y, int start_x, int height) {
    for (int i = 0; i < height; i++) {
        mvprintw(start_y + i, start_x - i, "/");
        mvprintw(start_y + i, start_x + i, "\\");
        if (i == height - 1) {
            for (int j = -i; j <= i; j++) {
                mvprintw(start_y + i, start_x + j, "_");
            }
        }
    }
}

void break_triangle(int start_y, int start_x, int height) {
    // Left half
    for (int i = 0; i < height; i++) {
        mvprintw(start_y + i, start_x - i - 2, "/");
    }

    // Right half
    for (int i = 0; i < height; i++) {
        mvprintw(start_y + i, start_x + i + 2, "\\");
    }
}

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int height = 5;
    int start_y = 5;
    int start_x = 20;

    draw_triangle(start_y, start_x, height);
    refresh();
    getch();
    clear();

    break_triangle(start_y, start_x, height);
    refresh();
    getch();

    endwin();
    return 0;
}
