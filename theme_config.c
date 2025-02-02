#include <ncurses.h>
#include "theme_config.h"
int current_fg_color = COLOR_WHITE;
int current_bg_color = COLOR_BLACK;

void set_theme(int theme) {
    if (theme == 0) {
        current_fg_color = COLOR_WHITE;
        current_bg_color = COLOR_BLACK;
    } else if (theme == 1) {
        current_fg_color = COLOR_BLACK;
        current_bg_color = COLOR_WHITE;
    } else if (theme == 2) {
        current_fg_color = COLOR_YELLOW;
        current_bg_color = COLOR_BLACK;
        theme=0;
    } else if (theme == 3) {
        current_fg_color = COLOR_CYAN;
        current_bg_color = COLOR_BLACK;
        theme=0;
    }
}
