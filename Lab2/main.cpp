#include <iostream>
#include <SDL.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void render(SDL_Renderer* renderer) {
    // Limpiar la pantalla con un color negro
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dibujar un rectángulo rojo en el centro de la pantalla
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = {WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 50, 100, 100};
    SDL_RenderFillRect(renderer, &rect);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("life", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
    );

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Call our render function
        render(renderer);

        // Present the frame buffer to the screen
        SDL_RenderPresent(renderer);

        // Delay to limit the frame rate
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
