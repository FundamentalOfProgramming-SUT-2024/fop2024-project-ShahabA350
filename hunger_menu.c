#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include "main_game.h"
#include "hunger_menu.h"
void display_hunger_menu(int n,int hunger_bar[60],int food_stack[5],int health_bar[10]) {
    initscr();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(11, COLOR_BLACK, COLOR_RED);
    init_pair(12, COLOR_BLACK, COLOR_YELLOW);
    init_pair(13, COLOR_BLACK, COLOR_GREEN);
    init_pair(14,COLOR_RED,COLOR_BLACK);
    WINDOW *menu_win = newwin(20, 80, 10, 35);
    keypad(menu_win, TRUE);
    box(menu_win, 0, 0);
    refresh();
    wrefresh(menu_win);
    char buttons[5]; 
    int c= 0;
     if(eaten==3){mvwprintw(menu_win,3,29,"THAT APPLE LOOKED SO TONIC               ");}
    else if(eaten==4){mvwprintw(menu_win,3,27,"STRAWBERRIES ARE SO REFRESHING            ");} 
    else if(eaten==1){mvwprintw(menu_win,3,29,"A SMALL CHERRY,SO YUMMY               ");}
    else if(eaten==2){damage();mvwprintw(menu_win,3,29,"EW,THAT CHERRY WAS ROTTEN               ");}
    for (int i = 0; i < 60 && hunger_bar[i] == 1; i++) {
        if (i < 20) {
            wattron(menu_win, COLOR_PAIR(11));
            mvwprintw(menu_win, 1, i + 10, " ");
            wattroff(menu_win, COLOR_PAIR(11));
        } else if (i > 40) {
            wattron(menu_win, COLOR_PAIR(13));
            mvwprintw(menu_win, 1, i + 10, " ");
            wattroff(menu_win, COLOR_PAIR(13));
        } else {
            wattron(menu_win, COLOR_PAIR(12));
            mvwprintw(menu_win, 1, i + 10, " ");
            wattroff(menu_win, COLOR_PAIR(12));
        }
    }
    wrefresh(menu_win);

    
    while (1) {
        if(n==0){
            while(1){
                int selected_char = wgetch(menu_win);
                if(selected_char=='e'||selected_char=='E'){
                    return;
                }
                continue;
            }
            return;
        }
        for (int i = 0; i < n; i++) {
            if (i == c) {
                wattron(menu_win, A_REVERSE);
                if(food_stack[i]==1||food_stack[i]==2){
                mvwprintw(menu_win, 10, 20 + i * 10, "🍒");}
                else if(food_stack[i]==4){
                mvwprintw(menu_win, 10, 20 + i * 10, "🍓");}
                else if(food_stack[i]==3){
                mvwprintw(menu_win, 10, 20 + i * 10, "🍎");}
                wattroff(menu_win, A_REVERSE);
            } else {
                if(food_stack[i]==1||food_stack[i]==2){
                mvwprintw(menu_win, 10, 20 + i * 10, "🍒");}
                else if(food_stack[i]==4){
                mvwprintw(menu_win, 10, 20 + i * 10, "🍓");}
                else if(food_stack[i]==3){
                mvwprintw(menu_win, 10, 20 + i * 10, "🍎");}
            }
        }
        for(int i=n;i<5;i++){
            wattron(menu_win,COLOR_PAIR(14));
            mvwprintw(menu_win, 10, 20 + i * 10, "  ");
            wattroff(menu_win,COLOR_PAIR(14));
        }

        wrefresh(menu_win);
        int selected_char = wgetch(menu_win);
        if(selected_char=='e'||selected_char=='E'){
                    return;
                }

        if (selected_char == '\n') {
            if(food_stack[c]==2){damage();damage();damage();mvwprintw(menu_win,3,29,"EW,THAT CHERRY WAS ROTTEN               ");eaten=2;}
            else{
            for (int h = 0; h < 10; h++) {
                if (health_bar[h] == 0) { 
                    health_bar[h]=1;
                    if(h+1<10){health_bar[h+1]=1;}
                    if(heal_boost&&h<8){health_bar[h+2] = 1;}break;
                }
            }
           
             int t=0;
             for (int h = 0; h <60; h++) {
                if (hunger_bar[h] != 1) {
                    hunger_bar[h] = 1;t++;
                }
                if(t==20){break;}
            }
            if(food_stack[c]==3){damage_boost=10;mvwprintw(menu_win,3,29,"THAT APPLE LOOKED SO TONIC               ");}
            else if(food_stack[c]==4){speed_boost=10;mvwprintw(menu_win,3,29,"STRAWBERRIES ARE SO REFRESHING            ");} 
            else{mvwprintw(menu_win,3,29,"A SMALL CHERRY,SO YUMMY            ");}
            eaten=food_stack[c];
        }
        food_stack[c]=0;
        for(int i=c;i<4;i++){
            food_stack[i]=food_stack[i+1];
        }
        break;
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
        for (int i = 0; i < 60 && hunger_bar[i] == 1; i++) {
        if (i < 20) {
            wattron(menu_win, COLOR_PAIR(11));
            mvwprintw(menu_win, 1, i + 10, " ");
            wattroff(menu_win, COLOR_PAIR(11));
        } else if (i > 40) {
            wattron(menu_win, COLOR_PAIR(13));
            mvwprintw(menu_win, 1, i + 10, " ");
            wattroff(menu_win, COLOR_PAIR(13));
        } else {
            wattron(menu_win, COLOR_PAIR(12));
            mvwprintw(menu_win, 1, i + 10, " ");
            wattroff(menu_win, COLOR_PAIR(12));
        }
        refresh();
    }
    }

    delwin(menu_win);
    clear();
    display_hunger_menu(n-1,hunger_bar,food_stack,health_bar);
    endwin();
}
