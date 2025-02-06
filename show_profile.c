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
#include "show_profile.h"
#include <unistd.h>
void display_profile(){
    noecho();
 draw_horizontal_line(24, 60, 30);
draw_horizontal_line(9, 59, 31);
draw_vertical_line(10, 89, 15);
draw_vertical_line(10, 59, 15);

int l=0;
char players[111][100];
int  players_score[111];
int players_xp[3][111];
int myscore=0;
int my_finished=0;
int s=0;
FILE *file = fopen("/mnt/c/shahab/c-test/project/SCOREBOARD/scoreboard.txt", "r");
while (s<100&&fscanf(file, "%s %d %d %d %d\n", players[s], &players_score[s],&players_xp[0][s],&players_xp[1][s],&players_xp[2][s]) != EOF) {
    if(!strcmp(players[s],user.user_name)){
        my_finished=players_xp[0][s];
        myscore = players_score[s];
    }
    break;
}
mvprintw(11,60,"Name:%s",user.user_name);
mvprintw(14,60,"Password:%s",user.user_password);
mvprintw(17,60,"Highscore:%d",myscore);
mvprintw(22,65,"Finished %d times",my_finished);
int y=5;
    mvprintw(0+y,100, "                        ██████████");
    mvprintw(1+y,100, "                      ██▒▒██▒▒▒▒████");
    mvprintw(2+y,100, "                      ██▒▒██▒▒▒▒▓▓▓▓▒▒");
    mvprintw(3+y,100, "                      ██▒▒██▒▒██▒▒▒▒▒▒██");
    mvprintw(4+y,100, "                      ██▒▒██▒▒██▒▒██▒▒██");
    mvprintw(5+y,100, "                      ██▒▒██████████▒▒████");
    mvprintw(6+y,100, "                    ▒▒██▒▒██░░▓▓▒▒▒▒▓▓▓▓██");
    mvprintw(7+y,100, "                  ██▒▒██████▒▒▒▒▒▒▒▒░░████");
    mvprintw(8+y,100, "  ████          ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▓▓████          ▒▒██");
    mvprintw(9+y,100, "  ██▒▒██        ██░░░░████░░░░░░▒▒▒▒▒▒░░████        ██░░██");
    mvprintw(10+y,100, "  ██  ▒▒██████  ████████████████░░▒▒▒▒▒▒████████████░░  ██");
    mvprintw(11+y,100, "  ██░░▒▒██▒▒░░████████████████████░░▒▒▒▒████▒▒░░██▒▒  ░░██");
    mvprintw(12+y,100, "    ████░░▒▒▒▒░░██░░░░████░░░░░░░░░░▒▒▒▒██░░▒▒░░░░██▒▒██");
    mvprintw(13+y,100, "    ██▒▒▒▒▒▒▒▒░░██▒▒░░████░░▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒░░░░██████");
    mvprintw(14+y,100, "████████████▒▒░░██▒▒░░████░░▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒██████  ████");
    mvprintw(15+y,100, "██        ██  ██░░██▒▒░░████░░▒▒▒▒▒▒▒▒████▒▒▒▒██      ██  ██");
    mvprintw(16+y,100, "██░░░░░░░░  ██  ██████░░████░░▒▒░░████░░██████  ██████████");
    mvprintw(17+y,100, "██▒▒░░░░░░  ██▓▓  ████▓▓████▓▓▓▓▓▓▒▒░░▒▒████░░▓▓████████░░");
    mvprintw(18+y,100, "██▒▒░░░░░░  ████████▒▒  ░░░░░░░░▒▒    ▒▒██  ██████████");
    mvprintw(19+y,100, "██▒▒▒▒░░░░  ████░░██▒▒    ▒▒▒▒▒▒    ░░▒▒  ▓▓████████████");
    mvprintw(20+y,100, "██▒▒░░░░░░  ██      ██▒▒          ▒▒▒▒▒▒  ██    ████░░░░██");
    mvprintw(21+y,100, "██▒▒░░░░░░  ██        ████          ████████    ██▒▒▒▒▒▒░░██");
    mvprintw(22+y,100, "██▒▒░░░░░░  ██      ████░░██████████░░████░░██  ██▒▒▒▒▒▒▒▒██");
    mvprintw(23+y,100, "██▒▒░░░░░░  ██    ▓▓▒▒▒▒▓▓░░██████░░▓▓████▒▒▒▒  ██▒▒▒▒▒▒▒▒██");
    mvprintw(24+y,100, "██▒▒░░░░░░  ██  ██░░░░██████░░▒▒░░██████░░▒▒░░██  ██▒▒██████");
    mvprintw(25+y,100, "██░░░░░░░░  ██  ██▓▓████████▒▒▒▒▒▒██████▓▓▒▒▓▓    ██▓▓████░░");
    mvprintw(26+y,100, "██  ░░░░  ██  ██████████████░░▒▒░░████████████████");
    mvprintw(27+y,100, "  ██    ██  ██▒▒░░██████  ██  ▒▒░░██  ██████▒▒░░░░██");
    mvprintw(28+y,100, "    ████    ██░░░░░░████    ██  ████  ██████░░░░░░██");
    mvprintw(29+y,100, "    ░░      ██░░░░░░██░░██    ▓▓██░░  ░░████░░░░░░████");
    mvprintw(30+y,100, "          ██████▒▒░░██              ██▒▒██████░░██");
    mvprintw(31+y,100, "        ████▒▒▒▒▒▒▒▒░░▓▓            ██░░▒▒▒▒▒▒░░████");
    mvprintw(32+y,100, "    ████        ▒▒▒▒░░██              ██▒▒▒▒        ████");
    mvprintw(33+y,100, "  ██▒▒░░          ▒▒░░██              ██▒▒          ░░▒▒▒▒");
    mvprintw(34+y,100,  "  ██████████████████████              ████████████████████");
while(getch()!='q'){}
mvprintw(10 + y, 120, "░░");
mvprintw(10 + y, 128, "░░");
refresh();
usleep(2000000);

display_main_menu();
}