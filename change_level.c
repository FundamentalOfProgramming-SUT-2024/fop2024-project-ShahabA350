#include <stdio.h>
#include <stdlib.h>
#include "user_data.h"
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
#include <stdio.h>

int count_lines() {
    FILE *file = fopen("/mnt/c/shahab/c-test/project/SCOREBOARD/scoreboard.txt", "r");
    int line = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            line++;
        }
    }

    fclose(file);
    return line+1;
}

submit(){
    int lines = count_lines();
    FILE *file = fopen("/mnt/c/shahab/c-test/project/SCOREBOARD/scoreboard.txt", "r+");
    char buffer[256];
    for (int i = 0; i < lines; i++) { 
        char buffer[256]; 
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
              } }
        fprintf(file, "%s %d",user.user_name,score);

}
