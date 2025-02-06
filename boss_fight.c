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
#include "boss_fight.h"


void display_boss_fight(){
    // bossdeploy=1;
    for(int i=10;i<30;i++){
        for(int j=35;j<135;j++){
            themed[5][i][j]=6;
            // themed[5][i][j]=0;
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
      map[5][20][65]='$';
    movable[5][20][65]=-2;
    enemy_health[5][20][65]=200;

    map[5][20][105]='$';
    enemy_health[5][20][105]=200;
    movable[5][20][105]=-2;

    map[5][12][85]='$';
    movable[5][12][85]=-2;
    enemy_health[5][12][85]=200;

    map[5][28][85]='$';
    movable[5][28][85]=-2;
    enemy_health[5][28][85]=200;

    map[5][27][76]='$';
    // movable[5][27][76]=0;
    enemy_health[5][27][76]=50;

    map[5][27][94]='$';
    // movable[5][27][94]=0;
    enemy_health[5][27][94]=150;

    map[5][13][76]='$';

    enemy_health[5][13][76]=150;

    map[5][13][94]='$';
  
    enemy_health[5][13][94]=500;

    map[5][16][102]='$';

    enemy_health[5][16][102]=300;

    map[5][24][102]='$';

    enemy_health[5][24][102]=100;

    map[5][16][68]='$';

    enemy_health[5][16][68]=100;

    map[5][24][68]='$';

    enemy_health[5][24][68]=300;
    int i=10;
    int j=25;
    // map[5][i++][j]='#';map[5][i++][j]='#';map[5][i++][j]='#';map[5][i++][j]='#';map[5][i++][j]='#';map[5][i][j++]='#';map[5][i][j++]='#';map[5][i][j++]='#';map[5][i][j++]='#';map[5][i][j++]='#';map[5][i][j++]='#';map[5][i][j++]='#';map[5][i][j++]='#';map[5][i][j++]='#';map[5][i][j++]='#';map[5][i][j]='+';
    map[5][20][85]='B';
    movable[5][20][85]=-2;
    enemy_health[5][20][85]=5000;
 
    l=5;
    move_hero(19,36);
    play_game(1);
    
}