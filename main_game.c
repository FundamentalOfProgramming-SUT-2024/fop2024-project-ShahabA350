#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <locale.h>
#include "main_game.h"
#include "main_menu.h"
#include "theme_config.h"
#include "reveal_map.h"
#include "hunger_menu.h"
#include "save_game.h"
#include "sign_in.h"
#include "sign_in.h"
#include "user_data.h"
#include "load_game.h"
#include "theme_menu.h"
#include "scoreboard.h"
#include <unistd.h>
#include <pthread.h>
#include <stddef.h>
#include "display_lock.h"
#include "gun_menu.h"
#include "difficulty_menu.h"
#include "potion_menu.h"
#include <unistd.h>
#include "clash_room.h"
#include "music.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "boss_fight.h"
int k = 0, cx, cy, secret = 0, m = 0, foods = 0, eat = 0, coin = 0, score, forbidden = 0, placed = 0, crand, poison_m = 0, sickness = 0, health_m = 0, akey = 0, bkey = 0,
    healness = 0, trap_m, firsttime = 0, locked = 0, firstlock = 1, bplaced = 0, unlocked = 0, password = 9999, password2 = 9999, gofornext = 0, buttony, buttonx,
    error = 0, done = 0, picked_gun = 1, guns = 5, diff = 3, kplaced = 0,potion_stack[3]={1,2,3},potions=3,picked_potion=1,t_room=0,trand,endisnear=0,ends=0,allcoin=0,
    xp=0,finished=0,myturn=0,direction=0,arrowy,dagger_limit=0,arrow_limit=0,arrowx,wound_limit=0,sword=0,heal=0,heal_boost=0,speed_boost=0,damage_boost=0,repeat,eaten=0,
    rott_limit[5]={0,0,0,0,0},win=0,forbid_continue=1,clashed=0,beforel=0,beforecy=0,beforecx=0,musicplay=0,damage_to_boss=0,boss_defeated=0;
int l = 0;
int levels[5] = {0, 0, 0, 0, 0};
int map[6][200][200];
int themed[6][200][200];
int revealed[6][200][200];
int centers[10][2];
int revealed_path[200][200];
int health_bar[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int food_stack[5] = {0, 0, 0, 0, 0};
int hunger_bar[60] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int brand;
int gun_stack[5] = {1, 2, 3, 4, 5};
int enemy_health[6][200][200];
int movable[6][200][200];
void *timer_function(void *arg)
{
    init_pair(202, 202, COLOR_BLACK);
    if (gofornext == 2)
    {
        for (int i = 5; i >= 0; i--)
        {
            mvprintw(44, 55, " %d", i);
            refresh();
            sleep(1);
        }
        mvprintw(44, 40, "                         ");
        gofornext = 0;
        refresh();
        pthread_exit(NULL);
    }
    else if (gofornext == 0)
    {
        gofornext = 1;
        for (int i = 5; i >= 0; i--)
        {
            mvprintw(42, 55, " %d", i);
            refresh();
            sleep(1);
        }
        gofornext = 0;
        mvprintw(42, 40, "                         ");
        refresh();
        for (int i = 10; i >= 0; i--)
        {
            sleep(1);
        }
        if (rand() % 2)
        {
            mvprintw(0, 0, "PASSWORD CHANGED!");
            password2 = 9999;
            password = 9999;
        }
        pthread_exit(NULL);
    }
}
void draw_rectangle(int ll, int w, int map[6][200][200], int index)
{
    int chrand = rand() % 100;
    int temptheme = 0;
    if (diff == 4)
    {
        if (chrand % 3 == 0)
        {
            temptheme = 0;
        }
        else if (chrand < 2)
        {
            temptheme = 3;
        }
        else if (chrand < 40)
        {
            temptheme = 4;
        }
        else if (chrand < 100)
        {
            temptheme = 5;
        }
    }
    else if (diff == 2)
    {
        if (chrand % 2 == 0)
        {
            temptheme = 0;
        }
        else if (chrand < 40)
        {
            temptheme = 3;
        }
        else if (chrand < 80)
        {
            temptheme = 4;
        }
        else if (chrand < 100)
        {
            temptheme = 5;
        }
    }
    else if (diff == 1)
    {
        if (chrand % 2 == 0)
        {
            temptheme = 0;
        }
        else if (chrand < 80)
        {
            temptheme = 3;
        }
        else if (chrand < 98)
        {
            temptheme = 4;
        }
        else if (chrand < 100)
        {
            temptheme = 5;
        }
    }
    else
    {
        if (chrand % 2 == 0)
        {
            temptheme = 0;
        }
        else if (chrand < 33)
        {
            temptheme = 3;
        }
        else if (chrand < 66)
        {
            temptheme = 4;
        }
        else if (chrand < 100)
        {
            temptheme = 5;
        }
    }
    if(l==4&&(trand==1&&k==1||trand==0&&k==5||trand==2&&k==6)){
        temptheme=6;
    }
    int y1 = w + 2;
    int x1 = ll + 2;
    int y2 = y1 + 4 + (rand() % 12);
    int x2 = x1 + 4 + (rand() % 42);

    int centerX = (x1 + x2) / 2;
    int centerY = (y1 + y2) / 2;
    centers[index][0] = centerX;
    centers[index][1] = centerY;
    srand(time(0));
    int brandd = rand() % 3;
    int crandd = rand() % 6;
    for (int y = y1; y <= y2; y++)
    {
        for (int x = x1; x <= x2; x++)
        {
            if (rand() % 100 == 0 && (y == y1 || y == y2))
            {
                map[l][y][x] = '=';
                themed[l][y][x] = temptheme;
            }
            else if (y == y1 || y == y2)
            {
                map[l][y][x] = '_';
                themed[l][y][x] = temptheme;
                if (rand() % 100 == 0 && (x == x1 || x == x2) && y == y2)
                {
                    map[l][y][x] = '=';
                    themed[l][y][x] = temptheme;
                }
                else if ((x == x1 || x == x2) && y == y2)
                {
                    map[l][y][x] = '|';
                    themed[l][y][x] = temptheme;
                }
            }
            else
            {
                if (rand() % 100 == 0 && (x == x1 || x == x2))
                {
                    map[l][y][x] = '=';
                    themed[l][y][x] = temptheme;
                }
                else if (x == x1 || x == x2)
                {
                    map[l][y][x] = '|';
                    themed[l][y][x] = temptheme;
                }
                else if ((brandd == 2 && k == 2 || brandd == 1 && k == 3 || brandd == 0 && k == 4) && x == centerX && y == centerY - 1)
                {
                    mvprintw(y, x, "@");
                    map[l][y][x] = '<';
                    themed[l][y][x] = temptheme;
                    forbidden = k;
                    cx = x;
                    cy = y;
                } else if(temptheme == 6&&(rand() % 7 == 0 && abs(x - x1) > 1 && abs(x - x2) > 1 && abs(y - y1) > 1 && abs(y - y2) > 1))
                {
                    int p = rand() % 21;
                    if (p ==0 || p==1)
                    {
                        map[l][y][x] = 'O';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p > 7 && p < 10)
                    {
                            map[l][y][x] = 'U';enemy_health[l][y][x]=30;
                            themed[l][y][x] = temptheme;
                    }
                    else if (p == 12||p==10)
                    {
                            map[l][y][x] = 'S';enemy_health[l][y][x]=20;movable[l][y][x]=-2;
                            themed[l][y][x] = temptheme;
                    }
                    else if (p==8)
                    {
                            map[l][y][x] = 'F';enemy_health[l][y][x]=10;
                            themed[l][y][x] = temptheme;
                    }
                    else if (p==11)
                    {
                        if(rand()%2==0){
                            map[l][y][x] = 'D';enemy_health[l][y][x]=5;
                            themed[l][y][x] = temptheme;}
                        else{
                           map[l][y][x] = 'G';enemy_health[l][y][x]=15;
                            themed[l][y][x] = temptheme;
                        }
                    }
                    else if (p < 9 && p > 0 )
                    {
                        if (rand() % 2 == 0)
                        {
                            map[l][y][x] = 'C';
                            themed[l][y][x] = temptheme;
                        }
                        else
                        {
                            map[l][y][x] = 'c';
                            themed[l][y][x] = temptheme;
                         } 
                    }else{map[l][y][x] = '.';
                            themed[l][y][x] = temptheme; }

                } else if (temptheme != 3 && temptheme != 4 && temptheme != 5 && (rand() % 14 == 0 && abs(x - x1) > 1 && abs(x - x2) > 1 && abs(y - y1) > 1 && abs(y - y2) > 1))
                {
                    int p = rand() % 26;
                    if (p > 0 && p < 6)
                    {
                        map[l][y][x] = 'O';
                        themed[l][y][x] = temptheme;
                    }
                    else if(p>=21){
                        int pp=rand()&20;
                    if ((pp > 0 && pp < 10)&&l>2)
                    {
                            map[l][y][x] = 'U';enemy_health[l][y][x]=30;
                            themed[l][y][x] = temptheme;
                    }
                    else if ((pp > 0 && pp < 15)&&l>1)
                    {
                            map[l][y][x] = 'S';enemy_health[l][y][x]=20;movable[l][y][x]=-2;
                            themed[l][y][x] = temptheme;
                    }
                    else if ((pp>14&&pp<20)||pp==6)
                    {
                            map[l][y][x] = 'F';enemy_health[l][y][x]=10;
                            themed[l][y][x] = temptheme;
                    }
                    else if ((pp > 2 && pp < 6)||pp==8||l==0)
                    {
                            map[l][y][x] = 'D';enemy_health[l][y][x]=5;
                            themed[l][y][x] = temptheme;
                    }
                    else
                    {
                           map[l][y][x] = 'G';enemy_health[l][y][x]=15;
                            themed[l][y][x] = temptheme;
                    }
                    }
                    else if (p > 5 && p < 10)
                    {
                        if (rand() % 20 == 0 && kplaced == 0)
                        {
                            kplaced = 1;
                            map[l][y][x] = 'k';
                            themed[l][y][x] = temptheme;
                        }
                        else
                        {
                            map[l][y][x] = 't';
                            themed[l][y][x] = temptheme;
                        }
                    }
                    else if (p == 12 || p == 0)
                    {
                        if (rand() % 20 == 0)
                        {
                            map[l][y][x] = 'C';
                            themed[l][y][x] = temptheme;
                        }
                        else
                        {
                            map[l][y][x] = 'c';
                            themed[l][y][x] = temptheme;
                        }
                    }
                    else if (p == 21)
                    {
                        map[l][y][x] = '1';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 15)
                    {
                        map[l][y][x] = '2';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 16)
                    {
                        map[l][y][x] = '3';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 17)
                    {
                        map[l][y][x] = '4';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 18)
                    {
                        map[l][y][x] = '5';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 19)
                    {
                        map[l][y][x] = '6';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 20)
                    {
                        map[l][y][x] = '7';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 14)
                    {
                        map[l][y][x] = '8';
                        themed[l][y][x] = temptheme;
                    }
                    else
                    {
                        int foodrand=rand()%10;
                        if(foodrand==0){
                        map[l][y][x] = 'g';
                        themed[l][y][x] = temptheme;
                        }
                        else if(foodrand>4)  {                      
                        map[l][y][x] = 'f';
                        themed[l][y][x] = temptheme;
                        }
                        else if(foodrand==1||foodrand==2)  {                      
                        map[l][y][x] = 'h';
                        themed[l][y][x] = temptheme;
                        }
                        else if(foodrand==3||foodrand==4)  {                      
                        map[l][y][x] = 'j';
                        themed[l][y][x] = temptheme;
                        }

                    }
                }
                else if (temptheme == 3 && (rand() % 14 == 0 && abs(x - x1) > 1 && abs(x - x2) > 1 && abs(y - y1) > 1 && abs(y - y2) > 1))
                {
                    int p = rand() % 23;
                    if (p > 0 && p < 6)
                    {
                        map[l][y][x] = 'O';
                        themed[l][y][x] = temptheme;
                    }
                    else if(p>=21){
                        int pp=rand()&10;
                    if ((pp > 0 && pp < 5)&&l>2)
                    {
                            map[l][y][x] = 'U';enemy_health[l][y][x]=30;
                            themed[l][y][x] = temptheme;
                    }
                    else if ((pp > 0 && pp < 9)&&l>1)
                    {
                            map[l][y][x] = 'S';enemy_health[l][y][x]=20;movable[l][y][x]=-2;
                            themed[l][y][x] = temptheme;
                    }
                    else if ((pp>0&&pp<3)||pp==9)
                    {
                            map[l][y][x] = 'F';enemy_health[l][y][x]=10;
                            themed[l][y][x] = temptheme;
                    }
                    else if ((pp > 2 && pp < 6)||pp==8||l==0)
                    {
                            map[l][y][x] = 'D';enemy_health[l][y][x]=5;
                            themed[l][y][x] = temptheme;
                    }
                    else
                    {
                           map[l][y][x] = 'G';enemy_health[l][y][x]=15;
                            themed[l][y][x] = temptheme;
                    }
                    }
                    else if (p > 5 && p < 11)
                    {
                        map[l][y][x] = '.';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 12 || p == 0)
                    {
                        if (rand() % 20 == 0)
                        {
                            map[l][y][x] = 'C';
                            themed[l][y][x] = temptheme;
                        }
                        else
                        {
                            map[l][y][x] = 'c';
                            themed[l][y][x] = temptheme;
                        }
                    }
                    else if (p == 21)
                    {
                        map[l][y][x] = '1';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 15)
                    {
                        map[l][y][x] = '2';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 16)
                    {
                        map[l][y][x] = '3';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 17)
                    {
                        map[l][y][x] = '4';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 18)
                    {
                        map[l][y][x] = '5';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 19)
                    {
                        map[l][y][x] = '6';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 20)
                    {
                        map[l][y][x] = '7';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 14)
                    {
                        map[l][y][x] = '8';
                        themed[l][y][x] = temptheme;
                    }
                    else
                    {
                        int foodrand=rand()%10;
                         if(foodrand>4)  {                      
                        map[l][y][x] = 'f';
                        themed[l][y][x] = temptheme;
                        }
                        else if(foodrand==1||foodrand==2||foodrand==0)  {                      
                        map[l][y][x] = 'h';
                        themed[l][y][x] = temptheme;
                        }
                        else if(foodrand==3||foodrand==4)  {                      
                        map[l][y][x] = 'j';
                        themed[l][y][x] = temptheme;
                        }
                    }
                }
                else if (temptheme == 4 && (rand() % 14 == 0 && abs(x - x1) > 1 && abs(x - x2) > 1 && abs(y - y1) > 1 && abs(y - y2) > 1))
                {
                    int p = rand() % 23;
                    if (p > 0 && p < 4)
                    {
                        map[l][y][x] = 'O';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p > 5 && p < 7)
                    {
                        if (rand() % 20 == 0 && kplaced == 0)
                        {
                            kplaced = 1;
                            map[l][y][x] = 'k';
                            themed[l][y][x] = temptheme;
                        }
                        else
                        {
                            map[l][y][x] = 't';
                            themed[l][y][x] = temptheme;
                        }
                    }
                    else if (p > 6 && p < 12||p==14)
                    {
                        map[l][y][x] = 'P';
                        themed[l][y][x] = temptheme;
                    }
                    else if(p>=21){
                        int pp=rand()&10;
                    if ((pp > 0 && pp < 5)&&l>2)
                    {
                            map[l][y][x] = 'U';enemy_health[l][y][x]=30;
                            themed[l][y][x] = temptheme;
                    }
                    else if ((pp > 2 && pp < 9)&&l>1)
                    {
                            map[l][y][x] = 'S';enemy_health[l][y][x]=20;movable[l][y][x]=-2;

                            themed[l][y][x] = temptheme;
                    }
                    else if ((pp>0&&pp<3)||pp==9)
                    {
                            map[l][y][x] = 'F';enemy_health[l][y][x]=10;
                            themed[l][y][x] = temptheme;
                    }
                    else if ((pp > 2 && pp < 6)||pp==8||l==0)
                    {
                            map[l][y][x] = 'D';enemy_health[l][y][x]=5;
                            themed[l][y][x] = temptheme;
                    }
                    else 
                    {
                           map[l][y][x] = 'G';enemy_health[l][y][x]=15;
                            themed[l][y][x] = temptheme;
                    }
                    }
                    else if (p == 12 || p == 0)
                    {
                        if (rand() % 20 == 0)
                        {
                            map[l][y][x] = 'C';
                            themed[l][y][x] = temptheme;
                        }
                        else
                        {
                            map[l][y][x] = 'c';
                            themed[l][y][x] = temptheme;
                        }
                    }
                    else if (p == 21)
                    {
                        map[l][y][x] = '1';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 15)
                    {
                        map[l][y][x] = '2';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 16)
                    {
                        map[l][y][x] = '3';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 17)
                    {
                        map[l][y][x] = '4';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 18)
                    {
                        map[l][y][x] = '5';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 19)
                    {
                        map[l][y][x] = '6';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 20)
                    {
                        map[l][y][x] = '7';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 14)
                    {
                        map[l][y][x] = '8';
                        themed[l][y][x] = temptheme;
                    }
                    else
                    {
                        int foodrand=rand()%10;
                        if(foodrand==0){
                        map[l][y][x] = 'h';
                        themed[l][y][x] = temptheme;
                        }
                        else if(foodrand>4)  {                      
                        map[l][y][x] = 'g';
                        themed[l][y][x] = temptheme;
                        }
                        else if(foodrand==1||foodrand==2)  {                      
                        map[l][y][x] = 'f';
                        themed[l][y][x] = temptheme;
                        }
                        else if(foodrand==3||foodrand==4)  {                      
                        map[l][y][x] = 'j';
                        themed[l][y][x] = temptheme;
                        }
                    }
                }
                else if (temptheme == 5 && (rand() % 14 == 0 && abs(x - x1) > 1 && abs(x - x2) > 1 && abs(y - y1) > 1 && abs(y - y2) > 1))
                {
                    int p = rand() % 23;
                    if (p > 0 && p < 6)
                    {
                        map[l][y][x] = 'O';
                        themed[l][y][x] = temptheme;
                    }
                    else if(p>=21){
                        int pp=rand()&10;
                    if ((pp > 0 && pp < 5)&&l>2)
                    {
                            map[l][y][x] = 'U';enemy_health[l][y][x]=30;
                            themed[l][y][x] = temptheme;
                    }
                    else if ((pp > 2 && pp < 9)&&l>1)
                    {
                            map[l][y][x] = 'S';enemy_health[l][y][x]=20;movable[l][y][x]=-2;
                            themed[l][y][x] = temptheme;
                    }
                    else if ((pp>0&&pp<3)||p==9)
                    {
                            map[l][y][x] = 'F';enemy_health[l][y][x]=10;
                            themed[l][y][x] = temptheme;
                    }
                    else if ((pp > 2 && pp < 6)||pp==8||l==0)
                    {
                            map[l][y][x] = 'D';enemy_health[l][y][x]=5;
                            themed[l][y][x] = temptheme;
                    }
                    else
                    {
                           map[l][y][x] = 'G';enemy_health[l][y][x]=15;
                            themed[l][y][x] = temptheme;
                    }
                    }
                    else if (p > 5 && p < 11)
                    {
                        if (rand() % 20 == 0 && kplaced == 0)
                        {
                            kplaced = 1;
                            map[l][y][x] = 'k';
                            themed[l][y][x] = temptheme;
                        }
                        else
                        {
                            map[l][y][x] = 't';
                            themed[l][y][x] = temptheme;
                        }
                    }
                    else if (p == 12 || p == 0)
                    {
                        if (rand() % 20 == 0)
                        {
                            map[l][y][x] = 'C';
                            themed[l][y][x] = temptheme;
                        }
                        else
                        {
                            map[l][y][x] = 'c';
                            themed[l][y][x] = temptheme;
                        }
                    }
                    else if (p == 21)
                    {
                        map[l][y][x] = '1';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 15)
                    {
                        map[l][y][x] = '2';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 16)
                    {
                        map[l][y][x] = '3';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 17)
                    {
                        map[l][y][x] = '4';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 18)
                    {
                        map[l][y][x] = '5';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 19)
                    {
                        map[l][y][x] = '6';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 20)
                    {
                        map[l][y][x] = '7';
                        themed[l][y][x] = temptheme;
                    }
                    else if (p == 14)
                    {
                        map[l][y][x] = '8';
                        themed[l][y][x] = temptheme;
                    }
                    else
                    {
                        int foodrand=rand()%10;
                        if(foodrand==0){
                        map[l][y][x] = 'g';
                        themed[l][y][x] = temptheme;
                        }
                        else if(foodrand>4)  {                      
                        map[l][y][x] = 'f';
                        themed[l][y][x] = temptheme;
                        }
                        else if(foodrand==1||foodrand==2)  {                      
                        map[l][y][x] = 'h';
                        themed[l][y][x] = temptheme;
                        }
                        else if(foodrand==3||foodrand==4)  {                      
                        map[l][y][x] = 'j';
                        themed[l][y][x] = temptheme;
                        }
                    }
                }
                else
                {
                    map[l][y][x] = '.';
                    themed[l][y][x] = temptheme;
                }
            }
        }
    }
    if (crandd == forbidden)
    {
        crandd++;
    }
    if (l < 4 && ((placed != 1 && crandd == k) || (k == 6 && placed != 1)))
    {
        int ey = (rand() % (y2 - y1 - 2)) + y1 + 1;
        int ex = (rand() % (x2 - x1 - 2)) + x1 + 1;
        while (1)
        {
            if (map[l][ey][ex - 1] == '.' || map[l][ey][ex - 1] == '|' || map[l][ey][ex - 1] == '^')
            {
                map[l][ey][ex] = '>';
                break;
            }
            ex++;
            if (map[l][ey][ex + 1] == '|')
            {
                ey++;
                ex = x1 + 1;
            }
        }
        placed = 1;
    }
}
void create_path(int x1, int y1, int x2, int y2)
{
    int x = x1;
    int y = y1;
    int a;
    while (x != x2 || y != y2)
    {
        a = rand() % 2;
        if (map[l][y][x] == '=' || map[l][y][x] == '_')
        {
            if (locked == 1)
            {
                map[l][y][x] = '*';
                int i = x;
                while (map[l][y][i - 1] != '0')
                {
                    i--;
                    if (map[l][y][i] == '+')
                    {
                        map[l][y][i] = '*';
                    }
                }
                i = x;
                while (map[l][y][i + 1] != '0')
                {
                    i++;
                    if (map[l][y][i] == '+')
                    {
                        map[l][y][i] = '*';
                    }
                }
                i = y;
                while (map[l][i + 1][x] != '0')
                {
                    i++;
                    if (map[l][i][x] == '+')
                    {
                        map[l][i][x] = '*';
                    }
                }
                i = y;
                while (map[l][i - 1][x] != '0')
                {
                    i--;
                    if (map[l][i][x] == '+')
                    {
                        map[l][i][x] = '*';
                    }
                }
            }

            else if (secret == 1)
            {
                map[l][y][x] = '-';
            }
            else
            {
                map[l][y][x] = '+';
            }
            a = 1;
        }
        else if (map[l][y][x] == '=' || map[l][y][x] == '|')
        {
            if (secret == 1)
            {
                map[l][y][x] = '~';
            }
            else
            {
                map[l][y][x] = '+';
            }
            a = 0;
        }
        else if (map[l][y][x] == '0')
        {
            map[l][y][x] = '#';
        }
        else if (bplaced < 2 && map[l][y][x] != '0' && locked == 1)
        {
            int i = x, j = y;
            if (bplaced == 0)
            {
                if (map[l][y][x - 1] == '.' || map[l][y][x - 1] == '>')
                {
                    i = x - 1;
                }
                else if (map[l][y][x + 1] == '.' || map[l][y][x + 1] == '>')
                {
                    i = x + 1;
                }
                else if (map[l][y - 1][x] == '.' || map[l][y - 1][x] == '>')
                {
                    j = y - 1;
                }
                else if (map[l][y + 1][x] == '.' || map[l][y + 1][x] == '>')
                {
                    j = x + 1;
                }
                while (map[l][y][i] != '|' && map[l][y][i] != '~' && map[l][y][i] != '=' && map[l][y][i] != '+' && map[l][y][i] != '*')
                {
                    i++;
                }
                while (map[l][j][x] != '-' && map[l][j][x] != '_' && map[l][j][x] != '=' && map[l][j][x] != '+' && map[l][j][x] != '*')
                {
                    j++;
                }
                map[l][j - 1][i - 1] = '&';
                bplaced = 1;
                i = x, j = y;
            }
            else if (bplaced == 1)
            {
                if (map[l][y][x - 1] == '.' || map[l][y][x - 1] == '>')
                {
                    i = x - 1;
                }
                else if (map[l][y][x + 1] == '.' || map[l][y][x + 1] == '>')
                {
                    i = x + 1;
                }
                else if (map[l][y - 1][x] == '.' || map[l][y - 1][x] == '>')
                {
                    j = y - 1;
                }
                else if (map[l][y + 1][x] == '.' || map[l][y + 1][x] == '>')
                {
                    j = x + 1;
                }
                int i = x, j = y;
                while (map[l][y][i] != '|' && map[l][y][i] != '~' && map[l][y][i] != '=' && map[l][y][i] != '+' && map[l][y][i] != '*')
                {
                    i--;
                }
                while (map[l][j][x] != '-' && map[l][j][x] != '_' && map[l][j][x] != '=' && map[l][j][x] != '+' && map[l][j][x] != '*')
                {
                    j--;
                }
                map[l][j + 1][i + 1] = '&';
                bplaced = 2;
                i = x, j = y;
            }
        }

        if (x != x2 && (a == 0 || y == y2))
        {
            if (x < x2)
            {
                x++;
            }
            else
            {
                x--;
            }
        }
        else
        {
            if (y < y2)
            {
                y++;
            }
            else
            {
                y--;
            }
        }
    }
}
void create_junction(int x1, int y1, int x2, int y2, int x3, int y3)
{
    create_path(x1, y1, x2, y2);
    create_path(x2, y2, x3, y3);
}
void draw_secret_Rectangle(int my, int mx, int centersx, int centersy)
{
    int randtemp = rand() % 80;
    int permtemp;
    if (randtemp == 0)
    {
        permtemp = 0;
    }
    else if (randtemp > 30)
    {
        permtemp = 1;
    }
    else
    {
        permtemp = 2;
    }
    int width = (rand() % 3) + 6;
    int height = (rand() % 3) + 6;
    int startX = mx + rand() % (8 - width + 1);
    int startY = my + rand() % (8 - height + 1);
    mvprintw(0, 0, "secret in (%d,%d) ", startX, startY);
    for (int y = startY; y < startY + height; y++)
    {
        for (int x = startX; x < startX + width; x++)
        {
            if (y == startY || y == startY + height - 1)
            {
                map[l][y][x] = '_';
                themed[l][y][x] = permtemp;
            }
            else if (x == startX || x == startX + width - 1)
            {
                map[l][y][x] = '|';
                themed[l][y][x] = permtemp;
            }
            else
            {
                if (permtemp == 2)
                {
                    int khrand = rand() % 4;
                    if (khrand < 2 && x < startX + width - 2 && map[l][y][x - 1] != 'c')
                    {
                        if (rand() % 3 == 1)
                        {
                            map[l][y][x] = 'C';
                            themed[l][y][x] = permtemp;
                        }
                        else
                        {
                            map[l][y][x] = 'c';
                            themed[l][y][x] = permtemp;
                        }
                    }
                    else
                    {
                        map[l][y][x] = '.';
                        themed[l][y][x] = permtemp;
                    }
                }
                else if (permtemp == 1)
                {
                    int khrand = rand() % 4;
                    if (khrand < 2 && x < startX + width - 2 && map[l][y][x - 1] != 'c')
                    {
                        if (rand() % 3 == 1)
                        {
                            map[l][y][x] = '6';
                            themed[l][y][x] = permtemp;
                        }
                        else if(rand()%3 !=2)
                        {
                            map[l][y][x] = '7';
                            themed[l][y][x] = permtemp;
                        }
                        else
                        {
                            map[l][y][x] = '8';
                            themed[l][y][x] = permtemp;
                        }
                    }
                    else
                    {
                        map[l][y][x] = '.';
                        themed[l][y][x] = permtemp;
                    }
                }
                else
                {
                    map[l][y][x] = '.';
                    themed[l][y][x] = permtemp;
                }
            }
            if ((y == startY + height - 1 && x == startX) || (y == startY + height - 1 && x == startX + width - 1))
            {
                map[l][y][x] = '|';
                themed[l][y][x] = permtemp;
            }
        }
    }
    secret = 1;
    create_path(mx + 4, my + 4, centersx, centersy);
    secret = 0;
}

void secret_room(int v)
{
    if (v == 0)
    {
        for (int y = 30; y < 40; y++)
        {
            for (int x = 30; x < 40; x++)
            {
                if (map[l][y][x] != '0')
                {
                    v++;
                    secret_room(v);
                    return;
                }
            }
        }
        draw_secret_Rectangle(30, 30, centers[1][0], centers[1][1]);
        secret_room(++v);
    }
    else if (v % 2 == 1)
    {
        for (int y = 0; y < 10; y++)
        {
            for (int x = 30; x < 40; x++)
            {
                if (map[l][y][x] != '0')
                {
                    return;
                }
            }
        }
        if (v > 1)
        {
            draw_secret_Rectangle(0, 30, centers[2][0], centers[2][1]);
        }
        else
        {
            draw_secret_Rectangle(0, 30, centers[1][0], centers[1][1]);
        }
    }
    else
    {
        for (int y = 15; y < 25; y++)
        {
            for (int x = 130; x < 140; x++)
            {
                if (map[l][y][x] != '0')
                {
                    return;
                }
            }
        }
        if (v > 1)
        {
            draw_secret_Rectangle(15, 130, centers[4][0], centers[4][1]);
        }
        else
        {
            draw_secret_Rectangle(15, 130, centers[5][0], centers[5][1]);
        }
    }
}
void window_reveal(int direction, int cy, int cx)
{
    switch (direction)
    {
    case 1:
        for (int s = 0; s < 200; s += 2)
        {
            int r = 0;
            for (int i = -s / 2; i <= s / 2; ++i)
            {
                if (cy + s < 50 && cx + i < 150 && cy + s >= 0 && cx + i >= 0)
                {
                    reveal_map(map, cy + s, cx + i);
                }
            }
        }
        break;

    case 2:
        for (int s = 0; s < 200; s += 2)
        {
            int r = 0;
            for (int i = -s / 2; i <= s / 2; ++i)
            {
                if (cy - s < 50 && cx + i < 150 && cy - s >= 0 && cx + i >= 0)
                {
                    reveal_map(map, cy - s, cx + i);
                }
            }
        }
        break;

    case 3:
        for (int s = 0; s < 200; s += 2)
        {
            int r = 0;
            for (int i = -s / 2; i <= s / 2; ++i)
            {
                if (cy + i < 50 && cx + s < 150 && cy + i >= 0 && cx + s >= 0)
                {
                    reveal_map(map, cy + i, cx + s);
                }
            }
        }
        break;

    case 4:
        for (int s = 0; s < 200; s += 2)
        {
            int r = 0;
            for (int i = -s / 2; i <= s / 2; ++i)
            {
                if (cy + i <50 && cx - s < 150 && cy + i >= 0 && cx - s >= 0)
                {
                    reveal_map(map, cy + i, cx - s);
                }
            }
        }
        break;
    }
    
}
int check_dead(int j,int i){

     if(enemy_health[l][j][i]<=0&&map[l][j][i]=='U'){
    map[l][j][i]='.';
    mvprintw(0,0,"YOU KILLED UNDEAD...AGAIN                                            ");
    reveal_map(map,cx,cy);
    return 0;
    }
    else if(enemy_health[l][j][i]<=0&&map[l][j][i]=='S'){
    map[l][j][i]='.';
    mvprintw(0,0,"YOU KILLED SNAKE                                                  ");
    reveal_map(map,cx,cy);
    return 0;
    }
    else if(enemy_health[l][j][i]<=0&&map[l][j][i]=='G'){
    map[l][j][i]='.';
    mvprintw(0,0,"YOU KILLED GIANT                                                  ");
    reveal_map(map,cx,cy);
    return 0;}
    else if(enemy_health[l][j][i]<=0&&map[l][j][i]=='D'){
    map[l][j][i]='.';
    mvprintw(0,0,"YOU KILLED DEMON                                       ");
    reveal_map(map,cx,cy);
    return 0;
    }
    else if(enemy_health[l][j][i]<=0&&map[l][j][i]=='F'){
    map[l][j][i]='.';
    mvprintw(0,0,"YOU KILLED FIRE BREATHING MONSTER                          ");
    reveal_map(map,cx,cy);
    return 0;
    }

    }

void display_health_bar()
{
    xp+=100;
    start_color();
    init_pair(100, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(100));
    if (l != 4)
    {
        mvprintw(0, 80, "stage %d", l + 1);
    }
    else
    {
        mvprintw(0, 80, "final stage");
    }
    attroff(COLOR_PAIR(100));
    init_pair(25, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(10, COLOR_BLACK, COLOR_RED);
    init_pair(50, 48, 48);
    for (int h = 0; h < 10; h++)
    {
        if (health_bar[0] == 0)
        {
            ends=1;
        }
        if (health_bar[h] == 1)
        {
            if (poison_m > h)
            {
                attron(COLOR_PAIR(25));
                mvprintw(40, h * 3, "   ");
                attroff(COLOR_PAIR(25));
            }
            else if (health_m / 3 > h||heal_boost)
            {
                attron(COLOR_PAIR(50));
                mvprintw(40, h * 3, "   ");
                attroff(COLOR_PAIR(50));
            }
            else
            {
                if (trap_m != 0)
                {
                    attron(COLOR_PAIR(25));
                }
                else
                {
                    attron(COLOR_PAIR(10));
                }
                mvprintw(40, h * 3, "   ");
                attron(COLOR_PAIR(25));
                attroff(COLOR_PAIR(10));
            }
        }
        else
        {
            mvprintw(40, h * 3, "   ");
        }
    }

    refresh();
}
void display_score()
{
    allcoin+=coin;
    if(diff==3){
    score += coin * 10;
    coin = 0;}
    else if(diff==4){
    score += coin * 12;
    coin = 0;}
    else if(diff==2){
    score += coin * 8;
    coin = 0;}
    else if(diff==1){
    score += coin * 6;
    coin = 0;}
    mvprintw(40, 40, "SCORE:");
    mvprintw(40, 46, "%d", score);
}
void display_food_stack()
{
    mvprintw(42, 0, "FOOD:");
    foods = 0;
    for (int f = 0; f < 5; f++)
    {
        if (food_stack[f] == 1||food_stack[f] == 2)
        {
            foods++;
            mvprintw(42, f * 3 + 6, "🍒");
        }
        else if (food_stack[f] == 3)
        {
            foods++;
            mvprintw(42, f * 3 + 6, "🍎");
        }
        else if (food_stack[f] == 4)
        {
            foods++;
            mvprintw(42, f * 3 + 6, "🍓");
        }
        else
        {
            mvprintw(42, f * 3 + 6, " ");
        }
    }
}
void damage(){
    for (int h = 9; h > -1; h--)
        {
            if (health_bar[h] == 1)
            {
                health_bar[h] = 0;
                break;
            }
        }
}
int fight(int cx,int cy){
    int eok=0;
    for(int i=cx-1;i<=cx+1;i++){
        for(int j=cy-1;j<=cy+1;j++){
            if(map[l][j][i]=='D'||map[l][j][i]=='S'||map[l][j][i]=='U'||map[l][j][i]=='F'||map[l][j][i]=='G'){
                if(movable[l][j][i]==-1){movable[l][j][i]=-1;}
                else if(movable[l][j][i]<-1){movable[l][j][i]=-2;}
                else{movable[l][j][i]=5;}
                eok=1;
            }
        }
    }
    if(eok){

    if(!myturn){
        myturn=1;
     mvprintw(43,0,"%c",map[l][cy][cx+1]);
     switch (map[l][cy][cx+1])
     {
        case 'D':
            damage();mvprintw(0,0,"DEMON DAMAGES YOU!                     ");
            break;
        case 'F':
            damage();mvprintw(0,0,"FIRE BREATHING MONSTER DAMAGES YOU!      "); 
            break;           
        case 'S':
            damage();mvprintw(0,0,"SNAKE DAMAGES YOU!                           ");
            damage();
            break;
        case 'G':
            damage();mvprintw(0,0,"GIANT DAMAGES YOU!                           ");
            damage();
            break;
        case 'U':
            damage();mvprintw(0,0,"UNDEAD DAMAGES YOU!                           ");
            damage();
            damage();
            break;
        case 'B':
         
            damage();mvprintw(0,0,"THE BOSS CRASHED YOU!                           ");
            damage();
            damage();
            damage();
            damage();
            break;
     }
     switch (map[l][cy-1][cx-1])
     {
        case 'D':
            damage();mvprintw(0,0,"DEMON DAMAGES YOU!                         ");
            break;
        case 'F':
            damage();mvprintw(0,0,"FIRE BREATHING MONSTER DAMAGES YOU!      "); 
            break;           
        case 'S':
            damage();mvprintw(0,0,"SNAKE DAMAGES YOU!                           ");
            damage();
            break;
        case 'G':
            damage();mvprintw(0,0,"GIANT DAMAGES YOU!                           ");
            damage();
            break;
        case 'U':
            damage();mvprintw(0,0,"UNDEAD DAMAGES YOU!                           ");
            damage();
            damage();
            break;
        case 'B':
         
            damage();mvprintw(0,0,"THE BOSS CRASHED YOU!                           ");
            damage();
            damage();
            damage();
            damage();
            break;
     }
     switch (map[l][cy+1][cx-1])
     {
        case 'D':
            damage();mvprintw(0,0,"DEMON DAMAGES YOU!                         ");
            break;
        case 'F':
            damage();mvprintw(0,0,"FIRE BREATHING MONSTER DAMAGES YOU!      "); 
            break;           
        case 'S':
            damage();mvprintw(0,0,"SNAKE DAMAGES YOU!                           ");
            damage();
            break;
        case 'G':
            damage();mvprintw(0,0,"GIANT DAMAGES YOU!                           ");
            damage();
            break;
        case 'U':
            damage();mvprintw(0,0,"UNDEAD DAMAGES YOU!                           ");
            damage();
            damage();
            break;
        case 'B':
         
            damage();mvprintw(0,0,"THE BOSS CRASHED YOU!                           ");
            damage();
            damage();
            damage();
            damage();
            break;
     }
     switch (map[l][cy-1][cx+1])
     {
        case 'D':
            damage();mvprintw(0,0,"DEMON DAMAGES YOU!                           ");
            break;
        case 'F':
            damage();mvprintw(0,0,"FIRE BREATHING MONSTER DAMAGES YOU!      "); 
            break;           
        case 'S':
            damage();mvprintw(0,0,"SNAKE DAMAGES YOU!                           ");
            damage();
            break;
        case 'G':
            damage();mvprintw(0,0,"GIANT DAMAGES YOU!                           ");
            damage();
            break;
        case 'U':
            damage();mvprintw(0,0,"UNDEAD DAMAGES YOU!                           ");
            damage();
            damage();
            break;
        case 'B':
         
            damage();mvprintw(0,0,"THE BOSS CRASHED YOU!                           ");
            damage();
            damage();
            damage();
            damage();
            break;
     }
     switch (map[l][cy+1][cx+1])
     {
        case 'D':
            damage();mvprintw(0,0,"DEMON DAMAGES YOU!                           ");
            break;
        case 'F':
            damage();mvprintw(0,0,"FIRE BREATHING MONSTER DAMAGES YOU!      "); 
            break;           
        case 'S':
            damage();mvprintw(0,0,"SNAKE DAMAGES YOU!                           ");
            damage();
            break;
        case 'G':
            damage();mvprintw(0,0,"GIANT DAMAGES YOU!                           ");
            damage();
            break;
        case 'U':
            damage();mvprintw(0,0,"UNDEAD DAMAGES YOU!                           ");
            damage();
            damage();
            break;
        case 'B':
         
            damage();mvprintw(0,0,"THE BOSS CRASHED YOU!                           ");
            damage();
            damage();
            damage();
            damage();
            break;
     }
     switch (map[l][cy-1][cx])
     {
        case 'D':
            damage();mvprintw(0,0,"DEMON DAMAGES YOU!                           ");
            break;
        case 'F':
            damage();mvprintw(0,0,"FIRE BREATHING MONSTER DAMAGES YOU!      "); 
            break;           
        case 'S':
            damage();mvprintw(0,0,"SNAKE DAMAGES YOU!                           ");
            damage();
            break;
        case 'G':
            damage();mvprintw(0,0,"GIANT DAMAGES YOU!                           ");
            damage();
            break;
        case 'U':
            damage();mvprintw(0,0,"UNDEAD DAMAGES YOU!                           ");
            damage();
            damage();
            break;
        case 'B':
         
            damage();mvprintw(0,0,"THE BOSS CRASHED YOU!                           ");
            damage();
            damage();
            damage();
            damage();
            break;
     }
     switch (map[l][cy+1][cx])
     {
        case 'D':
            damage();mvprintw(0,0,"DEMON DAMAGES YOU!                           ");
            break;
        case 'F':
            damage();mvprintw(0,0,"FIRE BREATHING MONSTER DAMAGES YOU!      "); 
            break;           
        case 'S':
            damage();mvprintw(0,0,"SNAKE DAMAGES YOU!                           ");
            damage();
            break;
        case 'G':
            damage();mvprintw(0,0,"GIANT DAMAGES YOU!                           ");
            damage();
            break;
        case 'U':
            damage();mvprintw(0,0,"UNDEAD DAMAGES YOU!                           ");
            damage();
            damage();
            break;
        case 'B':
         
            damage();mvprintw(0,0,"THE BOSS CRASHED YOU!                           ");
            damage();
            damage();
            damage();
            damage();
            break;
     }
     switch (map[l][cy][cx-1])
     {
        case 'D':
            damage();mvprintw(0,0,"DEMON DAMAGES YOU!                           ");
            break;
        case 'F':
            damage();mvprintw(0,0,"FIRE BREATHING MONSTER DAMAGES YOU!      "); 
            break;           
        case 'S':
            damage();mvprintw(0,0,"SNAKE DAMAGES YOU!                           ");
            damage();
            break;
        case 'G':
            damage();mvprintw(0,0,"GIANT DAMAGES YOU!                           ");
            damage();
            break;
        case 'U':
            damage();mvprintw(0,0,"UNDEAD DAMAGES YOU!                           ");
            damage();
            damage();
            break;
        case 'B':
         
            damage();mvprintw(0,0,"THE BOSS CRASHED YOU!                           ");
            damage();
            damage();
            damage();
            damage();
            break;
        
     }

    }
    display_health_bar();
    if(myturn){
        myturn=0;int s=getch();
        switch(s)
        {
            case ' ':
            if(picked_gun==1){
                for(int i=cx-1;i<=cx+1;i++){
                    for(int j=cy-1;j<=cy+1;j++){
                        if(map[l][j][i]=='D'){
                            mvprintw(0,0,"YOU HIT DEMON BY MACE -> 5 DAMAGE                              ");
                            if(damage_boost){mvprintw(0,35,"+ 5"); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=5;}
                            check_dead(j,i);
                        }
                        else if(map[l][j][i]=='F'){
                            mvprintw(0,0,"YOU HIT FIRE BREATHING MONSTER BY MACE -> 5 DAMAGE              ");
                            if(damage_boost){mvprintw(0,52,"+ 5"); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=5;}
                            check_dead(j,i);
                        }
                        else if(map[l][j][i]=='G'){
                            mvprintw(0,0,"YOU HIT GIANT BY MACE -> 5 DAMAGE                               ");
                            if(damage_boost){ mvprintw(0,35,"+ 5");repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=5;}
                            check_dead(j,i);
                        }
                        else if(map[l][j][i]=='S'){
                            mvprintw(0,0,"YOU HIT SNAKE BY MACE -> 5 DAMAGE                               ");
                            if(damage_boost){ mvprintw(0,35,"+ 5");repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=5;}
                            check_dead(j,i);
                        }
                        else if(map[l][j][i]=='U'){
                            mvprintw(0,0,"YOU HIT UNDEAD BY MACE -> 5 DAMAGE                               ");
                           if(damage_boost){mvprintw(0,36,"+ 5"); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=5;}
                            check_dead(j,i);
                        }
                        else if(map[l][j][i]=='$'){
                            mvprintw(0,0,"YOU HIT THE BOSS BY MACE -> 5 DAMAGE                               ");
                           if(damage_boost){mvprintw(0,36,"+ 5"); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=5;damage_to_boss+=5;}
                            check_dead(j,i);
                        }
                        else if(map[l][j][i]=='B'){
                            mvprintw(0,0,"YOU HIT THE BOSS BY MACE -> 0 DAMAGE                               ");
                           if(damage_boost){mvprintw(0,36,"+ 0"); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=5;}
                            check_dead(j,i);
                        }
                    }
                }
             }
            if(picked_gun==5){
                for(int i=cx-1;i<=cx+1;i++){
                    for(int j=cy-1;j<=cy+1;j++){
                        if(map[l][j][i]=='D'){
                            mvprintw(0,0,"YOU HIT DEMON BY SWORD -> 10 DAMAGE                               ");
                             if(damage_boost){mvprintw(0,37,"+ 10"); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=10;}
                            check_dead(j,i);
                        }
                        else if(map[l][j][i]=='F'){
                            mvprintw(0,0,"YOU HIT FIRE BREATHING MONSTER BY SWORD -> 10 DAMAGE                ");
                            if(damage_boost){mvprintw(0,54,"+ 10"); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=10;}
                            check_dead(j,i);
                        }
                        else if(map[l][j][i]=='G'){
                            mvprintw(0,0,"YOU HIT GIANT BY SWORD -> 10 DAMAGE                               ");
                            if(damage_boost){mvprintw(0,37,"+ 10"); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=10;}
                            check_dead(j,i);
                        }
                        else if(map[l][j][i]=='S'){
                            mvprintw(0,0,"YOU HIT SNAKE BY SWORD -> 10 DAMAGE                               ");
                            if(damage_boost){mvprintw(0,37,"+ 10"); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=10;}
                            check_dead(j,i);
                        }
                        else if(map[l][j][i]=='U'){
                            mvprintw(0,0,"YOU HIT UNDEAD BY SWORD -> 10 DAMAGE                               ");
                            if(damage_boost){mvprintw(0,38,"+ 10"); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=10;}
                            check_dead(j,i);
                        }
                        else if(map[l][j][i]=='$'){
                            mvprintw(0,0,"YOU HIT THE BOSS BY SWORD -> 10 DAMAGE                                ");
                           if(damage_boost){mvprintw(0,36,"+ 10"); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=10;damage_to_boss+=10;}
                            check_dead(j,i);
                        }
                        else if(map[l][j][i]=='B'){
                            mvprintw(0,0,"YOU HIT THE BOSS BY SWORD -> 0 DAMAGE                                ");
                           if(damage_boost){mvprintw(0,36,"+ 0"); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][j][i]-=10;}
                            check_dead(j,i);
                        }
                    }
                }
             }
            break;
        }
    
    }
}
}

int cha;
void show_map()
{
    init_pair(236, 236, COLOR_BLACK);
    init_pair(244, 236, COLOR_BLACK);
    init_pair(88, 88, COLOR_BLACK);
    attron(COLOR_PAIR(236));
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 150; j++)
        {
            if (revealed[l][i][j] == 1 && themed[l][i][j] == 5)
            {
                attron(COLOR_PAIR(88));
                if ((map[l][i][j] == 't' || map[l][i][j] == '.' || map[l][i][j] == 'c' || map[l][i][j] == 'C' || map[l][i][j] == 'k' || map[l][i][j] == 'j' ||map[l][i][j] == 'h' ||map[l][i][j] == 'g' ||map[l][i][j] == 'f' || map[l][i][j] == 'P' || map[l][i][j] == 'O'||map[l][i][j] == 'F'||map[l][i][j] == 'U'||map[l][i][j] == 'D'||map[l][i][j] == 'S'||map[l][i][j] == 'G'||map[l][i][j] == '2'||map[l][i][j] == '3'||map[l][i][j] == '4'||map[l][i][j] == '5'||map[l][i][j] == '6'||map[l][i][j] == '7'||map[l][i][j] == '8'))
                {
                    mvprintw(i, j, ".");
                }
                else if ((map[l][i][j] == '-' || map[l][i][j] == '_'))
                {
                    mvprintw(i, j, "_");
                }
                else if ((map[l][i][j] == '~' || map[l][i][j] == '|'))
                {
                    mvprintw(i, j, "|");
                }
                else if (map[l][i][j] != '0' && map[l][i][j] != '#')
                {
                    mvprintw(i, j, "%c", map[l][i][j]);
                }
                attroff(COLOR_PAIR(88));
            }
            else
            {
                attron(COLOR_PAIR(236));
                if (revealed[l][i][j] == 1)
                {
                    continue;
                }
                else if (revealed[l][i][j] != 1 && (map[l][i][j] == 't' || map[l][i][j] == '.' || map[l][i][j] == 'c' || map[l][i][j] == 'C' || map[l][i][j] == 'k' || map[l][i][j] == 'f' || map[l][i][j] == 'g' ||map[l][i][j] == 'h' ||map[l][i][j] == 'j' || map[l][i][j] == 'P' || map[l][i][j] == 'O'||map[l][i][j] == 'F'||map[l][i][j] == 'U'||map[l][i][j] == 'D'||map[l][i][j] == 'S'||map[l][i][j] == 'G'||map[l][i][j] == '2'||map[l][i][j] == '3'||map[l][i][j] == '4'||map[l][i][j] == '5'||map[l][i][j] == '6'||map[l][i][j] == '7'||map[l][i][j] == '8'))
                {
                    mvprintw(i, j, ".");
                }
                else if (revealed[l][i][j] != 1 && (map[l][i][j] == '-' || map[l][i][j] == '_'))
                {
                    mvprintw(i, j, "_");
                }
                else if (revealed[l][i][j] != 1 && (map[l][i][j] == '~' || map[l][i][j] == '|'))
                {
                    mvprintw(i, j, "|");
                }
                else if (revealed[l][i][j] != 1 && map[l][i][j] != '0' && map[l][i][j] != '#')
                {
                    mvprintw(i, j, "%c", map[l][i][j]);
                }
            }
        }
    }
    attroff(COLOR_PAIR(236));
}
void equipt(int n){
    if(n<6){
    for(int i=0;i<5;i++){
        if(n==5){sword=1;}
        if(gun_stack[i]%10==n){if(i==2){gun_stack[i]+=80;break;}else if(i==3){gun_stack[i]+=200;break;}gun_stack[i]+=100;break;}
        if(gun_stack[i]==0){gun_stack[i]=n+100;guns++;break;}}
        
    }else{
        
        for(int i=0;i<3;i++){
        if(potion_stack[i]%10==n-5){potion_stack[i]+=10;break;}
        }
    }
}
void move_enemy(int y2, int x2, int y1, int x1) {
    if ((rand() % 2 == 1 && y2 != y1) || x2 == x1) {
        if (y1 > y2) {
            if(map[l][y2 + 1][x2-1]=='f'||map[l][y2 + 1][x2-1]=='g'||map[l][y2 + 1][x2-1]=='h'||map[l][y2 + 1][x2-1]=='j'||map[l][y2 + 1][x2-1]=='c'||map[l][y2 + 1][x2-1]=='C'||map[l][y2 + 1][x2-1]=='k'||map[l][y2 + 1][x2-1]=='2'||map[l][y2 + 1][x2-1]=='3'||map[l][y2 + 1][x2-1]=='4'||map[l][y2 + 1][x2-1]=='5'||map[l][y2 + 1][x2-1]=='6'||map[l][y2 + 1][x2-1]=='7'||map[l][y2 + 1][x2-1]=='8')
            {int temp1=map[l][y2 + 1][x2-1];
            map[l][y2+1 ][x2-1]='.';
            map[l][y2 + 1][x2] = map[l][y2][x2];
            map[l][y2][x2]=temp1;
            int mtemp1=movable[l][y2 + 1][x2-1];
            movable[l][y2+1 ][x2-1]=0;
            movable[l][y2 + 1][x2] = movable[l][y2][x2]-1;
            movable[l][y2][x2]=mtemp1;
            int htemp1=enemy_health[l][y2 + 1][x2-1];
            enemy_health[l][y2+1 ][x2-1]=0;
            enemy_health[l][y2 + 1][x2] = enemy_health[l][y2][x2];
            enemy_health[l][y2][x2]=htemp1;
            }
            else{int temp1=map[l][y2 + 1][x2];
            map[l][y2 + 1][x2] = map[l][y2][x2];
            map[l][y2][x2]=temp1;
            int mtemp1=movable[l][y2 + 1][x2];
            movable[l][y2 + 1][x2] = movable[l][y2][x2]-1;
            movable[l][y2][x2]=mtemp1;
            int htemp1=enemy_health[l][y2 + 1][x2];
            enemy_health[l][y2 + 1][x2] = enemy_health[l][y2][x2];
            enemy_health[l][y2][x2]=htemp1;}
            if( map[l][y2+1][x2]!='_'&&map[l][y2+1][x2]!='-'&&map[l][y2+1][x2]!='+'&&map[l][y2+1][x2]!='*'&&map[l][y2+1][x2]!='|'&&map[l][y2+1][x2]!='~'&&map[l][y2+1][x2]!='#'){
            y2++;}
        } else {
            if(map[l][y2 - 1][x2-1]=='f'||map[l][y2 - 1][x2-1]=='g'||map[l][y2 - 1][x2-1]=='h'||map[l][y2 - 1][x2-1]=='j'||map[l][y2 - 1][x2-1]=='c'||map[l][y2 - 1][x2-1]=='C'||map[l][y2 - 1][x2-1]=='k'||map[l][y2 - 1][x2-1]=='2'||map[l][y2 - 1][x2-1]=='3'||map[l][y2 - 1][x2-1]=='4'||map[l][y2 - 1][x2-1]=='5'||map[l][y2 - 1][x2-1]=='6'||map[l][y2 - 1][x2-1]=='7'||map[l][y2 - 1][x2-1]=='8')
            {int temp2=map[l][y2 - 1][x2-1];
            map[l][y2-1 ][x2-1]='.';
            map[l][y2 - 1][x2] = map[l][y2][x2];
            map[l][y2][x2]=temp2;
            int mtemp2=movable[l][y2 - 1][x2-1];
            movable[l][y2-1 ][x2-1]=0;
            movable[l][y2 - 1][x2] = movable[l][y2][x2]-1;
            movable[l][y2][x2]=mtemp2;
            int htemp2=enemy_health[l][y2 - 1][x2-1];
            enemy_health[l][y2-1 ][x2-1]=0;
            enemy_health[l][y2 - 1][x2] = enemy_health[l][y2][x2];
            enemy_health[l][y2][x2]=htemp2;
            }
            else{int temp2=map[l][y2 - 1][x2];
            map[l][y2 - 1][x2] = map[l][y2][x2];
            map[l][y2][x2]=temp2;
            int mtemp2=movable[l][y2 - 1][x2];
            movable[l][y2 - 1][x2] = movable[l][y2][x2]-1;
            movable[l][y2][x2]=mtemp2;
            int htemp2=enemy_health[l][y2 - 1][x2];
            enemy_health[l][y2 - 1][x2] = enemy_health[l][y2][x2];
            enemy_health[l][y2][x2]=htemp2;}
            if( map[l][y2-1][x2]!='_'&&map[l][y2-1][x2]!='-'&&map[l][y2-1][x2]!='+'&&map[l][y2-1][x2]!='*'&&map[l][y2-1][x2]!='|'&&map[l][y2-1][x2]!='~'&&map[l][y2-1][x2]!='#'){
            y2--;}
        }
    } else {
        if (x2 > x1) {
            if(map[l][y2][x2-2]=='f'||map[l][y2][x2-2]=='g'||map[l][y2][x2-2]=='j'||map[l][y2][x2-2]=='h'||map[l][y2][x2-2]=='c'||map[l][y2][x2-2]=='C'||map[l][y2][x2-2]=='k'||map[l][y2][x2-2]=='2'||map[l][y2][x2-2]=='3'||map[l][y2][x2-2]=='4'||map[l][y2][x2-2]=='5'||map[l][y2][x2-2]=='6'||map[l][y2][x2-2]=='7'||map[l][y2][x2-2]=='8')
            {int temp3=map[l][y2 ][x2-2];
            map[l][y2 ][x2-2]='.';
            map[l][y2 ][x2-1] = map[l][y2][x2];
            map[l][y2][x2]=temp3;
            int mtemp3=movable[l][y2 ][x2-2];
            movable[l][y2 ][x2-2]=0;
            movable[l][y2 ][x2-1] = movable[l][y2][x2]-1;
            movable[l][y2][x2]=mtemp3;
            int htemp3=enemy_health[l][y2 ][x2-2];
            enemy_health[l][y2 ][x2-2]=0;
            enemy_health[l][y2 ][x2-1] = enemy_health[l][y2][x2];
            enemy_health[l][y2][x2]=htemp3;
            
            }
            else{int temp3=map[l][y2][x2-1];
            map[l][y2][x2 - 1] = map[l][y2][x2];
            map[l][y2][x2]=temp3;
            int mtemp3=movable[l][y2][x2-1];
            movable[l][y2][x2 - 1] = movable[l][y2][x2]-1;
            movable[l][y2][x2]=mtemp3;
            int htemp3=enemy_health[l][y2][x2-1];
            enemy_health[l][y2][x2 - 1] = enemy_health[l][y2][x2];
            enemy_health[l][y2][x2]=htemp3;}
            if( map[l][y2][x2-1]!='_'&&map[l][y2][x2-1]!='-'&&map[l][y2][x2-1]!='+'&&map[l][y2][x2-1]!='*'&&map[l][y2][x2-1]!='|'&&map[l][y2][x2-1]!='~'&&map[l][y2][x2-1]!='#'){
            x2--;}
        } else {
            if(map[l][y2][x2+1]=='f'||map[l][y2][x2+1]=='g'||map[l][y2][x2+1]=='h'||map[l][y2][x2+1]=='j'||map[l][y2][x2+1]=='c'||map[l][y2][x2+1]=='C'||map[l][y2][x2+1]=='k'||map[l][y2][x2+1]=='2'||map[l][y2][x2+1]=='3'||map[l][y2][x2+1]=='4'||map[l][y2][x2+1]=='5'||map[l][y2][x2+1]=='6'||map[l][y2][x2+1]=='7'||map[l][y2][x2+1]=='8')
            {int temp4=map[l][y2][x2+1];
             int htemp4=enemy_health[l][y2][x2+1];
             int mtemp4=movable[l][y2][x2+1];
            enemy_health[l][y2][x2+1]=enemy_health[l][y2][x2];
            map[l][y2][x2+1] = map[l][y2][x2];
            movable[l][y2][x2+1] = movable[l][y2][x2]-1;
            enemy_health[l][y2][x2-1]=htemp4;
            map[l][y2][x2-1]=temp4;
            movable[l][y2][x2-1]=mtemp4;
            }
            else{int temp4=map[l][y2][x2 + 1];
            int htemp4=enemy_health[l][y2][x2+1];
            int mtemp4=movable[l][y2][x2 + 1];
            movable[l][y2][x2 + 1] = movable[l][y2][x2]-1;
            movable[l][y2 ][x2]=mtemp4;
            map[l][y2][x2 + 1] = map[l][y2][x2];
            enemy_health[l][y2][x2 + 1] = enemy_health[l][y2][x2];
            map[l][y2 ][x2]=temp4;
            enemy_health[l][y2 ][x2]=htemp4;}
            if( map[l][y2][x2-1]!='_'&&map[l][y2][x2+1]!='-'&&map[l][y2][x2+1]!='+'&&map[l][y2][x2+1]!='*'&&map[l][y2][x2+1]!='|'&&map[l][y2][x2+1]!='~'&&map[l][y2][x2+1]!='#'){
            x2++;}
        }
    }
}

void check_enemy(int cy, int cx) {
    int i = cx;
    int j = cy;
    win=1;
    while (i > 0 && map[l][j][i - 1] != '|' && map[l][j][i - 1] != '~' && map[l][j][i - 1] != '=' && map[l][j][i - 1] != '+' && map[l][j][i - 1] != '*') {
        while (map[l][j + 1][i] != '0'&& map[l][j + 1][i] != '-' && map[l][j + 1][i] != '_' && map[l][j + 1][i] != '=' && map[l][j + 1][i] != '+' && map[l][j + 1][i] != '*' &&map[l][j + 1][i] != '|') {
            j++;
            if ((map[l][j][i] == 'U' )&&movable[l][j][i]!=0&&movable[l][j][i]!=-1
            || (map[l][j][i] == 'G')&&movable[l][j][i]!=0&&movable[l][j][i]!=-1
            || (map[l][j][i] == 'S' &&movable[l][j][i]!=0&&movable[l][j][i]!=-1)
            || map[l][j][i] == 'B' ) {
                move_enemy(j, i, cy, cx);
            }
            if(map[l][j][i] == 'U' ||map[l][j][i] == 'D' ||map[l][j][i] == 'S' ||map[l][j][i] == 'G' ||map[l][j][i] == 'F'){
                win=0;
            }
        }
        j = cy;
        while (map[l][j - 1][i] != '0'&& map[l][j - 1][i] != '-' && map[l][j - 1][i] != '_' && map[l][j - 1][i] != '=' && map[l][j - 1][i] != '+' && map[l][j - 1][i] != '*'&& map[l][j - 1][i] != '|') {
            j--;
            if ((map[l][j][i] == 'U' )&&movable[l][j][i]!=0&&movable[l][j][i]!=-1
            || (map[l][j][i] == 'G') &&movable[l][j][i]!=0&&movable[l][j][i]!=-1
            || (map[l][j][i] == 'S' &&movable[l][j][i]!=0&&movable[l][j][i]!=-1)
            || map[l][j][i] == 'B') {
                move_enemy(j, i, cy, cx);
            }
            if(map[l][j][i] == 'U' ||map[l][j][i] == 'D' ||map[l][j][i] == 'S' ||map[l][j][i] == 'G' ||map[l][j][i] == 'F'){
                win=0;
            }
        }
        i--;
        
    }

    i = cx;
    j = cy;

    while (map[l][j ][i+1] != '0' && map[l][j][i + 1] != '|' && map[l][j][i + 1] != '~' && map[l][j][i + 1] != '=' && map[l][j][i + 1] != '+' && map[l][j][i + 1] != '*') {
        i++;
        while (map[l][j + 1][i] != '0'&&map[l][j + 1][i] != '-' && map[l][j + 1][i] != '_' && map[l][j + 1][i] != '=' && map[l][j + 1][i] != '+' && map[l][j + 1][i] != '*'&& map[l][j + 1][i] != '|') {
            j++;
            if ((map[l][j][i] == 'U' )&&movable[l][j][i]!=0&&movable[l][j][i]!=-1
            || (map[l][j][i] == 'G') &&movable[l][j][i]!=0&&movable[l][j][i]!=-1
            || (map[l][j][i] == 'S' &&movable[l][j][i]!=0&&movable[l][j][i]!=-1)
            || map[l][j][i] == 'B') {
                move_enemy(j, i, cy, cx);
            }
            if(map[l][j][i] == 'U' ||map[l][j][i] == 'D' ||map[l][j][i] == 'S' ||map[l][j][i] == 'G' ||map[l][j][i] == 'F'){
                win=0;
            }
        }
        j = cy;
        while (j > 0 && map[l][j - 1][i] != '-' && map[l][j - 1][i] != '_' && map[l][j - 1][i] != '=' && map[l][j - 1][i] != '+' && map[l][j - 1][i] != '*'&& map[l][j - 1][i] != '|') {
            j--;
            if ((map[l][j][i] == 'U' )&&movable[l][j][i]!=0&&movable[l][j][i]!=-1
            || (map[l][j][i] == 'G') &&movable[l][j][i]!=0&&movable[l][j][i]!=-1
            || (map[l][j][i] == 'S' &&movable[l][j][i]!=0&&movable[l][j][i]!=-1)
             || map[l][j][i] == 'B') {
                move_enemy(j, i, cy, cx);
            }
            if(map[l][j][i] == 'U' ||map[l][j][i] == 'D' ||map[l][j][i] == 'S' ||map[l][j][i] == 'G' ||map[l][j][i] == 'F'){
                win=0;
            }
        }
    }
}
void reset_game(){
     k = 0, cx, cy, secret = 0, m = 0, foods = 0, eat = 0, coin = 0, score, forbidden = 0, placed = 0, crand, poison_m = 0, sickness = 0, health_m = 0, akey = 0, bkey = 0,
    healness = 0, trap_m, firsttime = 0, locked = 0, firstlock = 1, bplaced = 0, unlocked = 0, password = 9999, password2 = 9999, gofornext = 0, buttony, buttonx,
    error = 0, done = 0, picked_gun = 1, guns = 5, diff = 3, kplaced = 0,potions=3,picked_potion=1,t_room=0,trand,endisnear=0,ends=0,allcoin=0,
    xp=0,finished=0,myturn=0,direction=0,arrowy,dagger_limit=0,arrow_limit=0,arrowx,wound_limit=0,sword=0,heal=0,heal_boost=0,speed_boost=0,damage_boost=0,repeat,eaten=0,win=0,forbid_continue=1;
     l = 0;
     for(int i=0;i<60;i++){
        hunger_bar[i]=1;
        if(i<10){health_bar[i]=1;}
        if(i<5){food_stack[i]=0;gun_stack[i]=i+1;levels[i]=0;}
        if(i<3){potion_stack[i]=i+1;}

    }

    }


void move_hero(int cy, int cx)
{
    pthread_t timer_thread;
    display_score();
    display_food_stack();
    display_health_bar();
    reveal_map(map, cy, cx);
    mvprintw(cy, cx, "@");
    move(cy, cx);

int end() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    int height, width;
    getmaxyx(stdscr, height, width);
    WINDOW *end_win = newwin(height, width, 0, 0);
    box(end_win, 0, 0);
    refresh();
    if(endisnear==2){
        score+=2000;
        submit();
    wrefresh(end_win);
    
    mvwprintw(end_win,1, 63, "                           ,--.");
    mvwprintw(end_win,2, 63, "                          {    }");
    mvwprintw(end_win,3, 63, "                          K,   }");
    mvwprintw(end_win,4, 63, "                         /  `Y`");
    mvwprintw(end_win,5, 63, "                    _   /   /");
    mvwprintw(end_win,6, 63, "                   {_'-K.__/");
    mvwprintw(end_win,7, 63, "                     `/-.__L._");
    mvwprintw(end_win,8, 63, "                     /  ' /`\\_}");
    mvwprintw(end_win,9, 63, "                    /  ' /    ");
    mvwprintw(end_win,10, 63, "            ____   /  ' /");
    mvwprintw(end_win,11, 63, "     ,-'~~~~    ~~/  ' /_");
    mvwprintw(end_win,12,63, "   ,'             ``~~~  ',");
    mvwprintw(end_win,13,63, "  (                         Y");
    mvwprintw(end_win,14,63, " {                         I");
    mvwprintw(end_win,15,63, "{      -                     `.");
    mvwprintw(end_win,16,63, "|       ',                    )");
    mvwprintw(end_win,17, 63, "|        |   ,..__      __. Y");
    mvwprintw(end_win,18, 63, "|    .,_./  Y ' / ^Y   J   )|");
    mvwprintw(end_win,19, 63, "\\           |' /   |   |   ||");
    mvwprintw(end_win,20, 63, " \\          L_/    . _ (_,.'(");
    mvwprintw(end_win,21, 63, "  \\,   ,      ^^\"\"' / |      )");
    mvwprintw(end_win,22, 63, "    \\_  \\          /,L]     /");
    mvwprintw(end_win,23, 63, "      '-_`-,       ` `   ./`");
    mvwprintw(end_win,24, 63, "         `-(_            )");
    mvwprintw(end_win,25, 63, "             ^^\\..___,.--`");

    mvwprintw(end_win, height / 2+8, (width - 10) / 2+1, "CONGRATS");
    mvwprintw(end_win, height / 2+10, (width - 10) / 2-22, "Score: %d + 2000 SCORE YOU FOUND IN TREASURE ROOM!", score-2000);endisnear=0;wrefresh(end_win);getch();submit();;forbid_continue=1;}
    else{
            
    init_pair(16,COLOR_MAGENTA,COLOR_BLACK);
    mvwprintw(end_win,11, 63, "     ,-'~~~~```~~-``' -_");
    mvwprintw(end_win,12,63, "   ,'                    ',");
    mvwprintw(end_win,13,63, "  (                         Y");
    mvwprintw(end_win,14,63, " {                         I");
    mvwprintw(end_win,15,63, "{      -                     `.");
    mvwprintw(end_win,16,63, "|       ',                    )");
    mvwprintw(end_win,17, 63, "|        |   ,..__      __.   Y");
    mvwprintw(end_win,18, 63, "|    .,_./  Y     ^Y   J   )  |");
    mvwprintw(end_win,19, 63, "\\           |      |   |   | |");
    wattron(end_win,COLOR_PAIR(16));
     mvwprintw(end_win,19, 78, "O");
     mvwprintw(end_win,19, 87, "O");
    wattroff(end_win,COLOR_PAIR(16));
    mvwprintw(end_win,20, 63, " \\          L_     . _ (_,.'(");
    mvwprintw(end_win,21, 63, "  \\,   ,      ^^\"\"' / |      )");
    mvwprintw(end_win,22, 63, "    \\_  \\          /,L]     /");
    mvwprintw(end_win,23, 63, "      '-_`-,       ` `   ./`");
    mvwprintw(end_win,24, 63, "         `-(_            )");
    mvwprintw(end_win,25, 63, "             ^^\\..___,.--`");


        mvwprintw(end_win, height / 2+8, (width - 10) / 2, "OH-UH:(...");endisnear=0;getch();forbid_continue=1;}
    // for(int i=0;i<60;i++){
    //     if(i<10){health_bar[i]=1;}
    //     if(i<5){food_stack[i]=0;gun_stack[i]=i+1;}
    //     if(i<3){potion_stack[i]=i+1;}
    //     // l=0;allcoin=0;score=0;coin=0;xp=0;

    // }
    reset_game();
    wrefresh(end_win);
    sleep(3);
    delwin(end_win);
    endwin();
    display_main_menu();

}
    while (1)
    { 
        // if(themed[5][cy][cx]==6){
        //     int bossdone=0;
        // for (int i = 0; i < 50; i++)
        // {
        //     for (int j = 0; j < 150; j++)
        //     {
        //         if(map[5][i][j]=='$')
        //         {
        //             map[5][i][j]='.';
        //         }
        //         if(map[5][i][j]=='B')
        //         {
        //             bossdone=1;
        //             map[5][i+1][j-1]='$';map[5][i-1][j+1]='$';map[5][i-1][j-1]='$';map[5][i+1][j+1]='$';map[5][i+1][j]='$';map[5][i-1][j]='$';map[5][i][j+1]='$';map[5][i][j-1]='$';
        //             break;
        //         }     
        //     }
        //     if(bossdone==1){
        //         bossdone=0;
        //         break;
        //     }
        // }
        // refresh();
        // }
        if(map[l][cy][cx]=='#'){
            musicplay=1;
            Mix_CloseAudio();
        }
        else if(themed[l][cy][cx]==1&&musicplay){
            musicplay=0;
            play_music("./soundtracks/1.mp3");
        }
        else if(themed[l][cy][cx]==2&&musicplay){
            musicplay=0;
            play_music("./soundtracks/2.mp3");
        }
        else if(themed[l][cy][cx]==3&&musicplay){
            musicplay=0;
            play_music("./soundtracks/3.mp3");
        }
        else if(themed[l][cy][cx]==5&&musicplay){
            musicplay=0;
            play_music("./soundtracks/5.mp3");
        }
        else if(themed[l][cy][cx]==6&&musicplay){
            musicplay=0;
            play_music("./soundtracks/6.mp3");
        }
        else if(map[l][cy][cx]=='?'&&musicplay){
            musicplay=0;
            play_music("./soundtracks/8.mp3");
        }
        else if(themed[l][cy][cx]==4&&musicplay){
            musicplay=0;
            play_music("./soundtracks/4.mp3");
        }
        else if(clashed&&musicplay){
            musicplay=0;
            play_music("./soundtracks/7.mp3");
        }
        if(hunger_bar[41]==1&&heal>=8){
            heal=0;
            for (int h = 0; h < 10; h++)
            {
                if (health_bar[h] == 0)
                {
                    health_bar[h] = 1;if(heal_boost&&h<9){health_bar[h+1] = 1;}
                    break;
                }
            }  
        }
        else if(hunger_bar[41]==1){
            heal++;
        }
        if(picked_gun==3){

         mvprintw(41,60,  "                                    ");
         mvprintw(42,60,  "  ==================================");
         mvprintw(43,60,  "  ==================================");
         mvprintw(44,60,  "                                    ");
         init_pair(164, COLOR_MAGENTA, COLOR_BLACK);
         attron(COLOR_PAIR(164));
         mvprintw(41,96,  "⣴⣷⣷⣿⣷⣄");
         mvprintw(42,96,  "⣿⣿⣿⣿⣿⡯⣄");
         mvprintw(43,96,  "⣿⣿⣿⣿⣿⣷⠟");
         mvprintw(44,96,  "⠙⣿⠟⢷⠟");
         attroff(COLOR_PAIR(164));
        }
        else if(picked_gun==4){ 
         mvprintw(42,60,  "  \\\\\\\\\\\\\\\\_____________________\\`-._");
         mvprintw(43,60,  "  ////////                     /.-' ");

        }
        else if(picked_gun==5){ 
         mvprintw(41,60,  "            /\\                                     ");
         mvprintw(42,60,  "/vvvvvvvvvvvv \\--------------------------------------,");
         mvprintw(43,60,  "`^^^^^^^^^^^^ /=====================================\"");
         mvprintw(44,60,  "            \\/                                      ");}
         else if(picked_gun==2){
         mvprintw(42,60,  "          ./~");
         mvprintw(43,60,  "(=OOOOOOO=[}=================--");
         mvprintw(44,60,"          `\\~");
         }
         else if(picked_gun==1){
         mvprintw(41,60,  "                                    .^--^--^-.");
         mvprintw(42,60,  "  ==================================| <   >  |>");
         mvprintw(43,60,  "  ==================================|   <   >|>");
         mvprintw(44,60,  "                                    `V----V--`");               
         }
         else if(picked_gun==0){
         mvprintw(41,60,  "                                                                     ");
         mvprintw(42,60,  "                                                                     ");
         mvprintw(43,60,  "                                                                     ");
         mvprintw(44,60,  "                                                                     ");               
         }
       
        for(int i=0;i<5;i++){
            if (food_stack[i]>0){
            rott_limit[i]++;
            if(rott_limit[i]>=100){
                rott_limit[i]=0;
                if(food_stack[i]==1){food_stack[i]=2;}
                else if(food_stack[i]>2){food_stack[i]=1;}
            }
            }
            else{rott_limit[i]=0;}
        }
        if(heal_boost>0)
        {heal_boost--;
        attron(COLOR_PAIR(48));
        mvprintw(40,120, "HEAL BOOST                   ");
        attroff(COLOR_PAIR(48));}
        else{mvprintw(40,120,"                      ");}
        if(speed_boost>0)
        {speed_boost--;
        attron(COLOR_PAIR(220));
        mvprintw(42,120, "SPEED BOOST             ");
        attroff(COLOR_PAIR(220));}
        else{mvprintw(42,120,"                      ");}
        if(damage_boost>0)
        {damage_boost--;
        attron(COLOR_PAIR(88));
        mvprintw(44,120, "DAMAGE BOOST             ");
        attroff(COLOR_PAIR(88));}
        else{mvprintw(44,120,"                      ");}
        curs_set(0);
        cha=fight(cx,cy);
        if(ends){end();}
        if(endisnear==2){end();}
        if(endisnear==1&&themed[l][cy][cx]==6){
        mvprintw(40,63,"KILL ALL MONSTERS TO WIN!");
        for(int i=0;i<50;i++){
            for(int j=0;j<150;j++){
                if(map[l][cy][cx]=='='){map[l][cy][cx]='+';}
            }
        }
        check_enemy(cy,cx);
        if(win){endisnear=2;}
        }
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 150; j++)
            {
                if (themed[l][i][j] != 5 && revealed[l][i][j] == 1 && map[l][i][j] == '~')
                {
                    if (themed[l][i][j] == 4)
                    {
                        init_pair(108,8,COLOR_BLACK);
                        attron(COLOR_PAIR(108));
                        mvprintw(i, j, "|");
                        attroff(COLOR_PAIR(108));
                    }
                    else if (themed[l][i][j] == 3)
                    {
                        init_pair(48, 48, COLOR_BLACK);
                        attron(COLOR_PAIR(48));
                        mvprintw(i, j, "|");
                        attroff(COLOR_PAIR(48));
                    }
                    else if (themed[l][i][j] == 0)
                    {
                        mvprintw(i, j, "|");
                    }
                }
            }
        }
        if (map[l][cy][cx] == '+' && (themed[l][cy + 1][cx] == 5 && revealed[l][cy + 1][cx] == 1 || themed[l][cy - 1][cx] == 5 && revealed[l][cy - 1][cx] == 1))
        {
            for (int i = 0; i < 50; i++)
            {
                for (int j = 0; j < 150; j++)
                {
                    if (themed[l][i][j] == 5)
                    {
                        mvprintw(i, j, " ");
                    }
                    else if (revealed[l][i][j] == 1 && map[l][i][j] == '~')
                    {
                        mvprintw(i, j, "|");
                    }
                }
            }
            mvprintw(cy, cx, "@");
        }
        eat = 0;
        keypad(stdscr, TRUE);
        cbreak();
        int button;
        if (firsttime == 2)
        {
            firsttime = 1;
            button = 'm';
        }
        else
        {
            button = getch();
        }
        check_enemy(cy,cx);
        mvprintw(0, 120, "Button pressed: %d\n", button);
        refresh();
        mvprintw(40, 140, "%d", poison_m);
        if (themed[l][cy][cx] == 1 && mapp_theme == 1)
        {
            display_health_bar();
            sickness = 1;
            init_pair(16, COLOR_MAGENTA, COLOR_BLACK);
            attron(COLOR_PAIR(16));
            poison_m++;
        }
        else if (themed[l][cy][cx] == 2 && mapp_theme == 1)
        {
            init_pair(203, 202, COLOR_BLACK);
            attron(COLOR_PAIR(203));
        }
        else if (themed[l][cy][cx] == 3 && mapp_theme == 1)
        {
            init_pair(49, 48, COLOR_BLACK);
            attron(COLOR_PAIR(49));
            display_health_bar();
            healness = 1;
            health_m++;
            m = 0;
        }

        else if (themed[l][cy][cx] == 3)
        {
            init_pair(48, 48, COLOR_BLACK);
            attron(COLOR_PAIR(48));
            display_health_bar();
            healness = 1;
            health_m++;
            m = 0;
        }
        else if (themed[l][cy][cx] == 5 && mapp_theme == 1)
        {
            init_pair(89, 88, COLOR_BLACK);
            attron(COLOR_PAIR(89));
        }
        else if (themed[l][cy][cx] == 5)
        {
            init_pair(88, 88, COLOR_BLACK);
            attron(COLOR_PAIR(88));
        }
        else if (themed[l][cy][cx] == 6 && mapp_theme == 1)
        {
            init_pair(221, 220, COLOR_BLACK);
            attron(COLOR_PAIR(220));
        }
        else if (themed[l][cy][cx] == 6)
        {
            init_pair(220, 220, COLOR_BLACK);
            attron(COLOR_PAIR(220));
        }
        else if (themed[l][cy][cx] == 4 && mapp_theme == 1)
        {
            init_pair(247, 246, COLOR_BLACK);
            attron(COLOR_PAIR(247));
        }
        else if (themed[l][cy][cx] == 4)
        {
            init_pair(246, 246, COLOR_BLACK);
            attron(COLOR_PAIR(246));
        }
        else if (themed[l][cy][cx] == 2)
        {
            init_pair(202, 202, COLOR_BLACK);
            attron(COLOR_PAIR(202));
        }
        else if (themed[l][cy][cx] == 1)
        {
            display_health_bar();
            sickness = 1;
            init_pair(15, COLOR_MAGENTA, COLOR_BLACK);
            attron(COLOR_PAIR(15));
            poison_m++;
        }
        else
        {
            poison_m = 0;
            health_m = 0;
            healness = 0;
            sickness = 0;
        }
        if(map[l][cy][cx]=='a'){
            gun_stack[3]+=10;
            map[l][cy][cx]='.';
        }
        else if(map[l][cy][cx]=='w'){
            gun_stack[2]+=10;
            map[l][cy][cx]='.';
        }
        else if(map[l][cy][cx]=='d'){
            gun_stack[1]+=10;
            map[l][cy][cx]='.';
        }
        switch (button)
        {
        case 'p':
        case 'P':
           if(potion_stack[picked_potion-1]/10<1){mvprintw(0,0,"YOU RAN OUT OF THIS POTION                      ");break;}
           else{
            potion_stack[picked_potion-1]-=10;
            if(picked_potion==2){mvprintw(0,0,"SPEED POTION APPLIED                    ");speed_boost=30;}else if(picked_potion==1){mvprintw(0,0,"HEAL POTION APPLIED                    ");heal_boost=30;}else if(picked_potion==3){mvprintw(0,0,"DAMAGE POTION APPLIED                                ");damage_boost=30;}
           break;}
        case 'g':
        case 'G':
            while(1){
                int q=getch();
                if(q=='g'||q=='G'){break;}
                
                reveal_map(map,cy,cx);mvprintw(cy,cx,"@");
                switch (q)
                {
                    case KEY_HOME:
                     if (map[l][cy - 1][cx - 1] != '_' && map[l][cy - 1][cx - 1] != '|' && map[l][cy - 1][cx - 1] != '0' && map[l][cy - 1][cx - 1] != 'O'&&map[l][cy - 1][cx - 1] != 'U'&&map[l][cy - 1][cx - 1] != 'F'&&map[l][cy - 1][cx - 1] != 'S'&&map[l][cy - 1][cx - 1] != 'G'&&map[l][cy - 1][cx - 1] != 'D' && map[l][cy - 1][cx - 1] != '=')
                     {mvprintw(cy - 1, cx - 1, "@");
                     mvprintw(cy, cx, "%c", map[l][cy][cx]);
                     move(cy - 1, cx - 1);
                     cy -= 1;
                     cx -= 1;}break;
                    case KEY_PPAGE:
                if (map[l][cy - 1][cx + 1] != '_' && map[l][cy - 1][cx + 1] != '|' && map[l][cy - 1][cx + 1] != 'O'&&map[l][cy - 1][cx + 1] != 'U'&&map[l][cy - 1][cx + 1] != 'F'&&map[l][cy - 1][cx + 1] != 'S'&&map[l][cy - 1][cx + 1] != 'G'&&map[l][cy - 1][cx + 1] != 'D' && map[l][cy - 1][cx + 1] != 'O' && map[l][cy - 1][cx + 1] != '=') {
                    mvprintw(cy - 1, cx + 1, "@");
                    mvprintw(cy, cx, "%c", map[l][cy][cx]);
                    move(cy - 1, cx + 1);
                    cy -= 1;
                    cx += 1;}
                    break;
                

            case KEY_NPAGE:
                if (map[l][cy + 1][cx + 1] != '_' && map[l][cy + 1][cx + 1] != '|' && map[l][cy + 1][cx + 1] != '0' && map[l][cy + 1][cx + 1] != 'O'&&map[l][cy + 1][cx + 1] != 'U'&&map[l][cy + 1][cx + 1] != 'F'&&map[l][cy + 1][cx + 1] != 'S'&&map[l][cy + 1][cx + 1] != 'G'&&map[l][cy + 1][cx + 1] != 'D' && map[l][cy + 1][cx + 1] != '=') {
                    mvprintw(cy + 1, cx + 1, "@");
                    mvprintw(cy, cx, "%c", map[l][cy][cx]);
                    move(cy + 1, cx + 1);
                    cy += 1;
                    cx += 1;}
                    break;
                

            case KEY_END:
                if (map[l][cy + 1][cx - 1] != '_' && map[l][cy + 1][cx - 1] != '|' && map[l][cy + 1][cx - 1] != '0' && map[l][cy + 1][cx - 1] != 'O'&&map[l][cy + 1][cx - 1] != 'U'&&map[l][cy + 1][cx - 1] != 'F'&&map[l][cy + 1][cx - 1] != 'S'&&map[l][cy + 1][cx - 1] != 'G'&&map[l][cy + 1][cx - 1] != 'D' && map[l][cy + 1][cx - 1] != '=') {
                    mvprintw(cy + 1, cx - 1, "@");
                    mvprintw(cy, cx, "%c", map[l][cy][cx]);
                    move(cy + 1, cx - 1);
                    cy += 1;
                    cx -= 1;}
                    break;
            case KEY_UP:
                if (map[l][cy - 1][cx] != '_' && map[l][cy - 1][cx] != '|' && map[l][cy - 1][cx] != '0' && map[l][cy - 1][cx] != 'O'&&map[l][cy-1][cx] != 'U'&&map[l][cy -1][cx] != 'F'&&map[l][cy -1][cx] != 'S'&&map[l][cy - 1][cx] != 'G'&&map[l][cy - 1][cx] != 'D'
 && map[l][cy - 1][cx] != '=') {
                    mvprintw(cy - 1, cx, "@");
                    mvprintw(cy, cx, "%c", map[l][cy][cx]);
                    move(cy - 1, cx);
                    cy -= 1;}
                    break;
                

            case KEY_DOWN:
                if (map[l][cy + 1][cx] != '_' && map[l][cy + 1][cx] != '|' && map[l][cy + 1][cx] != '0' && map[l][cy + 1][cx] != 'O'&&map[l][cy+1][cx] != 'U'&&map[l][cy +1][cx] != 'F'&&map[l][cy +1][cx] != 'S'&&map[l][cy + 1][cx] != 'G'&&map[l][cy + 1][cx] != 'D' && map[l][cy + 1][cx] != '=') {
                    mvprintw(cy + 1, cx, "@");
                    mvprintw(cy, cx, "%c", map[l][cy][cx]);
                    move(cy + 1, cx);
                    cy += 1;}
                    break;
                

            case KEY_LEFT:
                if (map[l][cy][cx - 1] != '_' && map[l][cy][cx - 1] != '|' && map[l][cy][cx - 1] != '0' && map[l][cy][cx - 1] != 'O'&&map[l][cy][cx - 1] != 'U'&&map[l][cy][cx - 1] != 'F'&&map[l][cy][cx - 1] != 'S'&&map[l][cy][cx - 1] != 'G'&&map[l][cy][cx - 1] != 'D' && map[l][cy][cx - 1] != '=') {
                    mvprintw(cy, cx - 1, "@");
                    mvprintw(cy, cx, "%c", map[l][cy][cx]);
                    move(cy, cx - 1);
                    cx -= 1;}
                    break;
                

            case KEY_RIGHT:
                if (map[l][cy][cx + 1] != '_' && map[l][cy][cx + 1] != '|' && map[l][cy][cx + 1] != '0' && map[l][cy][cx + 1] != 'O'&&map[l][cy][cx + 1] != 'U'&&map[l][cy][cx + 1] != 'F'&&map[l][cy][cx + 1] != 'S'&&map[l][cy][cx + 1] != 'G'&&map[l][cy][cx + 1] != 'D'
 && map[l][cy][cx + 1] != '=') {
                    mvprintw(cy, cx + 1, "@");
                    mvprintw(cy, cx, "%c", map[l][cy][cx]);
                    move(cy, cx + 1);
                    cx += 1;}
                    break;
                

                            

                }

            }
            break;
        case 'F':
        case 'f':
            int q=getch();
            switch (q){
                case KEY_DOWN:
                mvprintw(cy,cx,"%c",map[l][cy][cx]);
                while (map[l][cy+1][cx] != '_' &&map[l][cy+1][cx] != '|' && map[l][cy+1][cx] != '='  && map[l][cy+1][cx] != '*'&&map[l][cy+1][cx] != '0'&&map[l][cy+1][cx] != 'O' ){
                cy++;}
                break;
            case KEY_UP:
                mvprintw(cy,cx,"%c",map[l][cy][cx]);
                while (map[l][cy-1][cx] != '_' &&map[l][cy-1][cx] != '|' && map[l][cy-1][cx] != '='  && map[l][cy-1][cx] != '*'&&map[l][cy-1][cx] != '0'&&map[l][cy-1][cx] != 'O' )
                {cy--;}break;
            case KEY_LEFT:
                mvprintw(cy,cx,"%c",map[l][cy][cx]);
                while (map[l][cy][cx-1] != '_' &&map[l][cy][cx-1] != '|' && map[l][cy][cx-1] != '='  && map[l][cy][cx-1] != '*'&&map[l][cy][cx-1] != '0'&&map[l][cy][cx-1] != 'O' )
                {cx--;}break;
            case KEY_RIGHT:
                mvprintw(cy,cx,"%c",map[l][cy][cx]);
                while (map[l][cy][cx+1] != '_' &&map[l][cy][cx+1] != '|' && map[l][cy][cx+1] != '='  && map[l][cy][cx+1] != '*'&&map[l][cy][cx+1] != '0'&&map[l][cy][cx+1] != 'O' )
                {cx++;}break;
            }
        break;
        case 't':
        case 'T':
        save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                    
                    refresh();
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 150; j++)
            {
                if ((themed[l][i][j] != 5 && revealed[l][i][j] == 1) && (map[l][i][j] == '~'||map[l][i][j] == 't'||map[l][i][j] == 'P'))
                {mvprintw(i,j,"%c",map[l][i][j]);}}}
        while(getch()!='t'){}
        save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                    int *tcty;
                    int *tctx;
                    int *tlt;
                    clear();
                    load_game_state(user, map, revealed, health_bar, food_stack, hunger_bar, tctx, tcty, tlt, levels, themed);
                    for (int i = 0; i < 50; i++)
                    {
                        for (int j = 0; j < 150; j++)
                        {
                            if (themed[l][i][j] == 5)
                            {
                                mvprintw(i, j, " ");
                            }
                        }
                    }

        break;
         
        case KEY_HOME:
            repeat;
            if(speed_boost){ repeat=2;}else{ repeat=1;}
            for(int rr=repeat;rr>0;rr--){
            if (map[l][cy - 1][cx - 1] != '_' && map[l][cy - 1][cx - 1] != '|' && map[l][cy - 1][cx - 1] != '0' && map[l][cy - 1][cx - 1] != 'O'&&map[l][cy - 1][cx - 1] != 'U'&&map[l][cy - 1][cx - 1] != 'F'&&map[l][cy - 1][cx - 1] != 'S'&&map[l][cy - 1][cx - 1] != 'G'&&map[l][cy - 1][cx - 1] != 'D' && map[l][cy - 1][cx - 1] != '=')
            {
                if (map[l][cy - 1][cx - 1] == 't')
                {
                    for (int h = 9; h > -1; h--)
                    {
                        if (health_bar[h] == 1)
                        {
                            health_bar[h] = 0;
                            break;
                        }
                    }
                    map[l][cy - 1][cx - 1] = '^';
                }
                else if (map[l][cy - 1][cx - 1] == '-' || map[l][cy - 1][cx - 1] == '~')
                {
                    map[l][cy - 1][cx - 1] = '?';
                }
                else if (map[l][cy - 1][cx - 1] == 'f')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx - 1] != 5)
                        {
                            food_stack[f] = 1;
                            map[l][cy - 1][cx - 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx - 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx - 2] == 'f')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx - 2] != 5)
                        {
                            food_stack[f] = 1;
                            map[l][cy - 1][cx - 2] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx - 2] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx - 1] == 'j')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx - 1] != 5)
                        {
                            food_stack[f] = 4;
                            map[l][cy - 1][cx - 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx - 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx - 2] == 'j')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx - 2] != 5)
                        {
                            food_stack[f] = 4;
                            map[l][cy - 1][cx - 2] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx - 2] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx - 1] == 'h')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx - 1] != 5)
                        {
                            food_stack[f] = 3;
                            map[l][cy - 1][cx - 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx - 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx - 2] == 'h')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx - 2] != 5)
                        {
                            food_stack[f] = 3;
                            map[l][cy - 1][cx - 2] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx - 2] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx - 1] == 'g')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx - 1] != 5)
                        {
                            food_stack[f] = 2;
                            map[l][cy - 1][cx - 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx - 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx - 2] == 'g')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx - 2] != 5)
                        {
                            food_stack[f] = 2;
                            map[l][cy - 1][cx - 2] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx - 2] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx - 1] == '1')
                {
                    if (themed[l][cy - 1][cx - 1] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';

                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                        map[l][cy - 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 1] == '2')
                {
                    if (themed[l][cy - 1][cx - 1] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                        map[l][cy - 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 1] == '3')
                {
                    if (themed[l][cy - 1][cx - 1] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                        map[l][cy - 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 1] == '4')
                {
                    if (themed[l][cy - 1][cx - 1] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                        map[l][cy - 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 1] == '5')
                {
                    if (themed[l][cy - 1][cx - 1] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                        map[l][cy - 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 1] == '6')
                {
                    if (themed[l][cy - 1][cx - 1] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                        map[l][cy - 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 1] == '7')
                {
                    if (themed[l][cy - 1][cx - 1] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                        map[l][cy - 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 1] == '8')
                {
                    if (themed[l][cy - 1][cx - 1] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                        map[l][cy - 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 2] == '1')
                {
                    if (themed[l][cy - 1][cx - 2] == 5)
                    {
                        map[l][cy - 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                        map[l][cy - 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 2] == '2')
                {
                    if (themed[l][cy - 1][cx - 2] == 5)
                    {
                        map[l][cy - 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                        map[l][cy - 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 2] == '3')
                {
                    if (themed[l][cy - 1][cx - 2] == 5)
                    {
                        map[l][cy - 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                        map[l][cy - 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 2] == '4')
                {
                    if (themed[l][cy - 1][cx - 2] == 5)
                    {
                        map[l][cy - 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                        map[l][cy - 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 2] == '5')
                {
                    if (themed[l][cy - 1][cx - 2] == 5)
                    {
                        map[l][cy - 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                        map[l][cy - 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 2] == '6')
                {
                    if (themed[l][cy - 1][cx - 2] == 5)
                    {
                        map[l][cy - 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                        map[l][cy - 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 2] == '7')
                {
                    if (themed[l][cy - 1][cx - 2] == 5)
                    {
                        map[l][cy - 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                        map[l][cy - 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 2] == '8')
                {
                    if (themed[l][cy - 1][cx - 2] == 5)
                    {
                        map[l][cy - 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                        map[l][cy - 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 1] == 'k')
                {
                    if (themed[l][cy - 1][cx - 1] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';
                    }
                    else
                    {
                        akey++;
                        mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                        map[l][cy - 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 1] == 'C')
                {
                    if (themed[l][cy - 1][cx - 1] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';
                    }
                    else
                    {
                        coin += rand() % 50 + 1;
                        mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                        map[l][cy - 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 1] == 'c')
                {
                    if (themed[l][cy - 1][cx - 1] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';
                    }
                    else
                    {
                        coin += rand() % 5 + 1;
                        mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                        map[l][cy - 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 2] == 'k')
                {
                    if (themed[l][cy - 1][cx - 2] == 5)
                    {
                        map[l][cy - 1][cx - 2] = '.';
                        map[l][cy - 1][cx - 1] = '.';
                    }
                    else
                    {
                        akey++;
                        mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                        map[l][cy - 1][cx - 2] = '.';
                        map[l][cy - 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 2] == 'C')
                {
                    if (themed[l][cy - 1][cx - 2] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';
                        map[l][cy - 1][cx - 2] = '.';
                    }
                    else
                    {
                        coin += rand() % 50 + 1;
                        mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                        map[l][cy - 1][cx - 1] = '.';
                        map[l][cy - 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy - 1][cx - 2] == 'c')
                {
                    if (themed[l][cy - 1][cx - 2] == 5)
                    {
                        map[l][cy - 1][cx - 1] = '.';
                        map[l][cy - 1][cx - 2] = '.';
                    }
                    else
                    {
                        coin += rand() % 5 + 1;
                        mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                        map[l][cy - 1][cx - 1] = '.';
                        map[l][cy - 1][cx - 2] = '.';
                    }
                }
                if (map[l][cy][cx - 1] == 'f'||map[l][cy][cx - 1] == 'g'||map[l][cy][cx - 1] == 'h'||map[l][cy][cx - 1] == 'j')
                {
                    mvprintw(cy - 1, cx - 1, "@");
                    move(cy - 1, cx - 1);
                    cy -= 1;
                    cx -= 1;
                }
                else
                {
                    mvprintw(cy - 1, cx - 1, "@");
                    mvprintw(cy, cx, "%c", map[l][cy][cx]);
                    move(cy - 1, cx - 1);
                    cy -= 1;
                    cx -= 1;
                }
            }
            }
            break;
        case KEY_PPAGE:
            repeat;
            if(speed_boost){ repeat=2;}else{ repeat=1;}
            for(int rr=repeat;rr>0;rr--){
            if ((unlocked == 1 || map[l][cy - 1][cx + 1] != '*') && map[l][cy - 1][cx + 1] != '_' && map[l][cy - 1][cx + 1] != '|' && map[l][cy - 1][cx + 1] != 'O'&&map[l][cy - 1][cx + 1] != 'U'&&map[l][cy - 1][cx + 1] != 'F'&&map[l][cy - 1][cx + 1] != 'S'&&map[l][cy - 1][cx + 1] != 'G'&&map[l][cy - 1][cx + 1] != 'D' && map[l][cy - 1][cx + 1] != 'O' && map[l][cy - 1][cx + 1] != '=')
            {
                if (map[l][cy - 1][cx + 1] == 't')
                {
                    for (int h = 9; h > -1; h--)
                    {
                        if (health_bar[h] == 1)
                        {
                            health_bar[h] = 0;
                            break;
                        }
                    }
                    map[l][cy - 1][cx + 1] = '^';
                }
                else if (map[l][cy - 1][cx + 1] == 'P')
                {
                    trap_m = 3;
                    for (int h = 9; h > -1; h--)
                    {
                        if (health_bar[h] == 1)
                        {
                            health_bar[h] = 0;
                            break;
                        }
                    }
                    map[l][cy - 1][cx + 1] = 'V';
                }
                else if (map[l][cy - 1][cx + 1] == '-' || map[l][cy - 1][cx + 1] == '~')
                {
                    map[l][cy - 1][cx + 1] = '?';
                }
                else if (map[l][cy - 1][cx + 1] == 'f')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx + 1] != 5)
                        {
                            food_stack[f] = 1;
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx] == 'f')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx] != 5)
                        {
                            food_stack[f] = 1;
                            map[l][cy - 1][cx] = '.';
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx] = '.';
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx + 1] == 'g')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx + 1] != 5)
                        {
                            food_stack[f] = 2;
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx] == 'g')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx] != 5)
                        {
                            food_stack[f] = 2;
                            map[l][cy - 1][cx] = '.';
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx] = '.';
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx + 1] == 'h')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx + 1] != 5)
                        {
                            food_stack[f] = 3;
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx] == 'h')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx] != 5)
                        {
                            food_stack[f] = 3;
                            map[l][cy - 1][cx] = '.';
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx] = '.';
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx + 1] == 'j')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx + 1] != 5)
                        {
                            food_stack[f] = 4;
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy - 1][cx] == 'j')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy - 1][cx] != 5)
                        {
                            food_stack[f] = 4;
                            map[l][cy - 1][cx] = '.';
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy - 1][cx] = '.';
                            map[l][cy - 1][cx + 1] = '.';
                            break;
                        }
                    }
                }


                else if (map[l][cy - 1][cx + 1] == 'k')
                {
                    if (themed[l][cy - 1][cx + 1] == 5)
                    {
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        akey++;
                        mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                        map[l][cy - 1][cx + 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx + 1] == 'C')
                {
                    if (themed[l][cy - 1][cx + 1] == 5)
                    {
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        coin += rand() % 50 + 1;
                        mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                        map[l][cy - 1][cx + 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx + 1] == '1')
                {
                    if (themed[l][cy - 1][cx + 1] == 5)
                    {
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                        map[l][cy - 1][cx + 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx + 1] == '2')
                {
                    if (themed[l][cy - 1][cx + 1] == 5)
                    {
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                        map[l][cy - 1][cx + 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx + 1] == '3')
                {
                    if (themed[l][cy - 1][cx + 1] == 5)
                    {
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                        map[l][cy - 1][cx + 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx + 1] == '4')
                {
                    if (themed[l][cy - 1][cx + 1] == 5)
                    {
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                        map[l][cy - 1][cx + 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx + 1] == '5')
                {
                    if (themed[l][cy - 1][cx + 1] == 5)
                    {
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                        map[l][cy - 1][cx + 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx + 1] == '6')
                {
                    if (themed[l][cy - 1][cx + 1] == 5)
                    {
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                        map[l][cy - 1][cx + 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx + 1] == '7')
                {
                    if (themed[l][cy - 1][cx + 1] == 5)
                    {
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                        map[l][cy - 1][cx + 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx + 1] == '8')
                {
                    if (themed[l][cy - 1][cx + 1] == 5)
                    {
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                        map[l][cy - 1][cx + 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx] == '1')
                {
                    if (themed[l][cy - 1][cx] == 5)
                    {
                        map[l][cy - 1][cx] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                        map[l][cy - 1][cx] = '.';
                    }
                }
                else if (map[l][cy - 1][cx] == '2')
                {
                    if (themed[l][cy - 1][cx] == 5)
                    {
                        map[l][cy - 1][cx] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                        map[l][cy - 1][cx] = '.';
                    }
                }
                else if (map[l][cy - 1][cx] == '3')
                {
                    if (themed[l][cy - 1][cx] == 5)
                    {
                        map[l][cy - 1][cx] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                        map[l][cy - 1][cx] = '.';
                    }
                }
                else if (map[l][cy - 1][cx] == '4')
                {
                    if (themed[l][cy - 1][cx] == 5)
                    {
                        map[l][cy - 1][cx] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                        map[l][cy - 1][cx] = '.';
                    }
                }
                else if (map[l][cy - 1][cx] == '5')
                {
                    if (themed[l][cy - 1][cx] == 5)
                    {
                        map[l][cy - 1][cx] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                        map[l][cy - 1][cx] = '.';
                    }
                }
                else if (map[l][cy - 1][cx] == '6')
                {
                    if (themed[l][cy - 1][cx] == 5)
                    {
                        map[l][cy - 1][cx] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                        map[l][cy - 1][cx] = '.';
                    }
                }
                else if (map[l][cy - 1][cx] == '7')
                {
                    if (themed[l][cy - 1][cx] == 5)
                    {
                        map[l][cy - 1][cx] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                        map[l][cy - 1][cx] = '.';
                    }
                }
                else if (map[l][cy - 1][cx] == '8')
                {
                    if (themed[l][cy - 1][cx] == 5)
                    {
                        map[l][cy - 1][cx] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                        map[l][cy - 1][cx + 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx + 1] == 'c')
                {
                    if (themed[l][cy - 1][cx + 1] == 5)
                    {
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        coin += rand() % 5 + 1;
                        mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                        map[l][cy - 1][cx + 1] = '.';
                    }
                }
                else if (map[l][cy - 1][cx] == 'k')
                {
                    if (themed[l][cy - 1][cx] == 5)
                    {
                        map[l][cy - 1][cx] = '.';
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        akey++;
                        mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                        map[l][cy - 1][cx + 1] = '.';
                        map[l][cy - 1][cx] = '.';
                    }
                }
                else if (map[l][cy - 1][cx] == 'C')
                {
                    if (themed[l][cy - 1][cx] == 5)
                    {
                        map[l][cy - 1][cx] = '.';
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        coin += rand() % 50 + 1;
                        mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                        map[l][cy - 1][cx + 1] = '.';
                        map[l][cy - 1][cx] = '.';
                    }
                }
                else if (map[l][cy - 1][cx] == 'c')
                {
                    if (themed[l][cy - 1][cx] == 5)
                    {
                        map[l][cy - 1][cx] = '.';
                        map[l][cy - 1][cx + 1] = '.';
                    }
                    else
                    {
                        coin += rand() % 5 + 1;
                        mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                        map[l][cy - 1][cx + 1] = '.';
                        map[l][cy - 1][cx] = '.';
                    }
                }
                if (map[l][cy][cx - 1] == 'f'||map[l][cy][cx - 1] == 'g'||map[l][cy][cx - 1] == 'h'||map[l][cy][cx - 1] == 'j')
                {
                    mvprintw(cy - 1, cx + 1, "@");
                    move(cy - 1, cx + 1);
                    cx += 1;
                    cy -= 1;
                }
                else
                {
                    mvprintw(cy - 1, cx + 1, "@");
                    mvprintw(cy, cx, "%c", map[l][cy][cx]);
                    move(cy - 1, cx + 1);
                    cy -= 1;
                    cx += 1;
                }
            }
            }
            break;
        case 'c':
        case 'C':
            if(clashed==1){
                int tempdone=0;
                for(int i=10;i<30;i++){
                    for(int j=35;j<135;j++){
                        if(map[5][i][j]=='U'||map[5][i][j]=='D'||map[5][i][j]=='F'||map[5][i][j]=='G'||map[5][i][j]=='S'||map[5][i][j]=='B'){
                            tempdone=1;                            
                        }
                    }
                    if(tempdone){break;}
                }
                refresh();
                if(!tempdone){
                clashed=0;
                 levels[l] = 1;
                    l=beforel;
                    cy=beforecy;
                    cx=beforecx;
                    map[l][cy][cx]='.';
                    levels[l] = 1;
                    for (int i = 0; i < 50; i++)
                            k = 0;
                            secret = 0;
                            m = 0;
                            forbidden = 0;
                            placed = 0, done = 0;
                            error = 0;
                            unlocked = 0;                          
                            save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                            play_game(levels[l]);
            }}
            // else if(map[l][cy][cx]=='^'){
                else{
                if(map[l][cy][cx]=='^'){
                beforel=l;
                beforecx=cx;
                beforecy=cy;
            save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
            clear();
            refresh();
            display_clash_room();}}
            // display_clash_room();}}
            break;
        case KEY_END:
            repeat;
            if(speed_boost){ repeat=2;}else{ repeat=1;}
            for(int rr=repeat;rr>0;rr--){
            if ((unlocked == 1 || map[l][cy + 1][cx - 1] != '*') && map[l][cy + 1][cx - 1] != '_' && map[l][cy + 1][cx - 1] != '|' && map[l][cy + 1][cx - 1] != '0' && map[l][cy + 1][cx - 1] != 'O'&&map[l][cy + 1][cx - 1] != 'U'&&map[l][cy + 1][cx - 1] != 'F'&&map[l][cy + 1][cx - 1] != 'S'&&map[l][cy + 1][cx - 1] != 'G'&&map[l][cy + 1][cx - 1] != 'D' && map[l][cy + 1][cx - 1] != '=')
            {
                if (map[l][cy + 1][cx - 1] == 't')
                {

                    for (int h = 9; h > -1; h--)
                    {
                        if (health_bar[h] == 1)
                        {
                            health_bar[h] = 0;
                            break;
                        }
                    }
                    map[l][cy + 1][cx - 1] = '^';
                }
                else if (map[l][cy + 1][cx - 1] == 'P')
                {
                    trap_m = 3;
                    for (int h = 9; h > -1; h--)
                    {
                        if (health_bar[h] == 1)
                        {
                            health_bar[h] = 0;
                            break;
                        }
                    }
                    map[l][cy + 1][cx - 1] = 'V';
                }
                else if (map[l][cy + 1][cx - 1] == '-' || map[l][cy + 1][cx - 1] == '~')
                {
                    map[l][cy + 1][cx - 1] = '?';
                }
                else if (map[l][cy + 1][cx - 1] == 'f')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy + 1][cx - 1] != 5)
                        {
                            food_stack[f] = 1;
                            map[l][cy + 1][cx - 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy + 1][cx - 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy + 1][cx - 2] == 'f')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy + 1][cx - 2] != 5)
                        {
                            food_stack[f] = 1;
                            map[l][cy + 1][cx - 2] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy + 1][cx - 2] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy + 1][cx - 1] == 'g')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy + 1][cx - 1] != 5)
                        {
                            food_stack[f] = 2;
                            map[l][cy + 1][cx - 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy + 1][cx - 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy + 1][cx - 2] == 'g')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy + 1][cx - 2] != 5)
                        {
                            food_stack[f] = 2;
                            map[l][cy + 1][cx - 2] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy + 1][cx - 2] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy + 1][cx - 1] == 'h')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy + 1][cx - 1] != 5)
                        {
                            food_stack[f] = 3;
                            map[l][cy + 1][cx - 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy + 1][cx - 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy + 1][cx - 2] == 'h')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy + 1][cx - 2] != 5)
                        {
                            food_stack[f] = 3;
                            map[l][cy + 1][cx - 2] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy + 1][cx - 2] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy + 1][cx - 1] == 'j')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy + 1][cx - 1] != 5)
                        {
                            food_stack[f] = 4;
                            map[l][cy + 1][cx - 1] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy + 1][cx - 1] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy + 1][cx - 2] == 'j')
                {
                    for (int f = 0; f < 5; f++)
                    {
                        if (food_stack[f] == 0 && themed[l][cy + 1][cx - 2] != 5)
                        {
                            food_stack[f] = 4;
                            map[l][cy + 1][cx - 2] = '.';
                            break;
                        }
                        else if (food_stack[f] == 0)
                        {
                            map[l][cy + 1][cx - 2] = '.';
                            break;
                        }
                    }
                }
                else if (map[l][cy + 1][cx - 1] == '1')
                {
                    if (themed[l][cy + 1][cx - 1] == 5)
                    {
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                        map[l][cy + 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 1] == '2')
                {
                    if (themed[l][cy + 1][cx - 1] == 5)
                    {
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                        map[l][cy + 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 1] == '3')
                {
                    if (themed[l][cy + 1][cx - 1] == 5)
                    {
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                        map[l][cy + 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 1] == '4')
                {
                    if (themed[l][cy + 1][cx - 1] == 5)
                    {
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                        map[l][cy + 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 1] == '5')
                {
                    if (themed[l][cy + 1][cx - 1] == 5)
                    {
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                        map[l][cy + 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 1] == '6')
                {
                    if (themed[l][cy + 1][cx - 1] == 5)
                    {
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                        map[l][cy + 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 1] == '7')
                {
                    if (themed[l][cy + 1][cx - 1] == 5)
                    {
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                        map[l][cy + 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 1] == '8')
                {
                    if (themed[l][cy + 1][cx - 1] == 5)
                    {
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                        map[l][cy + 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 2] == '1')
                {
                    if (themed[l][cy + 1][cx - 2] == 5)
                    {
                        map[l][cy + 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                        map[l][cy + 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 2] == '2')
                {
                    if (themed[l][cy + 1][cx - 2] == 5)
                    {
                        map[l][cy + 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                        map[l][cy + 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 2] == '3')
                {
                    if (themed[l][cy + 1][cx - 2] == 5)
                    {
                        map[l][cy + 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                        map[l][cy + 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 2] == '4')
                {
                    if (themed[l][cy + 1][cx - 2] == 5)
                    {
                        map[l][cy + 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                        map[l][cy + 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 2] == '5')
                {
                    if (themed[l][cy + 1][cx - 2] == 5)
                    {
                        map[l][cy + 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                        map[l][cy + 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 2] == '6')
                {
                    if (themed[l][cy + 1][cx - 2] == 5)
                    {
                        map[l][cy + 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                        map[l][cy + 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 2] == '7')
                {
                    if (themed[l][cy + 1][cx - 2] == 5)
                    {
                        map[l][cy + 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                        map[l][cy + 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 2] == '8')
                {
                    if (themed[l][cy + 1][cx - 2] == 5)
                    {
                        map[l][cy + 1][cx - 2] = '.';
                    }
                    else
                    {
                        mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                        map[l][cy + 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 1] == 'k')
                {
                    if (themed[l][cy + 1][cx - 1] == 5)
                    {
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        akey++;
                        mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                        map[l][cy + 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 1] == 'C')
                {
                    if (themed[l][cy + 1][cx - 1] == 5)
                    {
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        coin += rand() % 50 + 1;
                        mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                        map[l][cy + 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 1] == 'c')
                {
                    if (themed[l][cy + 1][cx - 1] == 5)
                    {
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        coin += rand() % 5 + 1;
                        mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                        map[l][cy + 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 2] == 'k')
                {
                    if (themed[l][cy + 1][cx - 2] == 5)
                    {
                        map[l][cy + 1][cx - 2] = '.';
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        akey++;
                        mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                        map[l][cy + 1][cx - 2] = '.';
                        map[l][cy + 1][cx - 1] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 2] == 'C')
                {
                    if (themed[l][cy + 1][cx - 2] == 5)
                    {
                        map[l][cy + 1][cx - 2] = '.';
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        coin += rand() % 50 + 1;
                        mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                        map[l][cy + 1][cx - 1] = '.';
                        map[l][cy + 1][cx - 2] = '.';
                    }
                }
                else if (map[l][cy + 1][cx - 2] == 'c')
                {
                    if (themed[l][cy + 1][cx - 2] == 5)
                    {
                        map[l][cy + 1][cx - 2] = '.';
                        map[l][cy + 1][cx - 1] = '.';
                    }
                    else
                    {
                        coin += rand() % 5 + 1;
                        mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                        map[l][cy + 1][cx - 1] = '.';
                        map[l][cy + 1][cx - 2] = '.';
                    }
                }
                if (map[l][cy][cx - 1] == 'f'||map[l][cy][cx - 1] == 'g'||map[l][cy][cx - 1] == 'h'||map[l][cy][cx - 1] == 'j')
                {
                    mvprintw(cy + 1, cx - 1, "@");
                    move(cy + 1, cx - 1);
                    cy += 1;
                    cx -= 1;
                }
                else
                {
                    mvprintw(cy + 1, cx - 1, "@");
                    mvprintw(cy, cx, "%c", map[l][cy][cx]);
                    move(cy + 1, cx - 1);
                    cy += 1;
                    cx -= 1;}
                                }
                                }
                                break;
                case KEY_NPAGE:
                    repeat;
                    if(speed_boost){ repeat=2;}else{ repeat=1;}
                    for(int rr=repeat;rr>0;rr--){
                    if ((unlocked == 1 || map[l][cy + 1][cx + 1] != '*') && map[l][cy + 1][cx + 1] != '_' && map[l][cy + 1][cx + 1] != '|' && map[l][cy + 1][cx + 1] != '0' && map[l][cy + 1][cx + 1] != 'O'&&map[l][cy + 1][cx + 1] != 'U'&&map[l][cy + 1][cx + 1] != 'F'&&map[l][cy + 1][cx + 1] != 'S'&&map[l][cy + 1][cx + 1] != 'G'&&map[l][cy + 1][cx + 1] != 'D' && map[l][cy + 1][cx + 1] != '=')
                    {
                        if (map[l][cy + 1][cx + 1] == 't')
                        {
                            for (int h = 9; h > -1; h--)
                            {
                                if (health_bar[h] == 1)
                                {
                                    health_bar[h] = 0;
                                    break;
                                }
                            }
                            map[l][cy + 1][cx + 1] = '^';
                        }
                        else if (map[l][cy + 1][cx + 1] == 'P')
                        {
                            trap_m = 3;
                            for (int h = 9; h > -1; h--)
                            {
                                if (health_bar[h] == 1)
                                {
                                    health_bar[h] = 0;
                                    break;
                                }
                            }
                            map[l][cy + 1][cx + 1] = 'V';
                        }
                        else if (map[l][cy + 1][cx + 1] == '-' || map[l][cy + 1][cx + 1] == '~')
                        {
                            map[l][cy + 1][cx + 1] = '?';
                        }
                        else if (map[l][cy + 1][cx + 1] == 'f')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx + 1] != 5)
                                {
                                    food_stack[f] = 1;
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'f')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx] != 5)
                                {
                                    food_stack[f] = 1;
                                    map[l][cy + 1][cx] = '.';
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx] = '.';
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == 'g')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx + 1] != 5)
                                {
                                    food_stack[f] = 2;
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'g')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx] != 5)
                                {
                                    food_stack[f] = 2;
                                    map[l][cy + 1][cx] = '.';
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx] = '.';
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == 'h')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx + 1] != 5)
                                {
                                    food_stack[f] = 3;
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'h')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx] != 5)
                                {
                                    food_stack[f] = 3;
                                    map[l][cy + 1][cx] = '.';
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx] = '.';
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == 'j')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx + 1] != 5)
                                {
                                    food_stack[f] = 4;
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'j')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx] != 5)
                                {
                                    food_stack[f] = 4;
                                    map[l][cy + 1][cx] = '.';
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx] = '.';
                                    map[l][cy + 1][cx + 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == 'k')
                        {
                            if (themed[l][cy + 1][cx + 1] == 5)
                            {
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                akey++;
                                mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                                map[l][cy + 1][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == '1')
                        {
                            if (themed[l][cy + 1][cx + 1] == 5)
                            {
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                                map[l][cy + 1][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == '2')
                        {
                            if (themed[l][cy + 1][cx + 1] == 5)
                            {
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                                map[l][cy + 1][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == '3')
                        {
                            if (themed[l][cy + 1][cx + 1] == 5)
                            {
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                                map[l][cy + 1][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == '4')
                        {
                            if (themed[l][cy + 1][cx + 1] == 5)
                            {
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                                map[l][cy + 1][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == '5')
                        {
                            if (themed[l][cy + 1][cx + 1] == 5)
                            {
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                                map[l][cy + 1][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == '6')
                        {
                            if (themed[l][cy + 1][cx + 1] == 5)
                            {
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                                map[l][cy + 1][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == '7')
                        {
                            if (themed[l][cy + 1][cx + 1] == 5)
                            {
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                                map[l][cy + 1][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == '8')
                        {
                            if (themed[l][cy + 1][cx + 1] == 5)
                            {
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                                map[l][cy + 1][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx ] == '1')
                        {
                            if (themed[l][cy + 1][cx ] == 5)
                            {
                                map[l][cy + 1][cx ] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                                map[l][cy + 1][cx ] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx ] == '2')
                        {
                            if (themed[l][cy + 1][cx ] == 5)
                            {
                                map[l][cy + 1][cx ] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                                map[l][cy + 1][cx ] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx ] == '3')
                        {
                            if (themed[l][cy + 1][cx ] == 5)
                            {
                                map[l][cy + 1][cx ] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                                map[l][cy + 1][cx ] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx ] == '4')
                        {
                            if (themed[l][cy + 1][cx ] == 5)
                            {
                                map[l][cy + 1][cx ] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                                map[l][cy + 1][cx ] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx ] == '5')
                        {
                            if (themed[l][cy + 1][cx ] == 5)
                            {
                                map[l][cy + 1][cx ] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                                map[l][cy + 1][cx ] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx ] == '6')
                        {
                            if (themed[l][cy + 1][cx ] == 5)
                            {
                                map[l][cy + 1][cx ] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                                map[l][cy + 1][cx ] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx ] == '7')
                        {
                            if (themed[l][cy + 1][cx ] == 5)
                            {
                                map[l][cy + 1][cx ] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                                map[l][cy + 1][cx ] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx ] == '8')
                        {
                            if (themed[l][cy + 1][cx ] == 5)
                            {
                                map[l][cy + 1][cx ] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                                map[l][cy + 1][cx ] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == 'C')
                        {
                            if (themed[l][cy + 1][cx + 1] == 5)
                            {
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                coin += rand() % 50 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy + 1][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx + 1] == 'c')
                        {
                            if (themed[l][cy + 1][cx + 1] == 5)
                            {
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                coin += rand() % 5 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy + 1][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'k')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                akey++;
                                mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                                map[l][cy + 1][cx] = '.';
                                map[l][cy + 1][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'C')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                coin += rand() % 50 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy + 1][cx + 1] = '.';
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'c')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                                map[l][cy + 1][cx + 1] = '.';
                            }
                            else
                            {
                                coin += rand() % 5 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy + 1][cx + 1] = '.';
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        if (map[l][cy][cx - 1] == 'f'||map[l][cy][cx - 1] == 'g'||map[l][cy][cx - 1] == 'h'||map[l][cy][cx - 1] == 'j')
                        {
                            mvprintw(cy + 1, cx + 1, "@");
                            move(cy + 1, cx + 1);
                            cx += 1;
                            cy += 1;
                        }
                        else
                        {
                            mvprintw(cy + 1, cx + 1, "@");
                            mvprintw(cy, cx, "%c", map[l][cy][cx]);
                            move(cy + 1, cx + 1);
                            cy += 1;
                            cx += 1;
                        }
                    }
                    }
                    break;
                case KEY_DOWN:
                    repeat;
                    if(speed_boost){ repeat=2;}else{ repeat=1;}
                    for(int rr=repeat;rr>0;rr--){
                    if (map[l][cy + 1][cx] == '=')
                    {
                        window_reveal(1, cy, cx);
                        break;
                    }
                    else if (map[l][cy + 1][cx] == '*' && done == 0)
                    {
                        save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                        clear();
                        refresh();
                        display_lock();
                        save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                        clear();
                        refresh();
                        int *tcy;
                        int *tcx;
                        int *tl;
                        load_game_state(user, map, revealed, health_bar, food_stack, hunger_bar, tcx, tcy, tl, levels, themed);
                        for (int i = 0; i < 50; i++)
                        {
                            for (int j = 0; j < 150; j++)
                            {
                                if (themed[l][i][j] == 5)
                                {
                                    mvprintw(i, j, " ");
                                }
                            }
                        }
                        break;
                    }
                    if ((unlocked == 1 || map[l][cy + 1][cx] != '*') && map[l][cy + 1][cx] != '_' && map[l][cy + 1][cx] != '|' && map[l][cy + 1][cx] != '0' && map[l][cy + 1][cx] != 'O'&&map[l][cy+1][cx] != 'U'&&map[l][cy +1][cx] != 'F'&&map[l][cy +1][cx] != 'S'&&map[l][cy + 1][cx] != 'G'&&map[l][cy + 1][cx] != 'D')
                    {
                        if (map[l][cy + 1][cx] == 't')
                        {
                            for (int h = 9; h > -1; h--)
                            {
                                if (health_bar[h] == 1)
                                {
                                    health_bar[h] = 0;
                                    break;
                                }
                            }
                            map[l][cy + 1][cx] = '^';
                        }
                        else if (map[l][cy + 1][cx] == 'P')
                        {
                            trap_m = 3;
                            for (int h = 9; h > -1; h--)
                            {
                                if (health_bar[h] == 1)
                                {
                                    health_bar[h] = 0;
                                    break;
                                }
                            }
                            map[l][cy + 1][cx] = 'V';
                        }
                        else if (map[l][cy + 1][cx] == '-' || map[l][cy + 1][cx] == '~')
                        {
                            map[l][cy + 1][cx] = '?';
                        }
                        else if (map[l][cy + 1][cx] == 'f')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx] != 5)
                                {
                                    food_stack[f] = 1;
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == 'f')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx - 1] != 5)
                                {
                                    food_stack[f] = 1;
                                    map[l][cy + 1][cx - 1] = '.';
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx - 1] = '.';
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'g')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx] != 5)
                                {
                                    food_stack[f] = 2;
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == 'g')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx - 1] != 5)
                                {
                                    food_stack[f] = 2;
                                    map[l][cy + 1][cx - 1] = '.';
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx - 1] = '.';
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'h')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx] != 5)
                                {
                                    food_stack[f] = 3;
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == 'h')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx - 1] != 5)
                                {
                                    food_stack[f] = 3;
                                    map[l][cy + 1][cx - 1] = '.';
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx - 1] = '.';
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'j')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx] != 5)
                                {
                                    food_stack[f] = 4;
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == 'j')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy + 1][cx - 1] != 5)
                                {
                                    food_stack[f] = 4;
                                    map[l][cy + 1][cx - 1] = '.';
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy + 1][cx - 1] = '.';
                                    map[l][cy + 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'k')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                            }
                            else
                            {
                                akey++;
                                mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'C')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                            }
                            else
                            {
                                coin += rand() % 50 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == '1')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == '2')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == '3')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == '4')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == '5')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == '6')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == '7')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == '8')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == '1')
                        {
                            if (themed[l][cy + 1][cx - 1] == 5)
                            {
                                map[l][cy + 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                                map[l][cy + 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == '2')
                        {
                            if (themed[l][cy + 1][cx - 1] == 5)
                            {
                                map[l][cy + 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                                map[l][cy + 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == '3')
                        {
                            if (themed[l][cy + 1][cx - 1] == 5)
                            {
                                map[l][cy + 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                                map[l][cy + 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == '4')
                        {
                            if (themed[l][cy + 1][cx - 1] == 5)
                            {
                                map[l][cy + 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                                map[l][cy + 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == '5')
                        {
                            if (themed[l][cy + 1][cx - 1] == 5)
                            {
                                map[l][cy + 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                                map[l][cy + 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == '6')
                        {
                            if (themed[l][cy + 1][cx - 1] == 5)
                            {
                                map[l][cy + 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                                map[l][cy + 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == '7')
                        {
                            if (themed[l][cy + 1][cx - 1] == 5)
                            {
                                map[l][cy + 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                                map[l][cy + 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == '8')
                        {
                            if (themed[l][cy + 1][cx - 1] == 5)
                            {
                                map[l][cy + 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                                map[l][cy + 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx] == 'c')
                        {
                            if (themed[l][cy + 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                            }
                            else
                            {
                                coin += rand() % 5 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy + 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == 'k')
                        {
                            if (themed[l][cy + 1][cx - 1] == 5)
                            {
                                map[l][cy + 1][cx - 1] = '.';
                                map[l][cy + 1][cx] = '.';
                            }
                            else
                            {
                                akey++;
                                mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                                map[l][cy + 1][cx] = '.';
                                map[l][cy + 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == 'C')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                                map[l][cy + 1][cx - 1] = '.';
                                eat = 1;
                            }
                            else
                            {
                                coin += rand() % 50 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy + 1][cx - 1] = '.';
                                map[l][cy + 1][cx] = '.';
                                eat = 1;
                            }
                        }
                        else if (map[l][cy + 1][cx - 1] == 'c')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy + 1][cx] = '.';
                                map[l][cy + 1][cx - 1] = '.';
                                eat = 1;
                            }
                            else
                            {
                                coin += rand() % 5 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy + 1][cx - 1] = '.';
                                map[l][cy + 1][cx] = '.';
                                eat = 1;
                            }
                        }
                        if (map[l][cy][cx - 1] == 'f'||map[l][cy][cx - 1] == 'g'||map[l][cy][cx - 1] == 'h'||map[l][cy][cx - 1] == 'j')
                        {
                            mvprintw(cy + 1, cx, "@");
                            move(cy + 1, cx);
                            cy += 1;
                        }
                        else
                        {
                            mvprintw(cy + 1, cx, "@");
                            mvprintw(cy, cx, "%c", map[l][cy][cx]);
                            move(cy + 1, cx);
                            cy += 1;
                        }
                    }
                    }
                    break;
                case KEY_UP:
                    repeat;
                    if(speed_boost){ repeat=2;}else{ repeat=1;}
                    for(int rr=repeat;rr>0;rr--){
                    if (map[l][cy - 1][cx] == '=')
                    {
                        window_reveal(2, cy, cx);
                        break;
                    }
                    else if (map[l][cy - 1][cx] == '*' && done == 0)
                    {
                        save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                        clear();
                        refresh();
                        display_lock();
                        save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                        clear();
                        refresh();
                        int *tcy;
                        int *tcx;
                        int *tl;
                        load_game_state(user, map, revealed, health_bar, food_stack, hunger_bar, tcx, tcy, tl, levels, themed);
                        for (int i = 0; i < 50; i++)
                        {
                            for (int j = 0; j < 150; j++)
                            {
                                if (themed[l][i][j] == 5)
                                {
                                    mvprintw(i, j, " ");
                                }
                            }
                        }
                        break;
                    }
                    if ((unlocked == 1 || map[l][cy - 1][cx] != '*') && map[l][cy - 1][cx] != '_' && map[l][cy - 1][cx] != '|' && map[l][cy - 1][cx] != '0' && map[l][cy - 1][cx] != 'O'&&map[l][cy-1][cx] != 'U'&&map[l][cy -1][cx] != 'F'&&map[l][cy -1][cx] != 'S'&&map[l][cy - 1][cx] != 'G'&&map[l][cy - 1][cx] != 'D'
)
                    {
                        if (map[l][cy - 1][cx] == 't')
                        {
                            for (int h = 9; h > -1; h--)
                            {
                                if (health_bar[h] == 1)
                                {
                                    health_bar[h] = 0;
                                    break;
                                }
                            }
                            map[l][cy - 1][cx] = '^';
                        }
                        else if (map[l][cy - 1][cx] == 'P')
                        {
                            trap_m = 3;
                            for (int h = 9; h > -1; h--)
                            {
                                if (health_bar[h] == 1)
                                {
                                    health_bar[h] = 0;
                                    break;
                                }
                            }
                            map[l][cy - 1][cx] = 'V';
                        }
                        else if (map[l][cy - 1][cx] == '-' || map[l][cy - 1][cx] == '~')
                        {
                            map[l][cy - 1][cx] = '?';
                        }
                        else if (map[l][cy - 1][cx] == 'f')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy - 1][cx] != 5)
                                {
                                    food_stack[f] = 1;
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == 'f')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy - 1][cx - 1] != 5)
                                {
                                    food_stack[f] = 1;
                                    map[l][cy - 1][cx - 1] = '.';
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy - 1][cx - 1] = '.';
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy - 1][cx] == 'g')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy - 1][cx] != 5)
                                {
                                    food_stack[f] = 2;
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == 'g')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy - 1][cx - 1] != 5)
                                {
                                    food_stack[f] = 2;
                                    map[l][cy - 1][cx - 1] = '.';
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy - 1][cx - 1] = '.';
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy - 1][cx] == 'h')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy - 1][cx] != 5)
                                {
                                    food_stack[f] = 3;
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == 'h')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy - 1][cx - 1] != 5)
                                {
                                    food_stack[f] = 3;
                                    map[l][cy - 1][cx - 1] = '.';
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy - 1][cx - 1] = '.';
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy - 1][cx] == 'j')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy - 1][cx] != 5)
                                {
                                    food_stack[f] = 4;
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == 'j')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy - 1][cx - 1] != 5)
                                {
                                    food_stack[f] = 4;
                                    map[l][cy - 1][cx - 1] = '.';
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy - 1][cx - 1] = '.';
                                    map[l][cy - 1][cx] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy - 1][cx] == 'k')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx] = '.';
                            }
                            else
                            {
                                akey++;
                                mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                                map[l][cy - 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx] == 'C')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx] = '.';
                            }
                            else
                            {
                                coin += rand() % 50 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy - 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx] == 'c')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx] = '.';
                            }
                            else
                            {
                                coin += rand() % 5 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy - 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx] == '1')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                                map[l][cy - 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx] == '2')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                                map[l][cy - 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx] == '3')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                                map[l][cy - 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx] == '4')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                                map[l][cy - 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx] == '5')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                                map[l][cy - 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx] == '6')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                                map[l][cy - 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx] == '7')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                                map[l][cy - 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx] == '8')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                                map[l][cy - 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == '1')
                        {
                            if (themed[l][cy - 1][cx - 1] == 5)
                            {
                                map[l][cy - 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                                map[l][cy - 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == '2')
                        {
                            if (themed[l][cy - 1][cx - 1] == 5)
                            {
                                map[l][cy - 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                                map[l][cy - 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == '3')
                        {
                            if (themed[l][cy - 1][cx - 1] == 5)
                            {
                                map[l][cy - 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                                map[l][cy - 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == '4')
                        {
                            if (themed[l][cy - 1][cx - 1] == 5)
                            {
                                map[l][cy - 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                                map[l][cy - 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == '5')
                        {
                            if (themed[l][cy - 1][cx - 1] == 5)
                            {
                                map[l][cy - 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                                map[l][cy - 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == '6')
                        {
                            if (themed[l][cy - 1][cx - 1] == 5)
                            {
                                map[l][cy - 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                                map[l][cy - 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == '7')
                        {
                            if (themed[l][cy - 1][cx - 1] == 5)
                            {
                                map[l][cy - 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                                map[l][cy - 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == '8')
                        {
                            if (themed[l][cy - 1][cx - 1] == 5)
                            {
                                map[l][cy - 1][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                                map[l][cy - 1][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == 'k')
                        {
                            if (themed[l][cy - 1][cx - 1] == 5)
                            {
                                map[l][cy - 1][cx - 1] = '.';
                                map[l][cy - 1][cx] = '.';
                            }
                            else
                            {
                                akey++;
                                mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                                map[l][cy - 1][cx - 1] = '.';
                                map[l][cy - 1][cx] = '.';
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == 'C')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx - 1] = '.';
                                map[l][cy - 1][cx] = '.';
                                eat = 1;
                            }
                            else
                            {
                                coin += rand() % 50 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy - 1][cx - 1] = '.';
                                map[l][cy - 1][cx] = '.';
                                eat = 1;
                            }
                        }
                        else if (map[l][cy - 1][cx - 1] == 'c')
                        {
                            if (themed[l][cy - 1][cx] == 5)
                            {
                                map[l][cy - 1][cx - 1] = '.';
                                map[l][cy - 1][cx] = '.';
                                eat = 1;
                            }
                            else
                            {
                                coin += rand() % 5 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy - 1][cx - 1] = '.';
                                map[l][cy - 1][cx] = '.';
                                eat = 1;
                            }
                        }
                        if (map[l][cy][cx - 1] == 'f'||map[l][cy][cx - 1] == 'g'||map[l][cy][cx - 1] == 'h'||map[l][cy][cx - 1] == 'j')
                        {
                            mvprintw(cy - 1, cx, "@");
                            move(cy - 1, cx);
                            cy -= 1;
                        }
                        else
                        {
                            mvprintw(cy - 1, cx, "@");
                            mvprintw(cy, cx, "%c", map[l][cy][cx]);
                            move(cy - 1, cx);
                            cy -= 1;
                        }
                    }
                    }
                    break;
                case ' ':
                    direction=getch();
                case 'a':
                case 'A':  
                    init_pair(108,8,COLOR_BLACK);
                    init_pair(16,COLOR_MAGENTA,COLOR_BLACK);
                    init_pair(220,220,COLOR_BLACK);
                    if(picked_gun==0){mvprintw(0,0,"YOU DO NOT PICKED ANY GUN"                      );break;}
                    else if(picked_gun>1&&picked_gun<5){
                        if(gun_stack[picked_gun-1]/10==0){mvprintw(0,0,"YOU RAN OF ARROW FOR THIS WEAPEN                          ");break;}
                    
                    if(direction==KEY_UP&&picked_gun==2){
                        attron(COLOR_PAIR(220));
                        arrowy=cy;
                        while (map[l][arrowy-1][cx] != '_' &&map[l][arrowy-1][cx] != '|' && map[l][arrowy-1][cx] != '='  && map[l][arrowy-1][cx] != '*'&&map[l][arrowy-1][cx] != '0'&&map[l][arrowy-1][cx] != 'O'&&dagger_limit<5&&map[l][arrowy][cx]!='D'&&map[l][arrowy][cx]!='G'&&map[l][arrowy][cx]!='F'&&map[l][arrowy][cx]!='U'&&map[l][arrowy][cx]!='S'&&map[l][arrowy][cx]!='B'&&map[l][arrowy][cx]!='$')
                        {arrowy--;refresh();napms(20);mvprintw(arrowy,cx,"^");if(arrowy+1!=cy){mvprintw(arrowy+1,cx,".");}; dagger_limit++;}if(gun_stack[1]>10){gun_stack[1]-=10;}else{}if(map[l][arrowy][cx]=='D'||map[l][arrowy][cx]=='F'||map[l][arrowy][cx]=='G'||map[l][arrowy][cx]=='S'||map[l][arrowy][cx]=='U'||map[l][arrowy][cx]=='B'||map[l][arrowy][cx]=='$'){if(damage_boost){mvprintw(0,24,"+ 12         "); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][arrowy][cx] -= 12;if(map[l][arrowy][cx]=='$'){damage_to_boss+=12;}};mvprintw(0,0,"NAILED IT! ->12 DAMAGE                 ");dagger_limit=0;check_dead(arrowy,cx);break;}else{dagger_limit=0;map[l][arrowy][cx]='d';break;}
                    attroff(COLOR_PAIR(220));}
                    else if (direction == KEY_LEFT && picked_gun == 2) {
                        attron(COLOR_PAIR(220));
                        arrowx = cx;
                        while (map[l][cy][arrowx-1] != '_' && map[l][cy][arrowx-1] != '|' && map[l][cy][arrowx-1] != '=' && map[l][cy][arrowx-1] != '*' && map[l][cy][arrowx-1] != '0' && map[l][cy][arrowx-1] != 'O' && dagger_limit < 5 && map[l][cy][arrowx] != 'D' && map[l][cy][arrowx] != 'G' && map[l][cy][arrowx] != 'F' && map[l][cy][arrowx] != 'U' && map[l][cy][arrowx] != 'S'&&map[l][cy][arrowx]!='B'&&map[l][cy][arrowx]!='$') {
                            arrowx--;
                            refresh();napms(20);
                            mvprintw(cy,arrowx,"<");if(arrowx+1!=cx){mvprintw(cy,arrowx+1,".");}
                            dagger_limit++;
                        }
                        if (gun_stack[1] > 10) { 
                            gun_stack[1] -= 10; 
                        }
                        if (map[l][cy][arrowx] == 'D' || map[l][cy][arrowx] == 'F' || map[l][cy][arrowx] == 'G' || map[l][cy][arrowx] == 'S' || map[l][cy][arrowx] == 'U'||map[l][cy][arrowx]=='B'||map[l][cy][arrowx]=='$') {
                            if(damage_boost){mvprintw(0,24,"+ 12         "); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][cy][arrowx] -= 12;
                            if( map[l][cy][arrowx]=='$'){damage_to_boss+=12;}}
                            mvprintw(0, 0, "NAILED IT! ->12 DAMAGE                                     ");
                            dagger_limit = 0;
                            check_dead(cy, arrowx);
                        } else {
                            dagger_limit = 0;
                            map[l][cy][arrowx] = 'd';
                        }
                        attroff(COLOR_PAIR(220));
                    }
                    if (direction == KEY_RIGHT && picked_gun == 2) {
                        attron(COLOR_PAIR(220));
                        arrowx = cx;
                        while (map[l][cy][arrowx+1] != '_' && map[l][cy][arrowx+1] != '|' && map[l][cy][arrowx+1] != '=' && map[l][cy][arrowx+1] != '*' && map[l][cy][arrowx+1] != '0' && map[l][cy][arrowx+1] != 'O' && dagger_limit < 5 && map[l][cy][arrowx] != 'D' && map[l][cy][arrowx] != 'G' && map[l][cy][arrowx] != 'F' && map[l][cy][arrowx] != 'U' && map[l][cy][arrowx] != 'S'&&map[l][cy][arrowx]!='B'&&map[l][cy][arrowx]!='$') {
                            arrowx++;
                            refresh();napms(20);
                            mvprintw(cy,arrowx,">");if(arrowx-1!=cx){mvprintw(cy,arrowx-1,".");}
                            dagger_limit++;
                        }
                        if (gun_stack[1] > 10) {
                            gun_stack[1] -= 10;
                        }
                        if (map[l][cy][arrowx] == 'D' || map[l][cy][arrowx] == 'F' || map[l][cy][arrowx] == 'G' || map[l][cy][arrowx] == 'S' || map[l][cy][arrowx] == 'U'||map[l][cy][arrowx]=='B'||map[l][cy][arrowx]=='$') {
                            if(damage_boost){mvprintw(0,24,"+ 12         "); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][cy][arrowx] -= 12; if( map[l][cy][arrowx]=='$'){damage_to_boss+=12;}}
                            mvprintw(0, 0, "NAILED IT! ->12 DAMAGE                                     ");
                            dagger_limit = 0;
                            check_dead(cy, arrowx);
                        } else {
                            dagger_limit = 0;
                            map[l][cy][arrowx] = 'd';
                        }
                        attroff(COLOR_PAIR(220));
                    }
                    if (direction == KEY_DOWN && picked_gun == 2) {
                        attron(COLOR_PAIR(220));
                        arrowy = cy;
                        while (map[l][arrowy+1][cx] != '_' && map[l][arrowy+1][cx] != '|' && map[l][arrowy+1][cx] != '=' && map[l][arrowy+1][cx] != '*' && map[l][arrowy+1][cx] != '0' && map[l][arrowy+1][cx] != 'O' && dagger_limit < 5 && map[l][arrowy][cx] != 'D' && map[l][arrowy][cx] != 'G' && map[l][arrowy][cx] != 'F' && map[l][arrowy][cx] != 'U' && map[l][arrowy][cx] != 'S'&&map[l][arrowy][cx]!='B'&&map[l][arrowy][cx]!='$') {
                            arrowy++;
                            refresh();napms(20);
                            mvprintw(arrowy,cx,"v");if(arrowy-1!=cy){mvprintw(arrowy-1,cx,".");}
                            dagger_limit++;
                        }
                        if (gun_stack[1] > 10) {
                            gun_stack[1] -= 10;
                        }
                        if (map[l][arrowy][cx] == 'D' || map[l][arrowy][cx] == 'F' || map[l][arrowy][cx] == 'G' || map[l][arrowy][cx] == 'S' || map[l][arrowy][cx] == 'U'|| map[l][arrowy][cx]=='$') {
                            if(damage_boost){mvprintw(0,24,"+ 12         "); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][arrowy][cx] -= 12;
                            if( map[l][arrowy][cx]=='$'){damage_to_boss+=12;}}
                            mvprintw(0, 0, "NAILED IT! ->12 DAMAGE                                     ");
                            dagger_limit = 0;
                            check_dead(arrowy, cx);
                        } else {
                            dagger_limit = 0;
                            map[l][arrowy][cx] = 'd';
                        }
                        attroff(COLOR_PAIR(220));
                    }



                    else if(direction==KEY_UP&&picked_gun==3){
                        attron(COLOR_PAIR(16));
                        arrowy=cy;
                        while (map[l][arrowy-1][cx] != '_' &&map[l][arrowy-1][cx] != '|' && map[l][arrowy-1][cx] != '='  && map[l][arrowy-1][cx] != '*'&&map[l][arrowy-1][cx] != '0'&&map[l][arrowy-1][cx] != 'O'&&wound_limit<10&&map[l][arrowy][cx]!='D'&&map[l][arrowy][cx]!='G'&&map[l][arrowy][cx]!='F'&&map[l][arrowy][cx]!='U'&&map[l][arrowy][cx]!='S'&&map[l][arrowy][cx]!='B'&&map[l][arrowy][cx]!='$')
                        {arrowy--;refresh();napms(10);mvprintw(arrowy,cx,"^");if(arrowy+1!=cy){mvprintw(arrowy+1,cx,".");};wound_limit++;}if(gun_stack[2]>10){gun_stack[2]-=10;}else{}if(map[l][arrowy][cx]=='D'||map[l][arrowy][cx]=='F'||map[l][arrowy][cx]=='G'||map[l][arrowy][cx]=='S'||map[l][arrowy][cx]=='U'||map[l][arrowy][cx]=='B'||map[l][arrowy][cx]=='$'){if(damage_boost){mvprintw(0,24,"+ 15         "); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][arrowy][cx] -= 15;if( map[l][arrowy][cx]=='$'){damage_to_boss+=5;}};movable[l][arrowy][cx]=-1;mvprintw(0,0,"NAILED IT! ->15 DAMAGE                                     ");wound_limit=0;check_dead(arrowy,cx);break;}else{wound_limit=0;map[l][arrowy][cx]='w';break;}
                    attroff(COLOR_PAIR(16));}
                    else if (direction == KEY_LEFT && picked_gun == 3) {
                        attron(COLOR_PAIR(16));
                        arrowx = cx;
                        while (map[l][cy][arrowx-1] != '_' && map[l][cy][arrowx-1] != '|' && map[l][cy][arrowx-1] != '=' && map[l][cy][arrowx-1] != '*' && map[l][cy][arrowx-1] != '0' && map[l][cy][arrowx-1] != 'O' && wound_limit < 10 && map[l][cy][arrowx] != 'D' && map[l][cy][arrowx] != 'G' && map[l][cy][arrowx] != 'F' && map[l][cy][arrowx] != 'U' && map[l][cy][arrowx] != 'S'&&map[l][cy][arrowx]!='B'&&map[l][cy][arrowx]!='$') {
                        arrowx--; refresh();napms(10);mvprintw(cy,arrowx,"<");if(arrowx+1!=cx){mvprintw(cy,arrowx+1,".");}
                            
                            wound_limit++;
                        }
                        if (gun_stack[2] > 10) { 
                            gun_stack[2] -= 10; 
                        }
                        if (map[l][cy][arrowx] == 'D' || map[l][cy][arrowx] == 'F' || map[l][cy][arrowx] == 'G' || map[l][cy][arrowx] == 'S' || map[l][cy][arrowx] == 'U'||map[l][cy][arrowx]=='B'||map[l][cy][arrowx]=='$') {
                            if(damage_boost){mvprintw(0,24,"+ 15             "); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][cy][arrowx] -= 15; if( map[l][cy][arrowx]=='$'){damage_to_boss+=5;}}
                            movable[l][cy][arrowx]=-1;
                            mvprintw(0, 0, "NAILED IT! ->15 DAMAGE                                     ");
                            wound_limit = 0;
                            check_dead(cy, arrowx);
                        } else {
                            wound_limit = 0;
                            map[l][cy][arrowx] = 'w';
                        }attroff(COLOR_PAIR(16));
                    }
                    else if (direction == KEY_RIGHT && picked_gun == 3) {
                        attron(COLOR_PAIR(16));
                        arrowx = cx;
                        while (map[l][cy][arrowx+1] != '_' && map[l][cy][arrowx+1] != '|' && map[l][cy][arrowx+1] != '=' && map[l][cy][arrowx+1] != '*' && map[l][cy][arrowx+1] != '0' && map[l][cy][arrowx+1] != 'O' && wound_limit < 10 && map[l][cy][arrowx] != 'D' && map[l][cy][arrowx] != 'G' && map[l][cy][arrowx] != 'F' && map[l][cy][arrowx] != 'U' && map[l][cy][arrowx] != 'S'&&map[l][cy][arrowx]!='B'&&map[l][cy][arrowx]!='$') {
                            arrowx++;
                            refresh();napms(10);mvprintw(cy,arrowx,">");if(arrowx-1!=cx){mvprintw(cy,arrowx-1,".");}
                            wound_limit++;
                        }
                        if (gun_stack[2] > 10) {
                            gun_stack[2] -= 10;
                        }
                        if (map[l][cy][arrowx] == 'D' || map[l][cy][arrowx] == 'F' || map[l][cy][arrowx] == 'G' || map[l][cy][arrowx] == 'S' || map[l][cy][arrowx] == 'U'||map[l][cy][arrowx]=='B'||map[l][cy][arrowx]=='$') {
                            if(damage_boost){mvprintw(0,24,"+ 15         "); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][cy][arrowx] -= 15; if( map[l][cy][arrowx]=='$'){damage_to_boss+=5;}}
                            movable[l][cy][arrowx]=-1;
                            mvprintw(0, 0, "NAILED IT! ->15 DAMAGE                                     ");
                            wound_limit = 0;
                            check_dead(cy, arrowx);
                        } else {
                            wound_limit = 0;
                            map[l][cy][arrowx] = 'w';
                        }
                        attroff(COLOR_PAIR(16));
                    }
                    else if (direction == KEY_DOWN && picked_gun == 3) {
                        attron(COLOR_PAIR(16));
                        arrowy = cy;
                        while (map[l][arrowy+1][cx] != '_' && map[l][arrowy+1][cx] != '|' && map[l][arrowy+1][cx] != '=' && map[l][arrowy+1][cx] != '*' && map[l][arrowy+1][cx] != '0' && map[l][arrowy+1][cx] != 'O' && wound_limit < 10 && map[l][arrowy][cx] != 'D' && map[l][arrowy][cx] != 'G' && map[l][arrowy][cx] != 'F' && map[l][arrowy][cx] != 'U' && map[l][arrowy][cx] != 'S'&&map[l][arrowy][cx]!='B'&&map[l][arrowy][cx]!='$') {
                            arrowy++;
                            refresh();napms(10);mvprintw(arrowy,cx,"v");if(arrowy-1!=cy){mvprintw(arrowy-1,cx,".");}
                            wound_limit++;
                        }
                        if (gun_stack[2] > 10) {
                            gun_stack[2] -= 10;
                        }
                        if (map[l][arrowy][cx] == 'D' || map[l][arrowy][cx] == 'F' || map[l][arrowy][cx] == 'G' || map[l][arrowy][cx] == 'S' || map[l][arrowy][cx] == 'U'||map[l][arrowy][cx]=='B'||map[l][arrowy][cx]=='$') {
                            if(damage_boost){mvprintw(0,24,"+ 15         "); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][arrowy][cx] -= 15;if( map[l][arrowy][cx]=='$'){damage_to_boss+=5;}}
                            movable[l][arrowy][cx]=-1;
                            mvprintw(0, 0, "NAILED IT! ->15 DAMAGE                                     ");
                            wound_limit = 0;
                            check_dead(arrowy, cx);
                        } else {
                            wound_limit = 0;
                            map[l][arrowy][cx] = 'w';
                        }
                    }
                    else if(direction==KEY_UP&&picked_gun==4){
                        attron(COLOR_PAIR(108));
                        arrowy=cy;
                        while (map[l][arrowy-1][cx] != '_' &&map[l][arrowy-1][cx] != '|' && map[l][arrowy-1][cx] != '='  && map[l][arrowy-1][cx] != '*'&&map[l][arrowy-1][cx] != '0'&&map[l][arrowy-1][cx] != 'O'&&arrow_limit<5&&map[l][arrowy][cx]!='D'&&map[l][arrowy][cx]!='G'&&map[l][arrowy][cx]!='F'&&map[l][arrowy][cx]!='U'&&map[l][arrowy][cx]!='S'&&map[l][arrowy][cx]!='B'&&map[l][arrowy][cx]!='$')
                        {arrowy--;refresh();napms(20);mvprintw(arrowy,cx,"^");if(arrowy+1!=cy){mvprintw(arrowy+1,cx,".");};arrow_limit++;}if(gun_stack[3]>10){gun_stack[3]-=10;}else{}if(map[l][arrowy][cx]=='D'||map[l][arrowy][cx]=='F'||map[l][arrowy][cx]=='G'||map[l][arrowy][cx]=='S'||map[l][arrowy][cx]=='U'||map[l][arrowy][cx]=='B'||map[l][arrowy][cx]=='$'){if(damage_boost){mvprintw(0,24,"+ 5         "); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][arrowy][cx] -= 5;if( map[l][arrowy][cx]=='$'){damage_to_boss+=5;}};mvprintw(0,0,"NAILED IT! ->5 DAMAGE                                     ");arrow_limit=0;check_dead(arrowy,cx);break;}else{arrow_limit=0;map[l][arrowy][cx]='a';break;}
                    attroff(COLOR_PAIR(108));
                    }
                    else if (direction == KEY_LEFT && picked_gun == 4) {
                        attron(COLOR_PAIR(108));
                        arrowx = cx;
                        while (map[l][cy][arrowx-1] != '_' && map[l][cy][arrowx-1] != '|' && map[l][cy][arrowx-1] != '=' && map[l][cy][arrowx-1] != '*' && map[l][cy][arrowx-1] != '0' && map[l][cy][arrowx-1] != 'O' && arrow_limit < 5 && map[l][cy][arrowx] != 'D' && map[l][cy][arrowx] != 'G' && map[l][cy][arrowx] != 'F' && map[l][cy][arrowx] != 'U' && map[l][cy][arrowx] != 'S'&&map[l][cy][arrowx]!='B'&&map[l][cy][arrowx]!='$') {
                            arrowx--; 
                            refresh();napms(20);mvprintw(cy,arrowx,"<");if(arrowx+1!=cx){mvprintw(cy,arrowx+1,".");}
                            arrow_limit++;
                        }
                        if (gun_stack[3] > 10) { 
                            gun_stack[3] -= 10; 
                        }
                        if (map[l][cy][arrowx] == 'D' || map[l][cy][arrowx] == 'F' || map[l][cy][arrowx] == 'G' || map[l][cy][arrowx] == 'S' || map[l][cy][arrowx] == 'U'||map[l][cy][arrowx]=='B'||map[l][cy][arrowx]=='$') {
                            if(damage_boost){mvprintw(0,24,"+ 5         "); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][cy][arrowx] -= 5; if( map[l][cy][arrowx]=='$'){damage_to_boss+=5;}}
                            mvprintw(0, 0, "NAILED IT! ->5 DAMAGE                                     ");
                            arrow_limit = 0;
                            check_dead(cy, arrowx);
                        } else {
                            arrow_limit = 0;
                            map[l][cy][arrowx] = 'a';
                        }
                        attroff(COLOR_PAIR(108));
                    }
                    else if (direction == KEY_RIGHT && picked_gun == 4) {
                        attron(COLOR_PAIR(108));
                        arrowx = cx;
                        while (map[l][cy][arrowx+1] != '_' && map[l][cy][arrowx+1] != '|' && map[l][cy][arrowx+1] != '=' && map[l][cy][arrowx+1] != '*' && map[l][cy][arrowx+1] != '0' && map[l][cy][arrowx+1] != 'O' && arrow_limit < 5 && map[l][cy][arrowx] != 'D' && map[l][cy][arrowx] != 'G' && map[l][cy][arrowx] != 'F' && map[l][cy][arrowx] != 'U' && map[l][cy][arrowx] != 'S'&&map[l][cy][arrowx]!='B'&&map[l][cy][arrowx]!='$') {
                            arrowx++;refresh();napms(20);mvprintw(cy,arrowx,">");if(arrowx-1!=cx){mvprintw(cy,arrowx-1,".");}
                            arrow_limit++;
                        }
                        if (gun_stack[3] > 10) {
                            gun_stack[3] -= 10;
                        }
                        if (map[l][cy][arrowx] == 'D' || map[l][cy][arrowx] == 'F' || map[l][cy][arrowx] == 'G' || map[l][cy][arrowx] == 'S' || map[l][cy][arrowx] == 'U'||map[l][cy][arrowx]=='B'||map[l][cy][arrowx]=='$') {
                            if(damage_boost){mvprintw(0,24,"+ 5         "); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][cy][arrowx] -= 5; if( map[l][cy][arrowx]=='$'){damage_to_boss+=5;}}
                            mvprintw(0, 0, "NAILED IT! ->5 DAMAGE                                     ");
                            arrow_limit = 0;
                            check_dead(cy, arrowx);
                        } else {
                            arrow_limit = 0;
                            map[l][cy][arrowx] = 'a';
                        }
                        attroff(COLOR_PAIR(108));
                    }
                    else if (direction == KEY_DOWN && picked_gun == 4) {
                        attron(COLOR_PAIR(108));
                        arrowy = cy;
                        while (map[l][arrowy+1][cx] != '_' && map[l][arrowy+1][cx] != '|' && map[l][arrowy+1][cx] != '=' && map[l][arrowy+1][cx] != '*' && map[l][arrowy+1][cx] != '0' && map[l][arrowy+1][cx] != 'O' && arrow_limit < 5 && map[l][arrowy][cx] != 'D' && map[l][arrowy][cx] != 'G' && map[l][arrowy][cx] != 'F' && map[l][arrowy][cx] != 'U' && map[l][arrowy][cx] != 'S'&&map[l][arrowy][cx]!='B'&&map[l][arrowy][cx]!='$') {
                            arrowy++;refresh();napms(20);mvprintw(arrowy,cx,"v");if(arrowy-1!=cy){mvprintw(arrowy-1,cx,".");}
                            arrow_limit++;
                        }
                        if (gun_stack[3] > 10) {
                            gun_stack[3] -= 10;
                        }
                        if (map[l][arrowy][cx] == 'D' || map[l][arrowy][cx] == 'F' || map[l][arrowy][cx] == 'G' || map[l][arrowy][cx] == 'S' || map[l][arrowy][cx] == 'U'||map[l][arrowy][cx]=='B'||map[l][arrowy][cx]=='$') {
                            if(damage_boost){mvprintw(0,24,"+ 5         "); repeat=2;}else{ repeat=1;}
                            for(int rr=repeat;rr>0;rr--){
                            enemy_health[l][arrowy][cx] -= 5;if(map[l][arrowy][cx]=='$'){damage_to_boss+=5;}}
                            mvprintw(0, 0, "NAILED IT! ->5 DAMAGE                                     ");
                            arrow_limit = 0;
                            check_dead(arrowy, cx);
                        } else {
                            arrow_limit = 0;
                            map[l][arrowy][cx] = 'a';
                        }
                        attron(COLOR_PAIR(108));
                    }

                    
                    
                    }
                    dagger_limit=0;
                    break;  
                case KEY_LEFT:
                    repeat;
                    if(speed_boost){ repeat=2;}else{ repeat=1;}
                    for(int rr=repeat;rr>0;rr--){
                    if (map[l][cy][cx - 1] == '=')
                    {
                        window_reveal(4, cy, cx);
                        break;
                    }
                    else if (map[l][cy][cx - 1] == '*' && done == 0)
                    {
                        save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                        clear();
                        refresh();
                        display_lock();
                        save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                        clear();
                        refresh();
                        int *tcy;
                        int *tcx;
                        int *tl;
                        load_game_state(user, map, revealed, health_bar, food_stack, hunger_bar, tcx, tcy, tl, levels, themed);
                        for (int i = 0; i < 50; i++)
                        {
                            for (int j = 0; j < 150; j++)
                            {
                                if (themed[l][i][j] == 5)
                                {
                                    mvprintw(i, j, " ");
                                }
                            }
                        }
                        break;
                    }
                    if ((unlocked == 1 || map[l][cy][cx - 1] != '*') && map[l][cy][cx - 1] != '_' && map[l][cy][cx - 1] != '|' && map[l][cy][cx - 1] != '0' && map[l][cy][cx - 1] != 'O'&&map[l][cy][cx - 1] != 'U'&&map[l][cy][cx - 1] != 'F'&&map[l][cy][cx - 1] != 'S'&&map[l][cy][cx - 1] != 'G'&&map[l][cy][cx - 1] != 'D' || map[l][cy][cx] == '<')
                    {
                        // if(map[l][cy][cx - 1] == 'U'||map[l][cy][cx - 1] == 'F'||map[l][cy][cx - 1] == 'S'||map[l][cy][cx - 1] == 'G'||map[l][cy][cx - 1] == 'D'){
                        //     fight(cx,cy);
                        // }

                         if (map[l][cy][cx - 1] == 't')
                        {
                            for (int h = 9; h > -1; h--)
                            {
                                if (health_bar[h] == 1)
                                {
                                    health_bar[h] = 0;
                                    break;
                                }
                            }
                            map[l][cy][cx - 1] = '^';
                        }
                        else if (map[l][cy][cx - 1] == 'P')
                        {
                            trap_m = 3;
                            for (int h = 9; h > -1; h--)
                            {
                                if (health_bar[h] == 1)
                                {
                                    health_bar[h] = 0;
                                    break;
                                }
                            }
                            map[l][cy][cx - 1] = 'V';
                        }
                        else if (map[l][cy][cx - 1] == '-' || map[l][cy][cx - 1] == '~')
                        {
                            map[l][cy][cx - 1] = '?';
                        }
                        else if (map[l][cy][cx - 1] == 'f')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy][cx - 1] != 5)
                                {
                                    food_stack[f] = 1;
                                    map[l][cy][cx - 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy][cx - 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy][cx - 2] == 'f')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy][cx - 2] != 5)
                                {
                                    food_stack[f] = 1;
                                    map[l][cy][cx - 1] = '.';
                                    map[l][cy][cx - 2] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy][cx - 1] = '.';
                                    map[l][cy][cx - 2] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy][cx - 1] == 'g')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy][cx - 1] != 5)
                                {
                                    food_stack[f] = 2;
                                    map[l][cy][cx - 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy][cx - 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy][cx - 2] == 'g')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy][cx - 2] != 5)
                                {
                                    food_stack[f] = 2;
                                    map[l][cy][cx - 1] = '.';
                                    map[l][cy][cx - 2] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy][cx - 1] = '.';
                                    map[l][cy][cx - 2] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy][cx - 1] == 'h')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy][cx - 1] != 5)
                                {
                                    food_stack[f] = 3;
                                    map[l][cy][cx - 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy][cx - 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy][cx - 2] == 'h')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy][cx - 2] != 5)
                                {
                                    food_stack[f] = 3;
                                    map[l][cy][cx - 1] = '.';
                                    map[l][cy][cx - 2] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy][cx - 1] = '.';
                                    map[l][cy][cx - 2] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy][cx - 1] == 'j')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy][cx - 1] != 5)
                                {
                                    food_stack[f] = 4;
                                    map[l][cy][cx - 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy][cx - 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy][cx - 2] == 'j')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy][cx - 2] != 5)
                                {
                                    food_stack[f] = 4;
                                    map[l][cy][cx - 1] = '.';
                                    map[l][cy][cx - 2] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy][cx - 1] = '.';
                                    map[l][cy][cx - 2] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy][cx - 1] == 'k')
                        {
                            if (themed[l][cy][cx - 1] == 5)
                            {
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                akey++;
                                mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                                map[l][cy][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 1] == 'C')
                        {
                            if (themed[l][cy][cx - 1] == 5)
                            {
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                coin += rand() % 50 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 1] == 'c')
                        {
                            if (themed[l][cy][cx - 1] == 5)
                            {
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                coin += rand() % 5 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 1] == '1')
                        {
                            if (themed[l][cy][cx - 1] == 5)
                            {
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                                map[l][cy][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 1] == '2')
                        {
                            if (themed[l][cy][cx - 1] == 5)
                            {
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                                map[l][cy][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 1] == '3')
                        {
                            if (themed[l][cy][cx - 1] == 5)
                            {
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                                map[l][cy][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 1] == '4')
                        {
                            if (themed[l][cy][cx - 1] == 5)
                            {
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                                map[l][cy][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 1] == '5')
                        {
                            if (themed[l][cy][cx - 1] == 5)
                            {
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                                map[l][cy][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 1] == '6')
                        {
                            if (themed[l][cy][cx - 1] == 5)
                            {
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                                map[l][cy][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 1] == '7')
                        {
                            if (themed[l][cy][cx - 1] == 5)
                            {
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                                map[l][cy][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 1] == '8')
                        {
                            if (themed[l][cy][cx - 1] == 5)
                            {
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                                map[l][cy][cx - 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 2] == '1')
                        {
                            if (themed[l][cy][cx - 2] == 5)
                            {
                                map[l][cy][cx - 2] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                                map[l][cy][cx - 2] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 2] == '2')
                        {
                            if (themed[l][cy][cx - 2] == 5)
                            {
                                map[l][cy][cx - 2] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                                map[l][cy][cx - 2] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 2] == '3')
                        {
                            if (themed[l][cy][cx - 2] == 5)
                            {
                                map[l][cy][cx - 2] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                                map[l][cy][cx - 2] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 2] == '4')
                        {
                            if (themed[l][cy][cx - 2] == 5)
                            {
                                map[l][cy][cx - 2] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                                map[l][cy][cx - 2] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 2] == '5')
                        {
                            if (themed[l][cy][cx - 2] == 5)
                            {
                                map[l][cy][cx - 2] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                                map[l][cy][cx - 2] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 2] == '6')
                        {
                            if (themed[l][cy][cx - 2] == 5)
                            {
                                map[l][cy][cx - 2] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                                map[l][cy][cx - 2] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 2] == '7')
                        {
                            if (themed[l][cy][cx - 2] == 5)
                            {
                                map[l][cy][cx - 2] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                                map[l][cy][cx - 2] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 2] == '8')
                        {
                            if (themed[l][cy][cx - 2] == 5)
                            {
                                map[l][cy][cx - 2] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                                map[l][cy][cx - 2] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 2] == 'k')
                        {
                            if (themed[l][cy][cx - 2] == 5)
                            {
                                map[l][cy][cx - 2] = '.';
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                akey++;
                                mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                          ");
                                map[l][cy][cx - 1] = '.';
                                map[l][cy][cx - 2] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 2] == 'C')
                        {
                            if (themed[l][cy][cx - 2] == 5)
                            {
                                map[l][cy][cx - 2] = '.';
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                coin += rand() % 50 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy][cx - 1] = '.';
                                map[l][cy][cx - 2] = '.';
                            }
                        }
                        else if (map[l][cy][cx - 2] == 'c')
                        {
                            if (themed[l][cy][cx - 2] == 5)
                            {
                                map[l][cy][cx - 2] = '.';
                                map[l][cy][cx - 1] = '.';
                            }
                            else
                            {
                                coin += rand() % 5 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy][cx - 1] = '.';
                                map[l][cy][cx - 2] = '.';
                            }
                        }
                        if (map[l][cy][cx] == '<' && l > 0)
                        {
                            clear();
                            attroff(COLOR_PAIR(16));
                            attroff(COLOR_PAIR(203));
                            attroff(COLOR_PAIR(220));
                            attroff(COLOR_PAIR(221));
                            attroff(COLOR_PAIR(49));
                            attroff(COLOR_PAIR(48));
                            attroff(COLOR_PAIR(89));
                            attroff(COLOR_PAIR(88));
                            attroff(COLOR_PAIR(247));
                            attroff(COLOR_PAIR(246));
                            attroff(COLOR_PAIR(202));
                            attroff(COLOR_PAIR(15));
                            levels[l] = 1;
                            l--;
                            levels[l] = 1;
                            for (int i = 0; i < 50; i++)
                            {
                                for (int j = 0; j < 150; j++)
                                {
                                    if (map[l][i][j] == '>')
                                    {
                                        cy = i;
                                        cx = j;
                                        break;
                                    }
                                }
                            }
                            k = 0;
                            secret = 0;
                            m = 0;
                            forbidden = 0;
                            placed = 0, done = 0;
                            error = 0;
                            unlocked = 0;
                             
                            save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                            play_game(levels[l]);
                        }
                        if (map[l][cy][cx - 1] == 'f'||map[l][cy][cx - 1] == 'g'||map[l][cy][cx - 1] == 'h'||map[l][cy][cx - 1] == 'j')
                        {
                            mvprintw(cy, cx - 1, "@");
                            move(cy, cx - 1);
                            cx -= 1;
                        }
                        else
                        {
                            mvprintw(cy, cx - 1, "@");
                            mvprintw(cy, cx, "%c", map[l][cy][cx]);
                            move(cy, cx - 1);
                            cx -= 1;
                        }
                    }
                    }
                    break;
                case 'M':
                case 'm':
                     
                    save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                    int *tcyy;
                    int *tcxx;
                    int *tll;
                    clear();
                    int tempcy, tempcx;
                    for (int i = 0; i < 50; i++)
                    {
                        for (int j = 0; j < 150; j++)
                        {
                            if (map[l][i][j] == '.' && revealed[l][i][j] == 1 && themed[l][i][j] != 5)
                            {
                                tempcy = i;
                                tempcx = j;
                                break;
                            }
                        }
                    }
                    load_game_state(user, map, revealed, health_bar, food_stack, hunger_bar, tcxx, tcyy, tll, levels, themed);
                    reveal_map(map, tempcy, tempcx);
                    show_map();
                    int buttonmap;
                    if (firsttime == 1)
                    {
                        firsttime = 0;
                        buttonmap = 'm';
                    }
                    else
                    {
                        buttonmap = getch();
                    }
                    while (buttonmap != 'm' && buttonmap != 'M')
                    {
                        buttonmap = getch();
                    }
                    clear();
                    load_game_state(user, map, revealed, health_bar, food_stack, hunger_bar, tcxx, tcyy, tll, levels, themed);
                    for (int i = 0; i < 50; i++)
                    {
                        for (int j = 0; j < 150; j++)
                        {
                            if (themed[l][i][j] == 5)
                            {
                                mvprintw(i, j, " ");
                            }
                        }
                    }
                    break;
                case 'o':
                case 'O':
                      
                    save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                    clear();
                    refresh();
                    display_potion_menu(potions, potion_stack);
                    save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                    int *tccy;
                    int *tccx;
                    int *tcl;
                    clear();
                    
                    load_game_state(user, map, revealed, health_bar, food_stack, hunger_bar, tccx, tccy, tcl, levels, themed);
                    for (int i = 0; i < 50; i++)
                    {
                        for (int j = 0; j < 150; j++)
                        {
                            if (themed[l][i][j] == 5)
                            {
                                mvprintw(i, j, " ");
                            }
                        }
                    }
                    break;
                case 'W':
                case 'w':
                   picked_gun=0;
                   mvprintw(0,0,"STACKED GUN IN BACKPACK                           ");
                   break;
                case 'i':
                case 'I':
                     
                    save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                    clear();
                    refresh();
                    display_gun_menu(guns, gun_stack);
                    save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                    int *tcy;
                    int *tcx;
                    int *tl;
                    clear();
                    load_game_state(user, map, revealed, health_bar, food_stack, hunger_bar, tcx, tcy, tl, levels, themed);
                    for (int i = 0; i < 50; i++)
                    {
                        for (int j = 0; j < 150; j++)
                        {
                            if (themed[l][i][j] == 5)
                            {
                                mvprintw(i, j, " ");
                            }
                        }
                    }
                    break;
                case 'e':
                case 'E':
                     
                    save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                    clear();
                    refresh();
                    display_hunger_menu(foods, hunger_bar, food_stack, health_bar);
                    save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                    // int *tcy;
                    // int *tcx;
                    // int *tl;
                    clear();
                    load_game_state(user, map, revealed, health_bar, food_stack, hunger_bar, tcx, tcy, tl, levels, themed);
                    for (int i = 0; i < 50; i++)
                    {
                        for (int j = 0; j < 150; j++)
                        {
                            if (themed[l][i][j] == 5)
                            {
                                mvprintw(i, j, " ");
                            }
                        }
                    }
                    break;
                case 'U':
                case 'u':
                    unlocked = 1;
                    done = 1;
                    break;
                case KEY_RIGHT:
                    repeat;
                    if(speed_boost){ repeat=2;}else{ repeat=1;}
                    for(int rr=repeat;rr>0;rr--){
                    if (map[l][cy][cx + 1] == '=')
                    {
                        window_reveal(3, cy, cx);
                        break;
                    }
                    else if (map[l][cy][cx] == '*' && done == 0)
                    {
                        save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                        clear();
                        refresh();
                        display_lock();
                        save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                        clear();
                        refresh();
                        load_game_state(user, map, revealed, health_bar, food_stack, hunger_bar, tcx, tcy, tl, levels, themed);
                        for (int i = 0; i < 50; i++)
                        {
                            for (int j = 0; j < 150; j++)
                            {
                                if (themed[l][i][j] == 5)
                                {
                                    mvprintw(i, j, " ");
                                }
                            }
                        }
                        break;
                    }
                    if ((unlocked == 1 || map[l][cy][cx + 1] != '*') && map[l][cy][cx + 1] != '_' && map[l][cy][cx + 1] != '|' && map[l][cy][cx + 1] != '0' && map[l][cy][cx + 1] != 'O'&&map[l][cy][cx + 1] != 'U'&&map[l][cy][cx + 1] != 'F'&&map[l][cy][cx + 1] != 'S'&&map[l][cy][cx + 1] != 'G'&&map[l][cy][cx + 1] != 'D'
 || map[l][cy][cx] == '>')
                    {
                        if (map[l][cy][cx + 1] == 't')
                        {
                            for (int h = 9; h > -1; h--)
                            {
                                if (health_bar[h] == 1)
                                {
                                    health_bar[h] = 0;
                                    break;
                                }
                            }
                            map[l][cy][cx + 1] = '^';
                        }
                        else if (map[l][cy][cx + 1] == 'P')
                        {
                            trap_m = 3;
                            for (int h = 9; h > -1; h--)
                            {
                                if (health_bar[h] == 1)
                                {
                                    health_bar[h] = 0;
                                    break;
                                }
                            }
                            map[l][cy][cx + 1] = 'V';
                        }
                        else if (map[l][cy][cx + 1] == '-' || map[l][cy][cx + 1] == '~')
                        {
                            map[l][cy][cx + 1] = '?';
                        }
                        else if (map[l][cy][cx + 1] == 'f')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy][cx + 1] != 5)
                                {
                                    food_stack[f] = 1;
                                    map[l][cy][cx + 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy][cx + 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy][cx + 1] == 'g')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy][cx + 1] != 5)
                                {
                                    food_stack[f] = 2;
                                    map[l][cy][cx + 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy][cx + 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy][cx + 1] == 'h')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy][cx + 1] != 5)
                                {
                                    food_stack[f] = 3;
                                    map[l][cy][cx + 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy][cx + 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy][cx + 1] == 'j')
                        {
                            for (int f = 0; f < 5; f++)
                            {
                                if (food_stack[f] == 0 && themed[l][cy][cx + 1] != 5)
                                {
                                    food_stack[f] = 4;
                                    map[l][cy][cx + 1] = '.';
                                    break;
                                }
                                else if (food_stack[f] == 0)
                                {
                                    map[l][cy][cx + 1] = '.';
                                    break;
                                }
                            }
                        }
                        else if (map[l][cy][cx + 1] == 'k')
                        {
                            if (themed[l][cy][cx + 1] == 5)
                            {
                                map[l][cy][cx + 1] = '.';
                            }
                            else
                            {
                                akey++;
                                mvprintw(0, 0, "YOU FOUND ANCIENT KEY!                                        ");
                                map[l][cy][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx + 1] == 'C')
                        {
                            if (themed[l][cy][cx + 1] == 5)
                            {
                                map[l][cy][cx + 1] = '.';
                            }
                            else
                            {
                                coin += rand() % 50 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx + 1] == 'c')
                        {
                            if (themed[l][cy][cx + 1] == 5)
                            {
                                map[l][cy][cx + 1] = '.';
                            }
                            else
                            {
                                coin += rand() % 5 + 1;
                                mvprintw(0, 0, "YOU FOUND %d GOLD                                             ", coin);
                                map[l][cy][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx + 1] == '1')
                        {
                            if (themed[l][cy][cx + 1] == 5)
                            {
                                map[l][cy][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MACE                                     ");equipt(1);
                                map[l][cy][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx + 1] == '2')
                        {
                            if (themed[l][cy][cx + 1] == 5)
                            {
                                map[l][cy][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAGGER                                     ");equipt(2);
                                map[l][cy][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx + 1] == '3')
                        {
                            if (themed[l][cy][cx + 1] == 5)
                            {
                                map[l][cy][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND MAGIC WANR                                     ");equipt(3);
                                map[l][cy][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx + 1] == '4')
                        {
                            if (themed[l][cy][cx + 1] == 5)
                            {
                                map[l][cy][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND NORMAL ARROW                                        ");equipt(4);
                                map[l][cy][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx + 1] == '5')
                        {
                            if (themed[l][cy][cx + 1] == 5)
                            {
                                map[l][cy][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SWORR                                     ");equipt(5);
                                map[l][cy][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx + 1] == '6')
                        {
                            if (themed[l][cy][cx + 1] == 5)
                            {
                                map[l][cy][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND HEALTH SPELL                                           ");equipt(6);
                                map[l][cy][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx + 1] == '7')
                        {
                            if (themed[l][cy][cx + 1] == 5)
                            {
                                map[l][cy][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND SPEED SPELL                                           ");equipt(7);
                                map[l][cy][cx + 1] = '.';
                            }
                        }
                        else if (map[l][cy][cx + 1] == '8')
                        {
                            if (themed[l][cy][cx + 1] == 5)
                            {
                                map[l][cy][cx + 1] = '.';
                            }
                            else
                            {
                                mvprintw(0, 0, "YOU FOUND DAMAGE SPELL                                           ");equipt(8);
                                map[l][cy][cx + 1] = '.';
                            }
                        }

                        if (map[l][cy][cx] == '>')
                        {
                            clear();
                            attroff(COLOR_PAIR(16));
                            attroff(COLOR_PAIR(203));
                            attroff(COLOR_PAIR(49));
                            attroff(COLOR_PAIR(48));
                            attroff(COLOR_PAIR(89));
                            attroff(COLOR_PAIR(88));
                            attroff(COLOR_PAIR(247));
                            attroff(COLOR_PAIR(246));
                            attroff(COLOR_PAIR(202));
                            attroff(COLOR_PAIR(15));
                            levels[l] = 1;
                            // levels[l+1]=1;
                            l++;
                            for (int i = 0; i < 50; i++)
                            {
                                for (int j = 0; j < 150; j++)
                                {
                                    if (map[l][i][j] == '<')
                                    {
                                        cy = i;
                                        cx = j;
                                        break;
                                    }
                                }
                            }
                             
                            save_game_state(user, map, revealed, revealed_path, centers, health_bar, food_stack, hunger_bar, cx, cy, l, levels);
                            k = 0;
                            secret = 0;
                            m = 0;
                            forbidden = 0;
                            placed = 0;
                            done = 0;
                            error = 0;
                            unlocked = 0;
                            play_game(levels[l]);
                        }
                        if (map[l][cy][cx - 1] == 'f'||map[l][cy][cx - 1] == 'g'||map[l][cy][cx - 1] == 'h'||map[l][cy][cx - 1] == 'j')
                        {
                            if (map[l][cy][cx + 1] != 'f'&&map[l][cy][cx + 1] != 'g'&&map[l][cy][cx + 1] != 'h'&&map[l][cy][cx + 1] != 'j')
                                mvprintw(cy, cx + 1, "@");
                        }
                        else
                        {
                            mvprintw(cy, cx + 1, "@");
                            mvprintw(cy, cx, "%c", map[l][cy][cx]);
                        }
                        move(cy, cx + 1);
                        cx += 1;
                    }
                    }
                    break;
                case 's':
                case 'S':
                    init_pair(108, 8, COLOR_BLACK);
                    attron(COLOR_PAIR(108));
                    if (map[l][cy][cx] == '&' && gofornext == 1 && buttony != cy && buttonx != cx)
                    {
                        password2 = rand() % 10000;
                        mvprintw(44, 40, "PASSWORD: %d", password2);
                        gofornext = 2;
                        refresh();
                        if (pthread_create(&timer_thread, NULL, timer_function, NULL))
                        {
                            fprintf(stderr, "Error creating thread\n");
                            endwin();
                            return;
                        }
                        pthread_detach(timer_thread);
                    }
                    else if (map[l][cy][cx] == '&' && gofornext == 0)
                    {
                        buttony = cy;
                        buttonx = cx;
                        password = rand() % 10000;
                        mvprintw(42, 40, "PASSWORD: %d", password);
                        refresh();
                        if (pthread_create(&timer_thread, NULL, timer_function, NULL))
                        {
                            fprintf(stderr, "Error creating thread\n");
                            endwin();
                            return;
                        }
                        pthread_detach(timer_thread);
                    }
                    attroff(COLOR_PAIR(108));
                    break;
                }
                m++;
                if (m == 8)
                {
                    for (int h = 59; h > -1; h--)
                    {
                        if (hunger_bar[h] == 1)
                        {
                            hunger_bar[h] = 0;
                            m = 0;
                            break;
                        }
                    }
                    if (hunger_bar[0] == 0 && m == 8)
                    {
                        for (int h = 9; h > -1; h--)
                        {
                            if (health_bar[h] == 1)
                            {
                                health_bar[h] = 0;
                                m = 0;
                                break;
                            }
                        }
                    }
                }
                if (poison_m > 12 && poison_m % 3 == 1)
                {
                    for (int h = 9; h > -1; h--)
                    {
                        if (health_bar[h] == 1)
                        {
                            health_bar[h] = 0;
                            break;
                        }
                    }
                }
                if (trap_m > 0 && m == 7)
                {
                    trap_m--;

                    for (int h = 9; h > -1; h--)
                    {
                        if (health_bar[h] == 1)
                        {
                            health_bar[h] = 0;
                            break;
                        }
                    }
                }
                if (health_m > 30 && health_m % 3 == 1)
                {
                    for (int h = 0; h < 10; h++)
                    {
                        if (health_bar[h] == 0)
                        {
                            health_bar[h] = 1;if(heal_boost&&h<9){health_bar[h+1] = 1;}
                            break;
                        }
                    }
                }
                int g = 5;
                int perx = cx, pery = cy;
                for (int i = 0; i < 200; i++)
                {
                    for (int j = 0; j < 200; j++)
                    {
                        revealed_path[j][i] = 0;
                    }
                }
                display_health_bar();
                display_food_stack();
                display_score();
                reveal_path(map, cy, cx, pery, perx);
                refresh();
                reveal_map(map, cy, cx);
                if (map[l][cy][cx] == 'f' || map[l][cy][cx - 1] == 'f'||map[l][cy][cx] == 'g' || map[l][cy][cx - 1] == 'g'||map[l][cy][cx] == 'h' || map[l][cy][cx - 1] == 'h'||map[l][cy][cx] == 'j' || map[l][cy][cx - 1] == 'j')
                {
                }
                else
                {
                    mvprintw(cy, cx, "@");
                }
                move(cy, cx);
                refresh();
            }
        }
        void play_game(int continue_game)
        {
            noecho();
            curs_set(0);
            if (continue_game == 2)
            {
                firsttime = 2;
                int *tcy;
                int *tcx;
                int *tl;
                clear();
                refresh();
                load_game_state(user, map, revealed, health_bar, food_stack, hunger_bar, tcx, tcy, tl, levels, themed);
                for (int i = 0; i < 50; i++)
                {
                    for (int j = 0; j < 150; j++)
                    {
                        if (themed[l][i][j] == 5)
                        {
                            mvprintw(i, j, " ");
                        }
                    }
                }
            for(int l=0;l<5;l++){    
                for (int i = 0; i < 50; i++)
                {
                    for (int j = 0; j < 150; j++)
                    {
                        if (map[l][i][j] == 'D')
                        {
                            enemy_health[l][i][j]=5;
                            movable[l][i][j]=0;
                        }
                        else if (map[l][i][j] == 'F')
                        {
                            enemy_health[l][i][j]=10;
                            movable[l][i][j]=0;
                        }
                        else if (map[l][i][j] == 'S')
                        {
                            enemy_health[l][i][j]=20;
                            movable[l][i][j]=-2;
                        }
                        else if (map[l][i][j] == 'G')
                        {
                            enemy_health[l][i][j]=15;
                            movable[l][i][j]=0;
                        }
                        else if (map[l][i][j] == 'U')
                        {
                            enemy_health[l][i][j]=30;
                            movable[l][i][j]=0;
                        }
                    }
                }
            }
                levels[l] = 1;
                l = lll;
                cy = yy;
                cx = xx;
                score = scoree;

                srand(time(NULL));

                brand = rand() % 3;
                crand = rand() % 6;
                initscr();
                noecho();
                cbreak();
                keypad(stdscr, TRUE);
                srand(time(NULL));
                trand=rand()%3;
            }
            if (continue_game == 0)
            {
                levels[l] = 1;
                for (int i = 0; i < 200; i++)
                {
                    for (int j = 0; j < 200; j++)
                    {
                        map[l][j][i] = '0';
                        revealed[l][j][i] = 0;
                        revealed_path[j][i] = 0;
                        themed[l][j][i] = 0;
                    }
                }
                srand(time(NULL));
                trand=rand()%3;

                for (int ll = 0; ll < 150; ll += 51)
                {
                    for (int w = 0; w < 42; w += 22)
                    {
                        draw_rectangle(ll, w, map, k++);
                    }
                }
                
                for (int i = 0; i < k - 1; i++)
                {
                    if (i < k - 2)
                    {
                        create_junction(centers[i][0], centers[i][1], (centers[i][0] + centers[i + 1][0]) / 2, (centers[i + 1][1] + centers[i + 2][1]) / 2, centers[i + 2][0], centers[i + 2][1]);
                        locked = 0;
                    }
                }
                int lock = rand() % 6 + 1;
                for (int i = 0; i < k - 1; i++)
                {
                    int q = rand() % 2;
                    if (i % 3 == 0 || q != 0)
                    {
                        if ((lock == i) && firstlock == 1)
                        {
                            locked = 1;
                            firstlock = 0;
                        }
                        create_path(centers[i][0], centers[i][1], centers[(i + 1) % k][0], centers[(i + 1) % k][1]);
                        if (i % 3 == 0)
                        {
                            int v = rand() % 4;
                            secret_room(v);
                        }
                    }
                }
            }
            else
            {
                int *tcy;
                int *tcx;
                int *tl;
                clear();
                refresh();
                load_game_state(user, map, revealed, health_bar, food_stack, hunger_bar, tcx, tcy, tl, levels, themed);
                // reveal_map(map,yy,xx);
                for (int i = 0; i < 50; i++)
                {
                    for (int j = 0; j < 150; j++)
                    {
                        if (themed[l][i][j] == 5)
                        {
                            mvprintw(i, j, " ");
                        }
                    }
                }
                mvprintw(40, 140, "%d %d", xx, scoree);
                levels[l] = 1;
                l = lll;
                cy = yy;
                cx = xx;
                score = scoree;
            }
            forbid_continue=0;
            move_hero(cy, cx);
            refresh();
            getch();
            endwin();

            return;
        }
