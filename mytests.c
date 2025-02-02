\#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    Mix_Music *music = Mix_LoadMUS("/mnt/c/shahab/c-test/project/soundtracks/Prepare-For-War.wav");
    if (music == NULL) {
        fprintf(stderr, "Failed to load WAV file: %s\n", Mix_GetError());
        return 1;
    }

    Mix_PlayMusic(music, 1); 
    while (Mix_PlayingMusic()) {
        SDL_Delay(100);
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
