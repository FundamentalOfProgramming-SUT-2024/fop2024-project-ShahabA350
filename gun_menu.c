#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include "main_game.h"
#include "gun_menu.h"

void display_gun_menu(int n,int gun_stack[5]) {
    initscr();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(14, COLOR_RED, COLOR_BLACK); 
    WINDOW *gun_win = newwin(20, 80, 10, 35);
    keypad(gun_win, TRUE);
    box(gun_win, 0, 0);
    refresh();
    wrefresh(gun_win);
    char buttons[5];
    int c = 0;

    while (1) {
        mvwprintw(gun_win, 5,0, "RANGED WEAPENS");
        mvwprintw(gun_win, 10,0, "MELEE WEAPENS");
        if (picked_gun == 1) {
        mvwprintw(gun_win,15,32,"PICKED GUN: ⚒ ");
    } else if (picked_gun == 2) {
        mvwprintw(gun_win,15,32,"PICKED GUN: 🗡 ");
    } else if (picked_gun == 3) {
        mvwprintw(gun_win,15,32,"PICKED GUN: 🪄 ");
    } else if (picked_gun == 4) {
        mvwprintw(gun_win,15,32,"PICKED GUN: ➳ ");
    } else if (picked_gun == 5) {
       mvwprintw(gun_win,15,32,"PICKED GUN: ⚔ ");}
        for (int i = 0; i < 5; i++) {
    for (int i = 0; i < 5; i++) {
    if (i == c) {
        wattron(gun_win, A_REVERSE);
    }
    for(int i=0;i<5&&gun_stack[i]>0;i++){
        for(int j=i;j<5&&gun_stack[j]>0;j++){
            if(gun_stack[i]%10>gun_stack[j]%10){
                int temp=gun_stack[i];
                gun_stack[i]=gun_stack[j];
                gun_stack[j]=temp;
            }
        }
    }
    
    if (gun_stack[i]%10 == 1) {
        mvwprintw(gun_win, 10, 20 + i * 10, "⚒ ");
        mvwprintw(gun_win, 8, 20 + i * 10-10, "DAMMAGE/HIT:5");
    } else if (gun_stack[i]%10 == 2) {
        mvwprintw(gun_win, 5, 20 + i * 10, "🗡 ");
        mvwprintw(gun_win, 3, 20 + i * 10-10, "DAMMAGE/HIT:12");
        mvwprintw(gun_win, 2, 20 + i * 10-5, "%d",gun_stack[i]/10);
    } else if (gun_stack[i]%10 == 3) {
        mvwprintw(gun_win, 5, 20 + i * 10, "🪄 ");
        mvwprintw(gun_win, 3, 20 + i * 10-5, "DAMMAGE/HIT:15");
        mvwprintw(gun_win, 2, 20 + i * 10, "%d",gun_stack[i]/10);
    } else if (gun_stack[i]%10 == 4) {
        mvwprintw(gun_win, 5, 20 + i * 10, "➳ ");
        mvwprintw(gun_win, 3, 20 + i * 10, "DAMMAGE/HIT:5");
        mvwprintw(gun_win, 2, 20 + i * 10+5, "%d",gun_stack[i]/10);
    } else if (gun_stack[i]%10 == 5) {
        mvwprintw(gun_win, 10, 20 + i * 10, "⚔ ");
        mvwprintw(gun_win, 8, 20 + i * 10, "DAMMAGE/HIT:10");
    } else {
        mvwprintw(gun_win, 10, 20 + i * 10, "  ");
    }
    if (i == c) {
        wattroff(gun_win, A_REVERSE);
    }
}

}

        // for (int i = n; i < 5; i++) {
        //     wattron(gun_win, COLOR_PAIR(14));
        //     mvwprintw(gun_win, 10, 20 + i * 10, "  ");
        //     wattroff(gun_win, COLOR_PAIR(14));
        // }

        wrefresh(gun_win);
        int selected_char = wgetch(gun_win);
        if (selected_char == 'i' || selected_char == 'I') {
            return;
        }

        if (selected_char == '\n') { 
                    
            if(picked_gun!=0){ mvwprintw(gun_win,1,27,"FIRST,STACK YOUR LAST GUN                ");}
            else if(c==4&&sword==0){mvwprintw(gun_win,1,27,"YOU HAVE NOT FIND SWORD YET                   ");}
            else{picked_gun=gun_stack[c]%10;mvwprintw(gun_win,1,27,"                                      ");}
    
        }
        if(selected_char=='W'||selected_char=='w'){
            picked_gun=0;
        }

        switch (selected_char) {
            case KEY_LEFT:
                c = (c +n-1) % n;
                break;
            case KEY_RIGHT:
                c = (c +1) % n;
                break;
            default:
                break;
        }
    }

    delwin(gun_win);
    clear();
    endwin();
}
