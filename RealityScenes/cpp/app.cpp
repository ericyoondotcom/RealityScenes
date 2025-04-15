#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed (%s)", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Rerality Scenes", 960, 540, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    bool quitOnNextFrame = false;
    while(!quitOnNextFrame) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quitOnNextFrame = true;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
