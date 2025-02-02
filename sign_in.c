#include <ncurses.h>
#include "sign_in.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include "main_menu.h"
#include "sign_up.h"
#include "theme_config.h"
#include "user_data.h"
#include "main_game.h"
extern int current_fg_color;
extern int current_bg_color;

void draw_vertical_line(int y, int x, int length) {
    for (int i = y; i < length + y; i++) {
        mvprintw(i, x, "|");
    }
}

void draw_horizontal_line(int y, int x, int length) {
    mvhline(y, x, '_', length);
}

void select_button_signin(struct user_data* user) {
    int x, y;
    int selected_char;

    while (1) {
        getyx(stdscr, y, x);

        refresh();

        selected_char = getch();
        if (selected_char == '\n') {
            break;
        }

        switch (selected_char) {
            case KEY_UP:
                if (y == 16) {
                    mvprintw(16, 51, "                                         ");
                    attron(A_REVERSE);
                    mvprintw(12, 51, " ");
                    attroff(A_REVERSE);
                    move(12, 51);
                } else if (y == 23) {
                    mvprintw(23, 31, "Forgot your password?");
                    mvprintw(23, 72, "play as a guest");
                    mvprintw(23, 120, "Sign up");
                    attron(A_REVERSE);
                    mvprintw(16, 51, " ");
                    attroff(A_REVERSE);
                    move(16, 51);
                }
                break;
            case KEY_DOWN:
                if (y == 12) {
                    mvprintw(12, 51, "                               ");
                    attron(A_REVERSE);
                    mvprintw(16, 51, " ");
                    attroff(A_REVERSE);
                    move(16, 51);
                } else if (y == 16) {
                    mvprintw(16, 51, "                               ");
                    attron(A_REVERSE);
                    mvprintw(23, 31, "Forgot your password?");
                    attroff(A_REVERSE);
                    move(23, 31);
                }
                break;
            case KEY_LEFT:
                if (y == 23 && x == 72) {
                    mvprintw(23, 72, "play as a guest");
                    attron(A_REVERSE);
                    mvprintw(23, 31, "Forgot your password?");
                    attroff(A_REVERSE);
                    move(23, 31);
                } else if (y == 23 && x == 120) {
                    mvprintw(23, 120, "Sign up");
                    attron(A_REVERSE);
                    mvprintw(23, 72, "play as a guest");
                    attroff(A_REVERSE);
                    move(23, 72);
                }
                break;
            case KEY_RIGHT:
                if (y == 23 && x == 31) {
                    mvprintw(23, 31, "Forgot your password?");
                    attron(A_REVERSE);
                    mvprintw(23, 72, "play as a guest");
                    attroff(A_REVERSE);
                    move(23, 72);
                } else if (y == 23 && x == 72) {
                    mvprintw(23, 72, "play as a guest");
                    attron(A_REVERSE);
                    mvprintw(23, 120, "Sign up");
                    attroff(A_REVERSE);
                    move(23, 120);
                }
                break;
            default:
                break;
        }

        refresh();
    }
}
void display_sign_in(struct user_data* user) {
    
    initscr();
    curs_set(0);
    clear();
    refresh();
    keypad(stdscr, TRUE);
    draw_horizontal_line(24, 30, 100);
    draw_horizontal_line(9, 30, 101);
    draw_vertical_line(10, 130, 15);
    draw_vertical_line(10, 30, 15);
    mvprintw(12, 31, "Enter your username:");
    mvprintw(16, 31, "Enter your password:");
    mvprintw(23, 31, "Forgot your password?");
    mvprintw(23, 72, "play as a guest");
    mvprintw(23, 120, "Sign up");
    move(12, 51);
    attron(A_REVERSE);
    mvprintw(12, 51, " ");
    attroff(A_REVERSE);
    refresh();
    noecho();
    select_button_signin(user);
    echo();
    int x = 0, y = 0;
    getyx(stdscr, y, x);
    int ok=0,fine=0;
while(!ok){
    if (y == 12) {
        fine=1;
        move(12, 51);
        echo();
        getstr(user->user_name);
        move(16, 51);
        echo();
        getstr(user->user_password);
    } else if (y == 16) {
        fine=1;
        mvprintw(16, 51, " ");
        move(16, 51);
        echo();
        getstr(user->user_password);
        move(12, 51);
        echo();
        getstr(user->user_name);}
    if(fine){
        char filepath[200];
        snprintf(filepath, sizeof(filepath), "/mnt/c/shahab/c-test/project/USERS/%s.txt",user->user_name);
        FILE *file=fopen(filepath,"r");
        if(file==NULL){
            mvprintw(12, 51, "                                                       ");
            mvprintw(16, 51, "                                                       ");
            mvprintw(14,60,"Incorrect username,try again.");
            continue;}
        char line[1000];
        char fakeline[1000];
        char saved[1000];
        fgets(fakeline, sizeof(fakeline), file);
        fgets(line, sizeof(line), file);
        fgets(fakeline,sizeof(fakeline),file);
        if (fgets(saved, sizeof(saved), file) == NULL) {
            forbid_continue=1;      
        }
        else{forbid_continue=0;}
        line[strcspn(line, "\n")] = '\0';
        int cmp=strcmp(user->user_password,line);
        if(!cmp){
            ok=1;
        }
        fclose(file);
        if(ok){
            display_main_menu();
        } else {
            mvprintw(12, 51, "                                                       ");
            mvprintw(16, 51, "                                                       ");            
            mvprintw(14,60,"Incorrect password,try again.");
        }
    }
    else{break;}
}
if (y == 23 && x == 31) {
    mvprintw(24,30,"\\  ");
    draw_vertical_line(25,31,9);
    draw_vertical_line(25,32,7);
    draw_horizontal_line(33,32,2);
    draw_horizontal_line(31,33,1);
    draw_vertical_line(28,34,4);
    draw_vertical_line(34,34,4);
    draw_horizontal_line(27,35,70);
    draw_horizontal_line(37,35,70);
    draw_vertical_line(28,105,10);
    mvprintw(28,35,"Hello there,stranger!We do not like our heroe's information to spread");
    mvprintw(29,35,"among the monsters;Are you sure you are not one of thoses?");
    mvprintw(33,58,"Yes");
    mvprintw(33,80,"No");
    attron(A_REVERSE);
    mvprintw(33,80, "No");
    attroff(A_REVERSE);
    refresh();
    int yes=0;
    while(1){
        int selected=getch();
        if(selected=='\n'){
            break;
        }
    switch (selected)
    {
    case KEY_RIGHT:
        yes=0;        
        mvprintw(33,58,"Yes");
        attron(A_REVERSE);
        mvprintw(33,80, "No");
        attroff(A_REVERSE);     
        refresh();           
        break;
    case KEY_LEFT:
        yes=1;
        mvprintw(33,80, "No");
        attron(A_REVERSE);
        mvprintw(33,58,"Yes");
        attroff(A_REVERSE);
        refresh();
        break;         
    default:
        break;
    }
    }  
    if(yes){
        mvprintw(28,35,"                                                                      ");
        mvprintw(29,35,"                                                               ");
        mvprintw(33,35,"                                                        ");
        mvprintw(30,35,"Enter your username:");
         while(1){
        char filepath[200],line[200],fakeline[200];
        getstr(user->user_name);
        snprintf(filepath, sizeof(filepath), "/mnt/c/shahab/c-test/project/USERS/%s.txt",user->user_name);
        FILE *file=fopen(filepath,"r");
        if(file==NULL){
            mvprintw(30, 56,"                                                 ");
            mvprintw(33,55,"Incorrect username,try again");
            move(30,55);
            continue;}
        else{fgets(fakeline, sizeof(fakeline), file);
            fgets(line, sizeof(line), file);
            line[strcspn(line, "\n")] = '\0';
             mvprintw(33, 45,"                                                 ");
            mvprintw(33,45,"here %s keep it safe from monsters :)",line);
            mvprintw(36,55,"press 'C' to continue");
            fclose(file);  
            break;}
         }    
    }
    else if(!yes){
        mvprintw(33,45,"One day , We will find you...                    ");
        getch();
        return;
    }
    refresh();
    noecho();
    int restart=getchar();
    while(restart!='C'&&restart!='c'){
        restart=getchar();
        continue;
    }
    display_sign_in(user);

} else if (y == 23 && x == 72) {
    clear();
    refresh();
    display_main_menu();
} else if (y == 23 && x == 120) {
    clear();
    refresh();
    display_sign_up(user);
}
refresh();
endwin();
}