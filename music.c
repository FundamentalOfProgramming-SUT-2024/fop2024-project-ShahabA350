#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <dirent.h>
#include <string.h>
#include "music.h"
#include <time.h>
#include "sign_in.h"
#include <unistd.h>
#include "setting_menu.h"

void print_music_menu(int startx, int starty, int highlight, char **choices, int n_choices) {
    int x = startx + 2, y = starty + 2;
    mvprintw(starty, (COLS - strlen("[Music Menu]")) / 2, "[Music Menu]");
    mvprintw(starty + 1, startx, "________________________________________");
    for (int i = 0; i < n_choices; ++i) {
        mvprintw(y, startx, "|"); 
        if (highlight == i + 1) {
            attron(A_BOLD | A_REVERSE);
            mvprintw(y, x, "%s", choices[i]);
            attroff(A_BOLD | A_REVERSE);
        } else {
            mvprintw(y, x, "%s", choices[i]);
        }
        mvprintw(y, startx + 39, "|");
        y++;
    }
    mvprintw(y, startx, "|______________________________________|"); 
}

char* display_music() {
    int highlight = 1, choice = 0, c;
    static char result[256];
    char *music_dir = "./music";
    DIR *dir;
    struct dirent *ent;
    char *choices[100];
    int n_choices = 0;

    if ((dir = opendir(music_dir)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".mp3") || strstr(ent->d_name, ".flac") || strstr(ent->d_name, ".wav")) {
                choices[n_choices] = strdup(ent->d_name);
                n_choices++;
            }
        }
        closedir(dir);
    } else {
        perror("Could not open music directory");
        return NULL;
    }

    initscr();
    start_color();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    int width = 40;
    int height = n_choices + 5; 
    int startx = (COLS - width) / 2;
    int starty = (LINES - height) / 2;


    refresh();
    print_music_menu(startx, starty, highlight, choices, n_choices);

    while (1) {
        c = getch();
        switch (c) {
            case 'q':   
                Mix_PauseMusic();
                choice = highlight;
                break;
            case 'r':
                Mix_ResumeMusic();
                choice = highlight;
                break;
            case KEY_UP:
                if (highlight == 1) highlight = n_choices;
                else --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_choices) highlight = 1;
                else ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        clear();
        print_music_menu(startx, starty, highlight, choices, n_choices);
        refresh();
        if (choice != 0) break;
    }

    snprintf(result, sizeof(result), "%s/%s", music_dir, choices[choice - 1]);
    for (int i = 0; i < n_choices; i++) {
        free(choices[i]);
    }

    endwin();
    return result;
}

void play_music(const char *filepath) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize: %s\n", Mix_GetError());
        return;
    }

    Mix_Music *music = Mix_LoadMUS(filepath);
    

    Mix_PlayMusic(music, 1);    
    
}

void display_music_menu() {
    char* selected_music = display_music();
    if (selected_music) {
        play_music(selected_music);display_setting_menu();
        sleep(10000);
    }
    
}
