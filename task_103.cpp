#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool game_running = false;

int rad1 = 80;
int cenx1 = -rad1;
int ceny1 = SCREEN_HEIGHT / 2;

int rad2 = 20;
int cenx2 = SCREEN_WIDTH / 2;
int ceny2 = rad2;

bool initialize_window() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("ERROR INITIALIZING SDL!");
        return false;
    }

    window = SDL_CreateWindow("Sumu's Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        return false;
    }

    return true;
}

void process_input() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RIGHT) {
                cenx2 += 10;
            }
            else if (event.key.keysym.sym == SDLK_LEFT) {
                cenx2 -= 10;
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                ceny2 -= 10;
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                ceny2 += 10;
            }
        }
        else if (event.type == SDL_QUIT) {
            game_running = false;
        }
    }
}

void drawSolidCircle(SDL_Renderer* renderer, int cenx, int ceny, int rad) {
    for (int x = -rad; x <= rad; x++) {
        for (int y = -rad; y <= rad; y++) {
            if (x * x + y * y <= rad * rad) {
                SDL_RenderDrawPoint(renderer, cenx + x, ceny + y);
            }
        }
    }
}

void update() {
    cenx1 += 2;
    if (cenx1 - rad1 >= SCREEN_WIDTH) {
        cenx1 = -rad1;
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    // Draw circle 1
    SDL_SetRenderDrawColor(renderer, 255, 255, 150, 255);
    drawSolidCircle(renderer, cenx1, ceny1, rad1);

    // Draw circle 2
    SDL_SetRenderDrawColor(renderer, 210, 133, 133, 255);
    drawSolidCircle(renderer, cenx2, ceny2, rad2);

    SDL_RenderPresent(renderer);
}

void collision() {
    int displacement = sqrt((cenx1 - cenx2) * (cenx1 - cenx2) + (ceny1 - ceny2) * (ceny1 - ceny2));
    if (displacement <= rad1 + rad2) {
        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        r.w = SCREEN_WIDTH;
        r.h = SCREEN_HEIGHT;

        SDL_SetRenderDrawColor(renderer, 47, 27, 27, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 47, 27, 27, 255);
        SDL_RenderDrawRect(renderer, &r);

        SDL_RenderPresent(renderer);
    }
}

void destroyWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    game_running = initialize_window();

    while (game_running) {
        process_input();
        update();
        render();
        collision();
    }

    destroyWindow();
    return 0;
}
