#include <iostream>
#include <SDL.h>

const int FRAMEBUFFER_WIDTH = 100;
const int FRAMEBUFFER_HEIGHT = 100;
const int FRAMEBUFFER_SIZE = FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int CELL_SIZE = WINDOW_WIDTH / FRAMEBUFFER_WIDTH;

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

Color framebuffer[FRAMEBUFFER_SIZE];
Color aliveColor = {255, 255, 255, 255}; // White
Color deadColor = {0, 0, 0, 255};       // Black

bool cells[FRAMEBUFFER_SIZE] = {false};
bool cellsNextState[FRAMEBUFFER_SIZE] = {false};

int countNeighbors(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Skip the cell itself
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < FRAMEBUFFER_WIDTH && ny >= 0 && ny < FRAMEBUFFER_HEIGHT) {
                if (cells[ny * FRAMEBUFFER_WIDTH + nx]) {
                    count++;
                }
            }
        }
    }
    return count;
}

void updateCells() {
    for (int y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
        for (int x = 0; x < FRAMEBUFFER_WIDTH; x++) {
            int index = y * FRAMEBUFFER_WIDTH + x;
            int neighbors = countNeighbors(x, y);

            if (cells[index]) {
                // Cell is alive
                if (neighbors < 2 || neighbors > 3) {
                    // Underpopulation or overpopulation: cell dies
                    cellsNextState[index] = false;
                } else {
                    // Survival: cell stays alive
                    cellsNextState[index] = true;
                }
            } else {
                // Cell is dead
                if (neighbors == 3) {
                    // Reproduction: cell becomes alive
                    cellsNextState[index] = true;
                } else {
                    cellsNextState[index] = false;
                }
            }
        }
    }

    // Update the cells array with the next state
    for (int i = 0; i < FRAMEBUFFER_SIZE; i++) {
        cells[i] = cellsNextState[i];
    }
}

void renderBuffer(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
        for (int x = 0; x < FRAMEBUFFER_WIDTH; x++) {
            int index = y * FRAMEBUFFER_WIDTH + x;
            if (cells[index]) {
                // Cell is alive, draw it with the aliveColor
                SDL_SetRenderDrawColor(renderer, aliveColor.r, aliveColor.g, aliveColor.b, aliveColor.a);
            } else {
                // Cell is dead, draw it with the deadColor
                SDL_SetRenderDrawColor(renderer, deadColor.r, deadColor.g, deadColor.b, deadColor.a);
            }

            SDL_Rect rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Conway's Game of Life", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
    );

    // Randomly initialize the cells' state
    for (int i = 0; i < FRAMEBUFFER_SIZE; i++) {
        cells[i] = rand() % 2 == 1; // 50% chance of being alive
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Update the cells' state
        updateCells();

        // Render the framebuffer to the screen
        renderBuffer(renderer);

        // Present the framebuffer on the screen
        SDL_RenderPresent(renderer);

        // Delay to limit the frame rate
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
