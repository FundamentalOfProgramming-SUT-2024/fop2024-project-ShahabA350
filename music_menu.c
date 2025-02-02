#include <ncurses.h>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_mixer.h>
#include "music_menu.h"

void play_music(const char *file) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        mvprintw(28, 70, "Failed to initialize SDL_mixer");
        return;
    }
    Mix_Music *music = Mix_LoadMUS(file);
    if (music == NULL) {
        mvprintw(28, 70, "Failed to load music file");
        return;
    }
    Mix_PlayMusic(music, -1);
}

void select_button_music() {
    int x, y;
    int selected_char;

    while (1) {
        getyx(stdscr, y, x);
        refresh();

        selected_char = getch();
        if (selected_char == '\n') {
            if (y == 17 && x == 70) {
                play_music("path/to/music1.mp3");
                mvprintw(28, 70, "Playing Music 1");
            } else if (y == 20 && x == 70) {
                play_music("path/to/music2.mp3");
                mvprintw(28, 70, "Playing Music 2");
            } else if (y == 23 && x == 70) {
                play_music("path/to/music3.mp3");
                mvprintw(28, 70, "Playing Music 3");
            } else if (y == 26 && x == 70) {
                Mix_HaltMusic();
                mvprintw(28, 70, "Stopping Music");
            } else if (y == 29 && x == 70) {
                mvprintw(28, 70, "Exiting Music Menu");
                break;
            }
            break;
        }

        switch (selected_char) {
            case KEY_UP:
                if (y == 20) {
                    mvprintw(20, 70, "Music 2");
                    attron(A_REVERSE);
                    mvprintw(17, 70, "Music 1");
                    attroff(A_REVERSE);
                    move(17, 70);
                } else if (y == 23) {
                    mvprintw(23, 70, "Music 3");
                    attron(A_REVERSE);
                    mvprintw(20, 70, "Music 2");
                    attroff(A_REVERSE);
                    move(20, 70);
                } else if (y == 26) {
                    mvprintw(26, 70, "Stop Music");
                    attron(A_REVERSE);
                    mvprintw(23, 70, "Music 3");
                    attroff(A_REVERSE);
                    move(23, 70);
                } else if (y == 29) {
                    mvprintw(29, 70, "Exit");
                    attron(A_REVERSE);
                    mvprintw(26, 70, "Stop Music");
                    attroff(A_REVERSE);
                    move(26, 70);
                }
                break;
            case KEY_DOWN:
                if (y == 17) {
                    mvprintw(17, 70, "Music 1");
                    attron(A_REVERSE);
                    mvprintw(20, 70, "Music 2");
                    attroff(A_REVERSE);
                    move(20, 70);
                } else if (y == 20) {
                    mvprintw(20, 70, "Music 2");
                    attron(A_REVERSE);
                    mvprintw(23, 70, "Music 3");
                    attroff(A_REVERSE);
                    move(23, 70);
                } else if (y == 23) {
                    mvprintw(23, 70, "Music 3");
                    attron(A_REVERSE);
                    mvprintw(26, 70, "Stop Music");
                    attroff(A_REVERSE);
                    move(26, 70);
                } else if (y == 26) {
                    mvprintw(26, 70, "Stop Music");
                    attron(A_REVERSE);
                    mvprintw(29, 70, "Exit");
                    attroff(A_REVERSE);
                    move(29, 70);
                }
                break;
            default:
                break;
        }

        refresh();
    }
}

void display_music_menu() {
    initscr();
    clear();
    refresh();
    keypad(stdscr, TRUE);
    mvprintw(5, 70, "Select Music");
    mvprintw(17, 70, "Music 1");
    mvprintw(20, 70, "Music 2");
    mvprintw(23, 70, "Music 3");
    mvprintw(26, 70, "Stop Music");
    mvprintw(29, 70, "Exit");
    move(17, 70);
    attron(A_REVERSE);
    mvprintw(17, 70, "Music 1");
    attroff(A_REVERSE);

    refresh();
    select_button_music();

    endwin();
}
