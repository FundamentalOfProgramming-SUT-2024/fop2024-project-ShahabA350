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

void display_clash_room(){
    clashed=1;
    for(int i=10;i<30;i++){
        for(int j=35;j<135;j++){
            themed[5][i][j]=0;
            if(i==10){
                map[5][i][j]='_';
            }
            else if(j==35||j==134){
                map[5][i][j]='|';
            }
            else if(i==29){
                map[5][i][j]='_';
            }
            else {map[5][i][j]='.';
            }
        }
    }
    map[5][20][65]='S';
    movable[5][20][65]=-2;
    enemy_health[5][20][65]=20;

    map[5][20][105]='S';
    enemy_health[5][20][105]=20;
    movable[5][20][105]=-2;

    map[5][12][85]='S';
    movable[5][12][85]=-2;
    enemy_health[5][12][85]=20;

    map[5][28][85]='S';
    movable[5][28][85]=-2;
    enemy_health[5][28][85]=20;

    map[5][27][76]='D';
    // movable[5][27][76]=0;
    enemy_health[5][27][76]=5;

    map[5][27][94]='G';
    // movable[5][27][94]=0;
    enemy_health[5][27][94]=15;

    map[5][13][76]='G';
    // movable[5][13][76]=0;
    enemy_health[5][13][76]=15;

    map[5][13][94]='D';
    // movable[5][13][94]=0;
    enemy_health[5][13][94]=5;

    map[5][16][102]='U';
    // movable[5][27][76]=0;
    enemy_health[5][16][102]=30;

    map[5][24][102]='F';
    // movable[5][27][94]=0;
    enemy_health[5][24][102]=10;

    map[5][16][68]='F';
    // movable[5][13][76]=0;
    enemy_health[5][16][68]=10;

    map[5][24][68]='U';
    // movable[5][13][94]=0;
    enemy_health[5][24][68]=30;
    srand(time(0));
    for(int i=13;i<28;i+=4){
        if(rand()%2==0){
            map[5][i][50]='h';
           
            if(rand()%3){
                map[5][i][120]='3';
            }
            else{
            map[5][i][120]='4';}
        }
        else{
            map[5][i][50]='j';
            if(rand()%3){
                map[5][i][120]='2';
            }
            else{
            map[5][i][120]='5';}

        }
    }
    for(int i=11;i<29;i++){
        for(int j=37;j<49;j++){
            if (rand() % 170 == 1)
            {
                map[5][i][j] = 'C';
                
            }
            else if(rand() % 93 == 1)
            {
                map[5][i][j] = 'c';
            }
        }
        for(int j=123;j<132;j++){
            if (rand() % 170 == 1)
            {
                map[5][i][j] = 'C';
                
            }
            else if(rand() % 93 == 1)
            {
                map[5][i][j] = 'c';
            }
        }

    } 
    l=5;
    move_hero(20,85);
    play_game(1);
    
}