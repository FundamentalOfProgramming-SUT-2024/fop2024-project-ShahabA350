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
void save_game_state(struct user_data user, int map[5][200][200]
, int revealed[5][200][200],int revealed_path[200][200], int centers[10][2]
, int health_bar[10], int food_stack[5], int hunger_bar[60], int cx, int cy,int l,int levels[5]) {
    char filepath[200];
    snprintf(filepath, sizeof(filepath), "/mnt/c/shahab/c-test/project/USERS/%s.txt",user.user_name);
    FILE *file = fopen(filepath, "r+");
    char buffer[256];
    for (int i = 0; i < 3; i++) { 
        char buffer[256]; 
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
             printf("Error or end of file while skipping lines\n"); 
             fclose(file); return;
              } }
    fprintf(file, "map:\n");
for(int l=0;l<5;l++){
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 150; j++) {
            fprintf(file, "%d ", map[l][i][j]);
        }
        fprintf(file, "\n");
    }
}
    fprintf(file, "revealed:\n");
for(int l=0;l<5;l++){
    for (int i = 0; i <50 ; i++) {
        for (int j = 0; j < 150; j++) {
            fprintf(file, "%d ", revealed[l][i][j]);
        }
        fprintf(file, "\n");
    }
}
    fprintf(file, "themes:\n");
for(int l=0;l<5;l++){
    for (int i = 0; i <50 ; i++) {
        for (int j = 0; j < 150; j++) {
            fprintf(file, "%d ", themed[l][i][j]);
        }
        fprintf(file, "\n");
    }
}
    fprintf(file, "health:\n");
    for (int i = 0; i < 10; i++) {
        fprintf(file, "%d ", health_bar[i]);
    }
    fprintf(file, "\n");
    fprintf(file, "food inventory:\n");
    for (int i = 0; i < 5; i++) {
        fprintf(file, "%d ", food_stack[i]);
    }
    fprintf(file, "\n");
    fprintf(file, "hunger bar:\n");
    for (int i = 0; i < 60; i++) {
        fprintf(file, "%d ", hunger_bar[i]);
    }
    fprintf(file, "\n");
    fprintf(file, "current location:\n");
    fprintf(file, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", cx, cy, l,levels[0],levels[1],levels[2],levels[3],levels[4],score,akey,bkey,gun_stack[0],gun_stack[1],gun_stack[2],gun_stack[3],gun_stack[4],potion_stack[0],potion_stack[1],potion_stack[2],diff,allcoin,xp);
    // for (int i = 0; i < 5; i++) {
    //     fprintf(file, "%d ", levels[i]);
    // }

    fclose(file);

}
