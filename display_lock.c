#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include "main_game.h"
#include "display_lock.h"
#include <stdlib.h>
void display_lock() {   
    initscr();
    echo(); 
    curs_set(1);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(222,COLOR_WHITE, 222);
    init_pair(51, 48,COLOR_BLACK );
    init_pair(91,88,COLOR_BLACK);
    init_pair(205, 202, COLOR_BLACK);
    init_pair(223, 220, COLOR_BLACK);
    init_pair(50, COLOR_WHITE   ,48);
    init_pair(90,COLOR_WHITE,88);
    init_pair(204, COLOR_WHITE, 202);
    WINDOW *lock_win = newwin(40, 150, 2, 3);
    keypad(lock_win, TRUE);
    box(lock_win, 0, 0);
    refresh();
    wrefresh(lock_win);
    int x=60,y=5;
    mvwprintw(lock_win,y++, x, "                 (v)   ");
    mvwprintw(lock_win,y++, x, "._________________=___.");
    mvwprintw(lock_win,y++, x, "|  _________________  |");
    mvwprintw(lock_win,y++, x, "| |  MADE IN        | |");
    mvwprintw(lock_win,y++, x, "| |PASSWORD: ____   | |");
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
    if(l>1||diff==4){
        mvwprintw(lock_win,y-20,x+3,"PASSWORD: ____ ");
    }
    wrefresh(lock_win);
    int t1,t2,t3,t4,t5,p1,p2,p3,p4,s1,s2,s3,s4,e1,e2,e3,e4,e5;srand(time(NULL));int year=rand()%26;int yearrand=rand()%2;
    if(yearrand==0){
            mvwprintw(lock_win,y-23,x+13,"%d",2000-year);}
    else{
            mvwprintw(lock_win,y-23,x+13,"%d",2000+year);}
     if(akey>0){mvwprintw(lock_win,16,20, "USE ANCIENT KEY?");}
     int key=wgetch(lock_win);
    while(key!='t'){
        key=wgetch(lock_win);
        if(key=='t'){break;}
        if (key=='r'){mvwprintw(lock_win,y+5,10, "pass1=%d,pass2=%d",password,password2);}
        y=6;
        if(akey!=0){
        mvwprintw(lock_win,y+10, 20, "USE ANCIENT KEY?         ");}
        if(akey!=0&&wgetch(lock_win)=='\n'){
            if(rand()%10==0){
                mvwprintw(lock_win,y+10, 20, "OH-UH , THE KEY IS BROKEN!        ");
                akey--;
                bkey++;
                if(bkey>1){mvwprintw(lock_win,y+12, 13, "BUT LOOK! TWO BROKEN KEYS CAN TURN INTO ONE");
                wgetch(lock_win);
                bkey=0;
                akey++;
                mvwprintw(lock_win,y+12, 20, "                                              ");
                mvwprintw(lock_win,y+10, 20, "                                              ");
                continue;}
            }
            else{unlocked=1;akey--;error=0;done=1;break;}

        }
    mvwprintw(lock_win,y++, x, "._________________=___.");
    mvwprintw(lock_win,y++, x, "|  _________________  |");
    mvwprintw(lock_win,y++, x, "| |  MADE IN        | |");
    mvwprintw(lock_win,y++, x, "| |PASSWORD: ____   | |");
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
    if(l>1||diff==4){
        mvwprintw(lock_win,y-20,x+3,"PASSWORD: ____ ");
    }
    if(yearrand==0){
            mvwprintw(lock_win,y-23,x+13,"%d",2000-year);}
    else{
            mvwprintw(lock_win,y-23,x+13,"%d",2000+year);}
    wrefresh(lock_win);

        wmove(lock_win,y-22,x+13);
        wscanw(lock_win,"%d",&t5);
        if(l>1||diff==4){
            wmove(lock_win,y-20,x+13);
            wscanw(lock_win,"%d",&e5);
        s1=password2%10;
        s2=(password2%100-s1)/10;
        s3=(password2%1000-password2%100)/100;
        s4=(password2%10000-password2%1000)/1000;
        e1=e5%10;
        e2=(e5%100-e1)/10;
        e3=(e5%1000-e5%100)/100;
        e4=(e5%10000-e5%1000)/1000;
        }
        t1=t5%10;
        t2=(t5%100-t1)/10;
        t3=(t5%1000-t5%100)/100;
        t4=(t5%10000-t5%1000)/1000;
        
        p1=password%10;
        p2=(password%100-p1)/10;
        p3=(password%1000-password%100)/100;
        p4=(password%10000-password%1000)/1000;

        
        if(yearrand==0){
            if((t1==p4&&t2==p3&&t3==p2&&t4==p1)&&((l<2)||((1>1)&&e1==s4&&e2==s3&&e3==s2&&e4==s1))){
                wattron(lock_win,COLOR_PAIR(51));                
                mvwprintw(lock_win,y-26, x+17, "(v)");
                wattroff(lock_win,COLOR_PAIR(51)); 
                    wattron(lock_win,COLOR_PAIR(50));
                    mvwprintw(lock_win,y-23, x+3, "                 ");
                    mvwprintw(lock_win,y-22, x+3, "                 ");
                    mvwprintw(lock_win,y-21, x+3, "     SUCCEED!    ");
                    mvwprintw(lock_win,y-20, x+3, "                 ");
                    mvwprintw(lock_win,y-19, x+3, "                 ");
                    mvwprintw(lock_win,y-18, x+3, "_________________");   
                wattroff(lock_win,COLOR_PAIR(50));unlocked=1;wgetch(lock_win);wclear(lock_win);error=0;done=1;break;

            }
            else{error++;}
        }
        else{
            if((t1==p1&&t2==p2&&t3==p3&&t4==p4)&&((l<2)||((1>1)&&e1==s1&&e2==s2&&e3==s3&&e4==s4))){
                wattron(lock_win,COLOR_PAIR(51));                
                mvwprintw(lock_win,y-26, x+17, "(v)");
                wattroff(lock_win,COLOR_PAIR(51)); 
                wattron(lock_win,COLOR_PAIR(50));
                    mvwprintw(lock_win,y-23, x+3, "                 ");
                    mvwprintw(lock_win,y-22, x+3, "                 ");
                    mvwprintw(lock_win,y-21, x+3, "     SUCCEED!    ");
                    mvwprintw(lock_win,y-20, x+3, "                 ");
                    mvwprintw(lock_win,y-19, x+3, "                 ");
                    mvwprintw(lock_win,y-18, x+3, "_________________");
                wattroff(lock_win,COLOR_PAIR(50));unlocked=1;wgetch(lock_win);wclear(lock_win);error=0;done=1;break;}
            else{error++;}
        }
            if(error==1){
            wattron(lock_win,COLOR_PAIR(223));                
                mvwprintw(lock_win,y-26, x+17, "(v)");
                wattroff(lock_win,COLOR_PAIR(223)); 
                wattron(lock_win,COLOR_PAIR(222));
                    mvwprintw(lock_win,y-23, x+3, "                 ");
                    mvwprintw(lock_win,y-22, x+3, "                 ");
                    mvwprintw(lock_win,y-21, x+3, "      WRONG!     ");
                    mvwprintw(lock_win,y-20, x+3, "                 ");
                    mvwprintw(lock_win,y-19, x+3, "                 ");
                    mvwprintw(lock_win,y-18, x+3, "_________________");
                wattroff(lock_win,COLOR_PAIR(222));
            }
            else if(error==2){
            wattron(lock_win,COLOR_PAIR(205));                
                mvwprintw(lock_win,y-26, x+17, "(v)");
                wattroff(lock_win,COLOR_PAIR(205)); 
                wattron(lock_win,COLOR_PAIR(204));
                    mvwprintw(lock_win,y-23, x+3, "                 ");
                    mvwprintw(lock_win,y-22, x+3, "                 ");
                    mvwprintw(lock_win,y-21, x+3, "      WRONG!     ");
                    mvwprintw(lock_win,y-20, x+3, "                 ");
                    mvwprintw(lock_win,y-19, x+3, "                 ");
                    mvwprintw(lock_win,y-18, x+3, "_________________");
                wattroff(lock_win,COLOR_PAIR(204));
            }
            else if(error==3){
            wattron(lock_win,COLOR_PAIR(91));                
                mvwprintw(lock_win,y-26, x+17, "(v)");
                wattroff(lock_win,COLOR_PAIR(91)); 
                wattron(lock_win,COLOR_PAIR(90));
                    mvwprintw(lock_win,y-23, x+3, "                 ");
                    mvwprintw(lock_win,y-22, x+3, "                 ");
                    mvwprintw(lock_win,y-21, x+3, "  SECURITY MODE  ");
                    mvwprintw(lock_win,y-20, x+3, "                 ");
                    mvwprintw(lock_win,y-19, x+3, "                 ");
                    mvwprintw(lock_win,y-18, x+3, "_________________");
                wattroff(lock_win,COLOR_PAIR(90));
                wgetch(lock_win);done=1;wgetch(lock_win);wclear(lock_win);break;
            }
             
        

    } 
    curs_set(0);
    noecho();
    endwin();
}
 
    
