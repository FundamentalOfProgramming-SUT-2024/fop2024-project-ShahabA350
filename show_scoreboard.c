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
#include "show_scoreboard.h"
void draw_horizontal_line2(int y, int x, int length) {
    mvhline(y, x, '-', length);
}

void board(int n) {
    keypad(stdscr, TRUE);
    start_color();
    init_pair(108, 8, COLOR_BLACK);
    init_pair(109, 8, COLOR_WHITE);
    init_pair(247, 241, COLOR_BLACK);
    init_pair(248, 241, COLOR_WHITE);
    init_pair(202, 202, COLOR_BLACK);
    init_pair(203, 202, COLOR_WHITE);
    init_pair(220, 220, COLOR_BLACK);
    init_pair(221, 220, COLOR_WHITE);
    attron(COLOR_PAIR(108));
    draw_vertical_line(0, 0, n-1);
    draw_horizontal_line(n-2, 1, 50);
    draw_vertical_line(0,50, n-1);
    attroff(COLOR_PAIR(108));
    attron(COLOR_PAIR(220));
    draw_vertical_line(0, 53, n);
    draw_horizontal_line(n-1, 54, 50);
    draw_vertical_line(0,104, n);
    attroff(COLOR_PAIR(220));
    attron(COLOR_PAIR(202));
    draw_vertical_line(0, 106, n-2);
    draw_horizontal_line(n-3, 107, 49);
    draw_vertical_line(0,155, n-2);
    attroff(COLOR_PAIR(202));
    attron(COLOR_PAIR(220));
    noecho();
    int x = 63, y = 5;

    mvprintw(y++, x, "                          /)");
    mvprintw(y++, x, " /\\_\\\\__               (_//");
    mvprintw(y++, x, "|   `>\\-`     _._       //`)");
    mvprintw(y++, x, " \\ /` \\\\  _.-`:::`-._  //");
    mvprintw(y++, x, "  `    \\|`    :::    `|/");
    mvprintw(y++, x, "        |     :::     |");
    mvprintw(y++, x, "        |.....:::.....|");
    mvprintw(y++, x, "        |:::::GOAT::::|");
    mvprintw(y++, x, "        |     :::     |");
    mvprintw(y++, x, "________\\     :::     /");
    mvprintw(y++, x, "         \\    :::    /");
    mvprintw(y++, x, "          `-. ::: .-'");
    mvprintw(y++, x, "           //`:::` \\\\");
    mvprintw(y++, x, "          //   '    \\\\");
    mvprintw(y++, x, "         |/          \\\\");
    attroff(COLOR_PAIR(220));
    attron(COLOR_PAIR(108));
    int x1 = 17, y1 = 4;

    mvprintw(y1++, x1, "  ,:\\      /:.");
    mvprintw(y1++, x1, " //  \\_()_/  \\\\");
    mvprintw(y1++, x1, "||   |    |   ||");
    mvprintw(y1++, x1, "||   |BEST|   ||");
    mvprintw(y1++, x1, "||   |____|   ||");
    mvprintw(y1++, x1, " \\\\  / || \\  //");
    mvprintw(y1++, x1, "  `:/  ||  \\;'");
    mvprintw(y1++, x1, "       ||");
    mvprintw(y1++, x1, "       ||");
    mvprintw(y1++, x1, "_______||");
    mvprintw(y1++, x1, "       XX");
    mvprintw(y1++, x1, "       XX");
    mvprintw(y1++, x1, "       XX");
    mvprintw(y1++, x1, "       OO");
    mvprintw(y1++, x1, "       `'");
    attroff(COLOR_PAIR(108));
    attron(COLOR_PAIR(202));

    int x2 = 122, y2 = 5; 

    mvprintw(y2++, x2, "       .--.");
    mvprintw(y2++, x2, "       |--|");
    mvprintw(y2++, x2, "       |--|");
    mvprintw(y2++, x2, "       |--|");
    mvprintw(y2++, x2, "   .---^  ^---.");
    mvprintw(y2++, x2, "   :__________:");
    mvprintw(y2++, x2, "      |E |//|");
    mvprintw(y2++, x2, "______|L |//|");
    mvprintw(y2++, x2, "      |L |//|");
    mvprintw(y2++, x2, "      |I |//|");
    mvprintw(y2++, x2, "      |T |.-|");
    mvprintw(y2++, x2, "      |E-'**|");
    mvprintw(y2++, x2, "       \\***/");
    mvprintw(y2++, x2, "        \\*/");
    mvprintw(y2++, x2, "         V");
    attroff(COLOR_PAIR(202));

    draw_horizontal_line(22,0,165);

    int l=0;
    char players[111][100];
    int  players_score[111];
    int players_xp[3][111];
    int s=0;
    FILE *file = fopen("/mnt/c/shahab/c-test/project/SCOREBOARD/scoreboard.txt", "r");
    while (s<100&&fscanf(file, "%s %d %d %d %d\n", players[s], &players_score[s],&players_xp[0][s],&players_xp[1][s],&players_xp[2][s]) != EOF) {
        s++;
    }
    fclose(file);
    for(int i=0;i<100&&players[i][0] != '\0';i++){
        for(int j=i+1;j<100&&players[j][0] != '\0';j++){
            if(players_score[i]<players_score[j]){
                char temp[100];
                int temp_score;
                int temp_xp;
                strcpy(temp,players[i]);
                strcpy(players[i],players[j]);
                strcpy(players[j],temp);
                temp_score=players_score[i];
                players_score[i]=players_score[j];
                players_score[j]=temp_score;
                temp_score=players_xp[0][i];
                players_xp[0][i]=players_xp[0][j];
                players_xp[0][j]=temp_xp;
                temp_xp=players_xp[1][i];
                players_xp[1][i]=players_xp[1][j];
                players_xp[1][j]=temp_xp;
                temp_xp=players_xp[2][i];
                players_xp[2][i]=players_xp[2][j];
                players_xp[2][j]=temp_xp;
            }
        }
    }
    draw_horizontal_line(22, 0, 165);
    mvprintw(21, 118, "SCORE");
    mvprintw(21, 127, "FINISHED");
    mvprintw(21, 138, "COINS");
    mvprintw(21, 145, "XP");
    attron(COLOR_PAIR(247));
    for(int i=24;i<46;i+=2){
     draw_horizontal_line2(i, 0, 165);
    }
    attroff(COLOR_PAIR(247));
    attron(COLOR_PAIR(220));
            mvprintw(0, 70, "finished %d times", players_xp[0][0]);
            mvprintw(2, 69, "coins:%d", players_xp[1][0]); 
            mvprintw(2, 82, "xp :%d", players_xp[2][0]);
            mvprintw(4, 70, "%s", players[0]);
            mvprintw(4, 65, "🏅");  
            if(strcmp(players[0],user.user_name)==0){
                 mvprintw(4, 67, "-->"); 
            }
            mvprintw(4, 82, "%d", players_score[0]);
    attroff(COLOR_PAIR(220));
    attron(COLOR_PAIR(108));
            mvprintw(0, 17, "finished %d times", players_xp[0][1]);
            mvprintw(1, 16, "coins:%d", players_xp[1][1]); 
            mvprintw(1, 27, "xp :%d", players_xp[2][1]);
            mvprintw(3, 20, "%s", players[1]);
            mvprintw(3, 15, "🥈"); 
            if(strcmp(players[1],user.user_name)==0){
                 mvprintw(3, 17, "-->"); 
            } 
            mvprintw(3, 27, "%d", players_score[1]);
    attroff(COLOR_PAIR(108));
    attron(COLOR_PAIR(202));
            mvprintw(0, 123, "finished %d times", players_xp[0][2]);
            mvprintw(2, 122, "coins:%d", players_xp[1][2]); 
            mvprintw(2, 133, "xp :%d", players_xp[2][2]);
            mvprintw(4, 124, "%s", players[2]); 
            mvprintw(4, 119, "🥉"); 
            if(strcmp(players[2],user.user_name)==0){
                 mvprintw(4, 121, "-->"); 
            }
            mvprintw(4, 133, "%d", players_score[2]);
    attroff(COLOR_PAIR(202));
    while(1) {
        
        int k = 0;
        for (int i = 6;i < 30 && i + l < 100; i+=2) {
            mvprintw(i + 17, 40, "                    ");
            mvprintw(i + 17, 120,"                    ");
             mvprintw(i + 17, 0,"                    ");
            mvprintw(i + 17, 0, "%d.", i/2 + l+1); 
            mvprintw(i + 17, 37, "   %s", players[i/2 + l]); 
            if(strcmp(players[i/2+l],user.user_name)==0){
                 mvprintw(i+17, 37, "-->"); 
            }
            mvprintw(i + 17, 120, "%d   ", players_score[i/2 + l]);
            mvprintw(i + 17, 130, "%d    ", players_xp[0][i/2 + l]); 
            mvprintw(i + 17, 140, "%d    ", players_xp[1][i/2 + l]); 
            mvprintw(i + 17, 145, "%d      ", players_xp[2][i/2 + l]);
        }
        refresh(); 
        int ch = getch(); 
        switch (ch) {
            case KEY_UP:
                if (l > 0) l--;
                break;
            case KEY_DOWN:
                if (players_score[l+15]!=0) l++;
                break;
            case 'q':
            display_main_menu();
                endwin(); 
                return;
        }
    }
}

// int main() {
//     initscr();
//     cbreak();   
//     noecho();  
//     start_color();
//     board(15);
//     refresh(); 
//     getch();   
//     endwin();   
//     return 0;
// }
