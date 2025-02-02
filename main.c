#include <ncurses.h>
#include <string.h>
#include "sign_in.h"
#include"main_menu.h"
#include "theme_config.h"
#include <locale.h>
#include <wchar.h>
#include "unicode_support.h"
extern int current_fg_color;
extern int current_bg_color;
struct user_data user;
int main() {
    setlocale(LC_ALL,"");
    initscr();
    keypad(stdscr, TRUE);
    mvprintw(10, 10, "Press any key to open sign-in interface...");
    refresh();
    getch();
    clear();
    refresh();
    
    display_sign_in(&user);                
    if(!strcmp(user.user_password, "abcdefg")) {
        clear();
        display_main_menu();
        refresh();
        getch();
    }

    endwin();
    return 0;
}
