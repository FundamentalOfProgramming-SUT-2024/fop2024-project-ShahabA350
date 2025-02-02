#include <ncurses.h>

void print_with_red_percent(int row, const char* str) {
    int col = 0;
    while (*str) {
        if (*str == '%') {
            attron(COLOR_PAIR(1));
            mvprintw(row, col, "%%");
            attroff(COLOR_PAIR(1));
        } else {
            mvprintw(row, col, "%c", *str);
        }
        str++;
        col++;
    }
}

int main() {
    initscr();            // Start ncurses mode
    start_color();        // Enable color functionality
    init_pair(1, COLOR_RED, COLOR_BLACK); // Define color pair

    noecho();            
    curs_set(FALSE);    

    mvprintw(1, 0, "                           ,--.");
    mvprintw(2, 0, "                          {    }");
    mvprintw(3, 0, "                          K,   }");
    mvprintw(4, 0, "                         /  `Y`");
    mvprintw(5, 0, "                    _   /   /");
    mvprintw(6, 0, "                   {_'-K.__/");
    mvprintw(7, 0, "                     `/-.__L._");
    mvprintw(8, 0, "                     /  ' /`\\_}");
    mvprintw(9, 0, "                    /  ' /     -ART BY ZEUS-");
    mvprintw(10, 0, "            ____   /  ' /");
    mvprintw(11, 0, "     ,-'~~~~    ~~/  ' /_");
    print_with_red_percent(12, "   ,'             ``~~~%%',");
    print_with_red_percent(13, "  (                     %%  Y");
    print_with_red_percent(14, " {                      %% I");
    print_with_red_percent(15, "{      -                 %%  `.");
    print_with_red_percent(16, "|       ',                %%  )");
    mvprintw(17, 0, "|        |   ,..__      __. Y");
    mvprintw(18, 0, "|    .,_./  Y ' / ^Y   J   )|");
    mvprintw(19, 0, "\\           |' /   |   |   ||");
    mvprintw(20, 0, " \\          L_/    . _ (_,.'(");
    mvprintw(21, 0, "  \\,   ,      ^^\"\"' / |      )");
    mvprintw(22, 0, "    \\_  \\          /,L]     /");
    mvprintw(23, 0, "      '-_`-,       ` `   ./`");
    mvprintw(24, 0, "         `-(_            )");
    mvprintw(25, 0, "             ^^\\..___,.--`");

    refresh();           
    getch();          
    endwin();             
    return 0;
}
