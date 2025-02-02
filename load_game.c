#include <stdlib.h>
#include <time.h>  
#include "sign_up.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "main_menu.h"
#include "sign_in.h"
#include "save_game.h"
#include "main_game.h"
#include "theme_menu.h"
int xx,yy,lll,scoree,akeyy,bkeyy,xpp,difff,allcoinn;
void load_game_state(struct user_data user, int map[5][200][200]
, int revealed[5][200][200],int health_bar[10], int food_stack[5], int hunger_bar[60], int *cx, int *cy,int *ls,int levels[5],int themed[5][200][200]) {
    char filepath[200];
    snprintf(filepath, sizeof(filepath), "/mnt/c/shahab/c-test/project/USERS/%s.txt",user.user_name);
    FILE *file = fopen(filepath, "r");
    char buffer[256];
    for (int i = 0; i < 3; i++) {
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            printf("Error reading file.\n");
            fclose(file);
            return;
        }
    }
    fgets(buffer, sizeof(buffer), file);
 for(int l=0;l<5;l++){   
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 150; j++) {
           fscanf(file, "%d ", &map[l][i][j]);
        }
    }
 }
    fgets(buffer, sizeof(buffer), file);
for(int l=0;l<5;l++){
    for (int i = 0; i <50 ; i++) {
        for (int j = 0; j < 150; j++) {
            fscanf(file, "%d ", &revealed[l][i][j]);
        }
    }
}
   fgets(buffer, sizeof(buffer), file);
for(int l=0;l<5;l++){
    for (int i = 0; i <50 ; i++) {
        for (int j = 0; j < 150; j++) {
            fscanf(file, "%d ", &themed[l][i][j]);
        }
    }
}
    fgets(buffer, sizeof(buffer), file);
    for (int i = 0; i < 10; i++) {
        fscanf(file, "%d ", &health_bar[i]);
    }
    fgets(buffer, sizeof(buffer), file);
    for (int i = 0; i < 5; i++) {
        fscanf(file, "%d ", &food_stack[i]);
    }
    fgets(buffer, sizeof(buffer), file);
    for (int i = 0; i < 60; i++) {
        fscanf(file, "%d ", &hunger_bar[i]);
    }
    fgets(buffer, sizeof(buffer), file);
    fscanf(file, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",&xx,&yy,&lll,&levels[0],&levels[1],&levels[2],&levels[3],&levels[4],&scoree,&akeyy,&bkeyy,&gun_stack[0],&gun_stack[1],&gun_stack[2],&gun_stack[3],&gun_stack[4],&potion_stack[0],&potion_stack[1],&potion_stack[2],&difff,&allcoinn,&xpp);
    //l=lll;
    diff=difff;
    allcoin=allcoinn;
    xp=xpp;
    score=scoree;
    akey=akeyy;
    bkey=bkeyy;
    fclose(file);
    
    for (int i = 0; i <50 ; i++) {
        for (int j = 0; j < 150; j++) {
            if(revealed[l][i][j]==1){
                if(themed[l][i][j]==1&&mapp_theme==1){
            attron(COLOR_PAIR(16));
        }
        else if(themed[l][i][j]==2&&mapp_theme==1){
            attron(COLOR_PAIR(203));
                }
        else if(themed[l][i][j]==3&&mapp_theme==1){
            attron(COLOR_PAIR(49));
                }
        else if(themed[l][i][j]==3){
            attron(COLOR_PAIR(48));
                }
        else if(themed[l][i][j]==5&&mapp_theme==1){
            attron(COLOR_PAIR(89));
                }
        else if(themed[l][i][j]==5){
            attron(COLOR_PAIR(88));
                }
        else if(themed[l][i][j]==4&&mapp_theme==1){
            attron(COLOR_PAIR(247));
                }
        else if(themed[l][i][j]==4){
            attron(COLOR_PAIR(246));
                }
        else if(themed[l][i][j]==2){
            attron(COLOR_PAIR(202));
                }
        else if(themed[l][i][j]==1){   
            attron(COLOR_PAIR(15));
        }
                if(map[l][i][j-1]=='f'||map[l][i][j-1]=='C'||map[l][i][j-1]=='c'||map[l][i][j-1]=='2'||map[l][i][j-1]=='3'||map[l][i][j-1]=='4'||map[l][i][j-1]=='5'||map[l][i][j-1]=='6'||map[l][i][j-1]=='7'||map[l][i][j-1]=='8'||map[l][i][j-1]=='g'||map[l][i][j-1]=='h'||map[l][i][j-1]=='j'){
                    continue;
                }
                else if(map[l][i][j]=='t'){
                    mvprintw(i,j,".");
                }
                else if(map[l][i][j]=='~'){
                    mvprintw(i,j,"|");
                }
                else if(map[l][i][j]=='-'){
                    mvprintw(i,j,"_");
                }
                else if(map[l][i][j]=='P'){
                    mvprintw(i,j,",");
                }
                else{
                mvprintw(i,j,"%c",map[l][i][j]);}
            attroff(COLOR_PAIR(16));
            attroff(COLOR_PAIR(49));
            attroff(COLOR_PAIR(48));
            attroff(COLOR_PAIR(89));
            attroff(COLOR_PAIR(88));
            attroff(COLOR_PAIR(247));
            attroff(COLOR_PAIR(246));
            attroff(COLOR_PAIR(203));
            attroff(COLOR_PAIR(202));
            attroff(COLOR_PAIR(15));
            }
        }
      }    
}
