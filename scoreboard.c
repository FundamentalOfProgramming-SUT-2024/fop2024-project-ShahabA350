#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "load_game.h"
#include "scoreboard.h"

void submit() {
    FILE *file = fopen("/mnt/c/shahab/c-test/project/SCOREBOARD/scoreboard.txt", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    char tempusername[100];
    int tempscore = 0, game_finished = 0, a, b;
    int found = 0;
    char buffer[4096];
    char lines[100][100];
    int line_count = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        strcpy(lines[line_count], buffer);
        line_count++;
    }
    fclose(file);
    file = fopen("/mnt/c/shahab/c-test/project/SCOREBOARD/scoreboard.txt", "w");
    for (int i = 0; i < line_count; i++) {
        sscanf(lines[i], "%s %d %d %d %d\n", tempusername, &tempscore, &game_finished, &a, &b);
        if (strcmp(tempusername, user.user_name) == 0) {
            found = 1;
            if (score > tempscore) {
                fprintf(file, "%s %d %d %d %d\n", user.user_name, score, game_finished+1, a, b);
            } else {
                fprintf(file, "%s %d %d %d %d\n", user.user_name, tempscore, game_finished+1, allcoin, xp);
            }
        } else {
            fputs(lines[i], file);
        }
    }

    if (!found) {
        int finished = 1;
        fprintf(file, "%s %d %d %d %d\n", user.user_name, score, finished, allcoin, xp);
    }

    fclose(file);
}
