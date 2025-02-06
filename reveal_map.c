#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "main_game.h"
#include "main_menu.h"
#include "theme_menu.h"
#include "reveal_map.h"
extern int l;
void reveal_map(int map[6][200][200], int cy, int cx) {
    init_pair(220,220,COLOR_BLACK);
    int tempx = cx;
    int tempy = cy;

    if (map[l][cy][cx] == '.'||map[l][cy][cx] == '<') {
        init_pair(16, COLOR_MAGENTA, COLOR_BLACK);init_pair(15, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(203, 202, COLOR_BLACK);init_pair(202, 202, COLOR_BLACK);
        init_pair(49, 48, COLOR_BLACK);init_pair(48,48, COLOR_BLACK);
        init_pair(89, 88, COLOR_BLACK);init_pair(88,88, COLOR_BLACK);
        init_pair(247, 246, COLOR_BLACK);init_pair(246,246, COLOR_BLACK);
        if(themed[l][cy][cx]==1&&mapp_theme==1){
            attron(COLOR_PAIR(16));
        }
        else if(themed[l][cy][cx]==2&&mapp_theme==1){
            attron(COLOR_PAIR(203));
                }
        else if(themed[l][cy][cx]==6&&mapp_theme==1){
            attron(COLOR_PAIR(221));
                }
                else if(themed[l][cy][cx]==6){
            attron(COLOR_PAIR(220));
            endisnear=1;
                }
        else if(themed[l][cy][cx]==3&&mapp_theme==1){
            attron(COLOR_PAIR(49));
                }
        else if(themed[l][cy][cx]==3){
            attron(COLOR_PAIR(48));
                }
        else if(themed[l][cy][cx]==5&&mapp_theme==1){
            attron(COLOR_PAIR(89));
                }
        else if(themed[l][cy][cx]==5){
            attron(COLOR_PAIR(88));
                }
        else if(themed[l][cy][cx]==5&&mapp_theme==1){
            attron(COLOR_PAIR(247));
                }
        else if(themed[l][cy][cx]==4){
            attron(COLOR_PAIR(246));
                }
        else if(themed[l][cy][cx]==2){
            attron(COLOR_PAIR(202));
                }
        else if(themed[l][cy][cx]==1){   
            attron(COLOR_PAIR(15));
        }
        while (map[l][cy][tempx] != '|' && map[l][cy][tempx] != '+' && map[l][cy][tempx] != '='&&map[l][cy][tempx] != '~'&&map[l][cy][tempx] != '?'&&map[l][cy][tempx] != '*') {
            if (map[l][cy][tempx] == 't') {
                if(themed[l][cy][tempx]==5&&abs(cx-tempx)>2){mvprintw(cy,tempx," ");}
                else{
                mvprintw(cy, tempx, ".");}
            } else if (map[l][cy][tempx] == '-') {
                mvprintw(cy, tempx, "_");   
            } else if (map[l][cy][tempx] == '~') {
                mvprintw(cy, tempx, "|");
            } else if (map[l][cy][tempx] == 'L') {
                    mvprintw(cy, tempx, "ค");
            }else if (map[l][cy][tempx] == 'P') {
                mvprintw(cy, tempx,","); 
            } else {
                if(themed[l][cy][tempx]==5&&abs(cx-tempx)>2){mvprintw(cy,tempx," ");}
                else{
                mvprintw(cy, tempx,"%c",map[l][cy][tempx]);}
            }
            revealed[l][cy][tempx] = 1;
            while (map[l][tempy][tempx] != '_' && map[l][tempy][tempx] != '+' && map[l][tempy][tempx] != '='&&map[l][tempy][tempx] != '-'&&map[l][tempy][tempx] != '?'&&map[l][tempy][tempx] != '*') {
                if (map[l][tempy][tempx] == 't') {
                    if(themed[l][tempy][tempx]==5&&abs(cx-tempx)>2||abs(cy-tempy)>2){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx,".");}               
                } else if (map[l][tempy][tempx] == '-') {
                    mvprintw(tempy, tempx, "_");
                } else if (map[l][tempy][tempx] == '~') {
                    mvprintw(tempy, tempx, "|");
                } else if (map[l][tempy][tempx] == 'L') {
                    mvprintw(tempy, tempx, "ค");
                }else if (map[l][tempy][tempx] == 'P') {
                mvprintw(tempy, tempx,",");
                } else {
                    if(themed[l][tempy][tempx]==5&&(abs(cx-tempx)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx, "%c", map[l][tempy][tempx]);}    
                }
                revealed[l][tempy][tempx] = 1;
                tempy--;

                if (map[l][tempy][tempx + 1] == 't') {
                    if(themed[l][tempy][tempx+1]==5&&(abs(cx-tempx-1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx+1," ");}
                else{
                mvprintw(tempy, tempx+1,".");} 
                } else if (map[l][tempy][tempx + 1] == '-') {
                    mvprintw(tempy, tempx + 1, "_");
                } else if (map[l][tempy][tempx + 1] == '~') {
                    mvprintw(tempy, tempx + 1, "|");
                } else if (map[l][tempy][tempx+1] == 'L') {
                    mvprintw(tempy, tempx+1, "ค");
                }else if (map[l][tempy][tempx+1] == 'P') {
                    mvprintw(tempy, tempx+1,",");
                } else {
                    if(themed[l][tempy][tempx+1]==5&&(abs(cx-tempx-1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx+1," ");}
                else{
                mvprintw(tempy, tempx+1,"%c",map[l][tempy][tempx + 1]);} 
                }

                if (map[l][tempy][tempx - 1] == 't') {
                    if(themed[l][tempy][tempx-1]==5&&(abs(cx-tempx+1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx-1," ");}
                else{
                mvprintw(tempy, tempx-1,".");} 
                 
                     
                } else if (map[l][tempy][tempx - 1] == '-') {
                    mvprintw(tempy, tempx - 1, "_");
                } else if (map[l][tempy][tempx - 1] == '~') {
                    mvprintw(tempy, tempx - 1, "|");
                } else if (map[l][tempy][tempx-1] == 'L') {
                    mvprintw(tempy, tempx-1, "ค");
                }else if (map[l][tempy][tempx-1] == 'P') {
                mvprintw(tempy, tempx-1,",");
                } else {
                    if(themed[l][tempy][tempx-1]==5&&(abs(cx-tempx+1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx-1," ");}
                else{
                mvprintw(tempy, tempx+1,"%c",map[l][tempy][tempx+1]);} 
                }

                revealed[l][tempy][tempx + 1] = 1;
                revealed[l][tempy][tempx - 1] = 1;
            }

            if (map[l][tempy][tempx] == 't') {
               if(themed[l][tempy][tempx]==5&&abs(cx-tempx)>2||abs(cy-tempy)>2){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx,".");}      
            } else if (map[l][tempy][tempx] == '-') {
                mvprintw(tempy, tempx, "_");
            } else if (map[l][tempy][tempx] == '~') {
                mvprintw(tempy, tempx, "|");
            }else if (map[l][tempy][tempx] == 'P') {
                mvprintw(tempy, tempx,",");
            } else if (map[l][tempy][tempx] == 'L') {
                    mvprintw(tempy, tempx, "ค");
            } else {
                if(themed[l][tempy][tempx]==5&&(abs(cx-tempx)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx, "%c", map[l][tempy][tempx]);}
            }
            revealed[l][tempy][tempx] = 1;
            tempy = cy;

            while (map[l][tempy][tempx] != '_' && map[l][tempy][tempx] != '+' && map[l][tempy][tempx] != '='&&map[l][tempy][tempx] != '-'&&map[l][tempy][tempx] != '?'&&map[l][tempy][tempx] != '*') {
                if (map[l][tempy][tempx] == 't') {
                    if(themed[l][tempy][tempx]==5&&abs(cx-tempx)>2||abs(cy-tempy)>2){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx,".");}
                } else if (map[l][tempy][tempx] == '-') {
                    mvprintw(tempy, tempx, "_");
                } else if (map[l][tempy][tempx] == '~') {
                    mvprintw(tempy, tempx, "|");
                } else if (map[l][tempy][tempx] == 'L') {
                    mvprintw(tempy, tempx, "ค");
                }else if (map[l][tempy][tempx] == 'P') {
                mvprintw(tempy, tempx,",");
                } else {
                   if(themed[l][tempy][tempx]==5&&(abs(cx-tempx)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx, "%c", map[l][tempy][tempx]);}
                }
                revealed[l][tempy][tempx] = 1;
                tempy++;

                if (map[l][tempy][tempx + 1] == 't') {
                    if(themed[l][tempy][tempx+1]==5&&(abs(cx-tempx-1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx+1," ");}
                else{
                mvprintw(tempy, tempx+1,".");} 
                 
                     
                } else if (map[l][tempy][tempx + 1] == '-') {
                    mvprintw(tempy, tempx + 1, "_");
                } else if (map[l][tempy][tempx + 1] == '~') {
                    mvprintw(tempy, tempx + 1, "|");
                } else if (map[l][tempy][tempx+1] == 'L') {
                    mvprintw(tempy, tempx+1, "ค");
                }else if (map[l][tempy][tempx+1] == 'P') {
                     mvprintw(tempy, tempx+1,",");
                } else {
                    if(themed[l][tempy][tempx+1]==5&&(abs(cx-tempx-1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx+1," ");}
                else{
                mvprintw(tempy, tempx+1,"%c",map[l][tempy][tempx + 1]);} 
                }

                if (map[l][tempy][tempx - 1] == 't') {
                    if(themed[l][tempy][tempx-1]==5&&(abs(cx-tempx+1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx-1," ");}
                else{
                mvprintw(tempy, tempx-1,".");} 
                 
                     
                } else if (map[l][tempy][tempx - 1] == '-') {
                    mvprintw(tempy, tempx - 1, "_");
                } else if (map[l][tempy][tempx - 1] == '~') {
                    mvprintw(tempy, tempx - 1, "|");
                } else if (map[l][tempy][tempx-1] == 'L') {
                      mvprintw(tempy, tempx-1, "ค");
                }else if (map[l][tempy][tempx-1] == 'P') {
                mvprintw(tempy, tempx-1,",");
                } else {
                     if(themed[l][tempy][tempx-1]==5&&(abs(cx-tempx+1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx-1," ");}
                else{
                mvprintw(tempy, tempx-1,"%c",map[l][tempy][tempx-1]);} 
                }

                revealed[l][tempy][tempx + 1] = 1;
                revealed[l][tempy][tempx - 1] = 1;
            }

            if (map[l][tempy][tempx] == 't') {
               if(themed[l][tempy][tempx]==5&&abs(cx-tempx)>2||abs(cy-tempy)>2){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx,".");}
             
                     
            } else if (map[l][tempy][tempx] == '-') {
                mvprintw(tempy, tempx, "_");
            } else if (map[l][tempy][tempx] == '~') {
                mvprintw(tempy, tempx, "|");
            } else if (map[l][tempy][tempx] == 'L') {
                mvprintw(tempy, tempx, "ค");
            }else if (map[l][tempy][tempx] == 'P') {
                mvprintw(tempy, tempx,",");
            } else {
                if(themed[l][tempy][tempx]==5&&(abs(cx-tempx)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx, "%c", map[l][tempy][tempx]);}
            }
            revealed[l][tempy][tempx] = 1;
            tempx++;
            tempy = cy;
        }

        if (map[l][tempy][tempx] == 't') {
            if(themed[l][tempy][tempx]==5&&abs(cx-tempx)>2||abs(cy-tempy)>2){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx,".");}
         
             
        } else if (map[l][tempy][tempx] == '-') {
            mvprintw(tempy, tempx, "_");
        } else if (map[l][tempy][tempx] == '~') {
            mvprintw(tempy, tempx, "|");
        } else if (map[l][tempy][tempx] == 'L') {
            mvprintw(tempy, tempx, "ค");
        }else if (map[l][tempy][tempx] == 'P') {
                mvprintw(tempy, tempx,",");
        } else {
           if(themed[l][tempy][tempx]==5&&(abs(cx-tempx)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx, "%c", map[l][tempy][tempx]);}
        }
        revealed[l][tempy][tempx] = 1;
        tempx = cx;

        while (map[l][cy][tempx] != '|' && map[l][cy][tempx] != '+' && map[l][cy][tempx] != '='&&map[l][cy][tempx] != '~'&&map[l][cy][tempx] != '?'&&map[l][cy][tempx] != '*') {
            if (map[l][cy][tempx] == 't') {
               if(themed[l][cy][tempx]==5&&abs(cx-tempx)>2){mvprintw(cy,tempx," ");}
                else{
                mvprintw(cy, tempx,".");}
             
                 
            } else if (map[l][cy][tempx] == '-') {
                mvprintw(cy, tempx, "_");
            } else if (map[l][cy][tempx] == '~') {
                mvprintw(cy, tempx, "|");
            } else if (map[l][cy][tempx] == 'L') {
                mvprintw(cy, tempx, "ค");
            }else if (map[l][cy][tempx] == 'P') {
                mvprintw(cy, tempx,",");
            } else {
                if(themed[l][cy][tempx]==5&&(abs(cx-tempx)>2)){mvprintw(cy,tempx," ");}
                else{
                mvprintw(cy, tempx, "%c", map[l][cy][tempx]);}
            }
            revealed[l][cy][tempx] = 1;

            while (map[l][tempy][tempx] != '_' && map[l][tempy][tempx] != '+' && map[l][tempy][tempx] != '='&&map[l][tempy][tempx] != '-'&&map[l][tempy][tempx] != '?'&&map[l][tempy][tempx] != '*') {
                if (map[l][tempy][tempx] == 't') {
                    if(themed[l][tempy][tempx]==5&&abs(cx-tempx)>2||abs(cy-tempy)>2){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx,".");}
                 
                     
                } else if (map[l][tempy][tempx] == '-') {
                    mvprintw(tempy, tempx, "_");
                } else if (map[l][tempy][tempx] == '~') {
                    mvprintw(tempy, tempx, "|");
                } else if (map[l][tempy][tempx] == 'L') {
                    mvprintw(tempy, tempx, "ค");
                }else if (map[l][tempy][tempx] == 'P') {
                mvprintw(tempy, tempx,",");
                } else {
                   if(themed[l][tempy][tempx]==5&&(abs(cx-tempx)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx, "%c", map[l][tempy][tempx]);}
                }
                revealed[l][tempy][tempx] = 1;
                tempy--;

                if (map[l][tempy][tempx + 1] == 't') {
                   if(themed[l][tempy][tempx+1]==5&&(abs(cx-tempx-1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx+1," ");}
                else{
                mvprintw(tempy, tempx+1,".");} 
                 
                     
                } else if (map[l][tempy][tempx + 1] == '-') {
                    mvprintw(tempy, tempx + 1, "_");
                } else if (map[l][tempy][tempx + 1] == '~') {
                    mvprintw(tempy, tempx + 1, "|");
                } else if (map[l][tempy][tempx+1] == 'L') {
                    mvprintw(tempy, tempx+1, "ค");
                    }else if (map[l][tempy][tempx+1] == 'P') {
                mvprintw(tempy, tempx+1,",");
                } else {
                    if(themed[l][tempy][tempx+1]==5&&(abs(cx-tempx-1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx+1," ");}
                else{
                mvprintw(tempy, tempx+1,"%c",map[l][tempy][tempx + 1]);} 
                }

                if (map[l][tempy][tempx - 1] == 't') {
                     if(themed[l][tempy][tempx-1]==5&&(abs(cx-tempx+1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx-1," ");}
                else{
                mvprintw(tempy, tempx-1,".");} 
                 
                     
                } else if (map[l][tempy][tempx - 1] == '-') {
                    mvprintw(tempy, tempx - 1, "_");
                } else if (map[l][tempy][tempx - 1] == '~') {
                    mvprintw(tempy, tempx - 1, "|");
                } else if (map[l][tempy][tempx-1] == 'L') {
                    mvprintw(tempy, tempx-1, "ค");
                }else if (map[l][tempy][tempx-1] == 'P') {
                mvprintw(tempy, tempx-1,",");
                } else {
                    if(themed[l][tempy][tempx-1]==5&&(abs(cx-tempx+1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx-1," ");}
                else{
                mvprintw(tempy, tempx-1,"%c",map[l][tempy][tempx-1]);} 
                }

                revealed[l][tempy][tempx + 1] = 1;
                revealed[l][tempy][tempx - 1] = 1;
            }

            if (map[l][tempy][tempx] == 't') {
                if(themed[l][tempy][tempx]==5&&abs(cx-tempx)>2||abs(cy-tempy)>2){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx,".");}
            } else if (map[l][tempy][tempx] == '-') {
                mvprintw(tempy, tempx, "_");
            } else if (map[l][tempy][tempx] == '~') {
                mvprintw(tempy, tempx, "|");
                } else if (map[l][tempy][tempx] == 'L') {
                    mvprintw(tempy, tempx, "ค");
            }else if (map[l][tempy][tempx] == 'P') {
                mvprintw(tempy, tempx,",");
            } else {
                if(themed[l][tempy][tempx]==5&&(abs(cx-tempx)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx, "%c", map[l][tempy][tempx]);}
            }
            revealed[l][tempy][tempx] = 1;
            tempy = cy;

            while (map[l][tempy][tempx] != '_' && map[l][tempy][tempx] != '+' && map[l][tempy][tempx] != '='&&map[l][tempy][tempx] != '-'&&map[l][tempy][tempx] != '?'&&map[l][tempy][tempx] != '*') {
                if (map[l][tempy][tempx] == 't') {
                    if(themed[l][tempy][tempx]==5&&abs(cx-tempx)>2||abs(cy-tempy)>2){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx,".");}
                } else if (map[l][tempy][tempx] == '-') {
                    mvprintw(tempy, tempx, "_");
                } else if (map[l][tempy][tempx] == '~') {
                    mvprintw(tempy, tempx, "|");
                } else if (map[l][tempy][tempx] == 'L') {
                    mvprintw(tempy, tempx, "ค");
                }else if (map[l][tempy][tempx] == 'P') {
                mvprintw(tempy, tempx,",");
                } else {
                    if(themed[l][tempy][tempx]==5&&(abs(cx-tempx)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx, "%c", map[l][tempy][tempx]);}
                }
                revealed[l][tempy][tempx] = 1;
                tempy++;

                if (map[l][tempy][tempx + 1] == 't') {
                   if(themed[l][tempy][tempx+1]==5&&(abs(cx-tempx-1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx+1," ");}
                else{
                mvprintw(tempy, tempx+1,".");} 
                 
                     
                } else if (map[l][tempy][tempx + 1] == '-') {
                    mvprintw(tempy, tempx + 1, "_");
                } else if (map[l][tempy][tempx + 1] == '~') {
                    mvprintw(tempy, tempx + 1, "|");
                } else if (map[l][tempy][tempx+1] == 'L') {
                    mvprintw(tempy, tempx+1, "ค");
                }else if (map[l][tempy][tempx+1] == 'P') {
                mvprintw(tempy, tempx+1,",");
                } else {
                    if(themed[l][tempy][tempx+1]==5&&(abs(cx-tempx-1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx+1," ");}
                else{
                mvprintw(tempy, tempx+1,"%c",map[l][tempy][tempx + 1]);} 
                }

                if (map[l][tempy][tempx - 1] == 't') {
                    if(themed[l][tempy][tempx-1]==5&&(abs(cx-tempx+1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx-1," ");}
                else{
                mvprintw(tempy, tempx-1,".");} 
                 
                     
                } else if (map[l][tempy][tempx - 1] == '-') {
                    mvprintw(tempy, tempx - 1, "_");
                } else if (map[l][tempy][tempx - 1] == '~') {
                    mvprintw(tempy, tempx - 1, "|");
                } else if (map[l][tempy][tempx-1] == 'L') {
                    mvprintw(tempy, tempx-1, "ค");
                }else if (map[l][tempy][tempx-1] == 'P') {
                mvprintw(tempy, tempx-1,",");
                } else {
                     if(themed[l][tempy][tempx-1]==5&&(abs(cx-tempx+1)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx-1," ");}
                else{
                mvprintw(tempy, tempx-1,"%c",map[l][tempy][tempx-1]);} 
                }

                revealed[l][tempy][tempx + 1] = 1;
                revealed[l][tempy][tempx - 1] = 1;
            }

            if (map[l][tempy][tempx] == 't') {
                if(themed[l][tempy][tempx]==5&&abs(cx-tempx)>2||abs(cy-tempy)>2){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx,".");}
             
                 
            } else if (map[l][tempy][tempx] == '-') {
                mvprintw(tempy, tempx, "_");
            } else if (map[l][tempy][tempx] == '~') {
                mvprintw(tempy, tempx, "|");
            } else if (map[l][tempy][tempx] == 'L') {
                mvprintw(tempy, tempx, "ค");
            }else if (map[l][tempy][tempx] == 'P') {
                mvprintw(tempy, tempx,",");
            } else {
                if(themed[l][tempy][tempx]==5&&(abs(cx-tempx)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx, "%c", map[l][tempy][tempx]);}
            }
            revealed[l][tempy][tempx] = 1;
            tempx--;
            tempy = cy;
        }
        for(int i=0;i<50;i++){
            for(int j=0;j<150;j++){
                if(themed[l][i][j]==5&&(abs(j-cx)>2||abs(i-cy)>2)){
                    mvprintw(i,j," ");
                }
            }
        }
        if (map[l][tempy][tempx] == 't') {
            if(themed[l][tempy][tempx]==5&&abs(cx-tempx)>2||abs(cy-tempy)>2){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx,".");}
        } else if (map[l][tempy][tempx] == '-') {
            mvprintw(tempy, tempx, "_");
        } else if (map[l][tempy][tempx] == '~') {
            mvprintw(tempy, tempx, "|");
        } else if (map[l][tempy][tempx] == 'L') {
            mvprintw(tempy, tempx, "ค");
        }else if (map[l][tempy][tempx] == 'P') {
                mvprintw(tempy, tempx,",");
        } else {
            if(themed[l][tempy][tempx]==5&&(abs(cx-tempx)>2||abs(cy-tempy)>2)){mvprintw(tempy,tempx," ");}
                else{
                mvprintw(tempy, tempx, "%c", map[l][tempy][tempx]);}
        }
        revealed[l][tempy][tempx] = 1;
    }
    for(int i=0;i<50;i++){
        for(int j=0;j<150;j++){
            if(map[l][i][j-1]=='f'||map[l][i][j-1]=='C'||map[l][i][j-1]=='c'||map[l][i][j-1]=='2'||map[l][i][j-1]=='3'||map[l][i][j-1]=='4'||map[l][i][j-1]=='5'||map[l][i][j-1]=='6'||map[l][i][j-1]=='7'||map[l][i][j-1]=='8'||map[l][i][j-1]=='g'||map[l][i][j-1]=='h'||map[l][i][j-1]=='j'){
                    continue;
                }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='f'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='f'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"🍒");
                j++;
                map[l][i][j]='.';
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='g'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='g'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"🍒");
                j++;
                map[l][i][j]='.';
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='h'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='h'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"🍎");
                j++;
                map[l][i][j]='.';
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='j'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='j'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"🍓");
                j++;
                map[l][i][j]='.';
            }
            else if((map[l][i][j+1]=='<'||map[l][i][j+1]=='>')&&map[l][i][j]=='f'){
                map[l][i][j]='.';
            }
        }
    }
    for(int i=0;i<50;i++){
        for(int j=0;j<150;j++){
            if(map[l][i][j-1]=='f'||map[l][i][j-1]=='C'||map[l][i][j-1]=='c'||map[l][i][j-1]=='2'||map[l][i][j-1]=='3'||map[l][i][j-1]=='4'||map[l][i][j-1]=='5'||map[l][i][j-1]=='6'||map[l][i][j-1]=='7'||map[l][i][j-1]=='8'||map[l][i][j-1]=='g'||map[l][i][j-1]=='h'||map[l][i][j-1]=='j'){
                    continue;
                }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='c'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='c'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"🪙");
                j++;
                map[l][i][j]='.';
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='C'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='C'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"💰");
                j++;
                map[l][i][j]='.';
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='1'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='1'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"⚒");
                j++;
                map[l][i][j]='.';
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='2'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='2'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"🗡");
                j++;
                map[l][i][j]='.';
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='3'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='3'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"🪄");
                j++;
                map[l][i][j]='.';
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='4'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='4'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"➳");
                j++;
                map[l][i][j]='.';
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='5'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='5'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"⚔");
                j++;
                map[l][i][j]='.';
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='6'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='6'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"🧉");
                j++;
                map[l][i][j]='.';
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='7'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='7'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"🧪");
                j++;
                map[l][i][j]='.';
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='8'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='8'&&revealed[l][i][j]==1)){
                mvprintw(i,j,"🔮");
                j++;
                map[l][i][j]='.';
            }
            
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='k'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='k'&&revealed[l][i][j]==1)){
                
                attron(COLOR_PAIR(220));
                mvprintw(i,j,"△");
                j++;
                map[l][i][j]='.';
                attroff(COLOR_PAIR(220));
            }
             else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='k'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='k'&&revealed[l][i][j]==1)){
                
                attron(COLOR_PAIR(220));
                mvprintw(i,j,"△");
                j++;
                map[l][i][j]='.';
                attroff(COLOR_PAIR(220));
            }
             else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='k'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='k'&&revealed[l][i][j]==1)){
                
                attron(COLOR_PAIR(220));
                mvprintw(i,j,"△");
                j++;
                map[l][i][j]='.';
                attroff(COLOR_PAIR(220));
            }
             else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='d'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='d'&&revealed[l][i][j]==1)){
                
                attron(COLOR_PAIR(220));
                mvprintw(i,j,"ӿ");
                attroff(COLOR_PAIR(220));
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='w'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='w'&&revealed[l][i][j]==1)){
                
                attron(COLOR_PAIR(16));
                mvprintw(i,j,"܀");
                attroff(COLOR_PAIR(16));
            }
            else if(map[l][i][j+1]!='<'&&map[l][i][j+1]!='>'&&(themed[l][i][j]==5&&abs(i-cy)<3&&abs(j-cx)<3&&map[l][i][j]=='a'&&revealed[l][i][j]==1)||(themed[l][i][j]!=5&&map[l][i][j]=='a'&&revealed[l][i][j]==1)){
                
                attron(COLOR_PAIR(108));
                mvprintw(i,j,"ܤ");
                attroff(COLOR_PAIR(108));
            }
            else if((map[l][i][j+1]=='<'||map[l][i][j+1]=='>')&&map[l][i][j]=='f'){
                map[l][i][j]='.';
            }
        }
    }
    
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
    for(int i=0;i<50;i++){
        for(int j=0;j<150;j++){
            if(unlocked==0&&map[l][i][j]=='*'&&revealed[l][i][j]==1){
                attron(COLOR_PAIR(88)); 
                mvprintw(i,j,"*");
                attroff(COLOR_PAIR(88)); 
            }
            else if(unlocked==1&&map[l][i][j]=='*'&&revealed[l][i][j]==1){
                attron(COLOR_PAIR(48)); 
                mvprintw(i,j,"*");
                attroff(COLOR_PAIR(48));                 
            }
        }
    }

}
void reveal_path(int map[6][200][200], int cy, int cx, int pery, int perx) {
    if (cy < 0 || cy >= 120 || cx < 0 || cx >= 198) return;
    if(map[l][cy][cx]=='+'){mvprintw(cy, cx, "%c", map[l][cy][cx]);
    revealed[l][cy][cx] = 1;return;}
    if (map[l][cy][cx] != '#') return;
    if(revealed_path[cy][cx]==1)return;
    if (abs(cx - perx) + abs(cy - pery) > 5) return;
    mvprintw(cy, cx, "%c", map[l][cy][cx]);
    revealed[l][cy][cx] = 1;
    revealed_path[cy][cx]=1;
    reveal_path(map, cy - 1, cx, pery, perx);
    reveal_path(map, cy + 1, cx, pery, perx);
    reveal_path(map, cy, cx - 1, pery, perx);
    reveal_path(map, cy, cx + 1, pery, perx);
}