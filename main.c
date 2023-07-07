#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// WINDOW_W is preferable to set to the powers of 3: 1, 9, 27, 81, 243, 729, 2187
// In this way you will get precise drawing, the screen gets fully painted after
// input steps greater than 'MAX_STEPS'. Change it to produce the desired result.
// REMEMBER on 8 steps, the program has to draw 5380839 cubes, not so efficient,
// it just an educational demonstration.
#define WINDOW_W 729
#define WINDOW_H WINDOW_W
#define WINDOW_FLAGS SDL_WINDOW_SHOWN
#define RENDER_FLAGS SDL_RENDERER_ACCELERATED
#define MAX_STEPS 8

SDL_Window *w;
SDL_Renderer *r;
SDL_Event e;
SDL_Rect *cube;

void render_carpet(int step);
void fill_tile(int x1, int y1, int x2, int y2);
void render_tile(int x1, int y1, int x2, int y2);

SDL_Rect *create_cube(int x, int y, int w, int h);

int main()
{
  int steps;
  printf("Enter steps = ");
  scanf("%d", &steps);

  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("INIT ERROR: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  w = SDL_CreateWindow(
    "Sierpinski Carpet",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WINDOW_W, WINDOW_H,
    WINDOW_FLAGS
  );

  r = SDL_CreateRenderer( w, -1, RENDER_FLAGS);

  // Main Part
  SDL_SetRenderDrawColor(r, 5, 32, 74, 255);
  SDL_Rect *bg = create_cube(0, 0, WINDOW_W, WINDOW_H);
  SDL_RenderFillRect(r, bg);
  render_carpet(steps);

  while (1) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:
          SDL_DestroyRenderer(r);
          SDL_DestroyWindow(w);
          return EXIT_SUCCESS;
        default: {}
      }
    }
  }

  free(cube);
  SDL_DestroyRenderer(r);
  SDL_DestroyWindow(w);

  return EXIT_SUCCESS;
}

void render_carpet(int steps)
{
  if (steps <= 0) {
    printf("! STEPS <= 0 !\n");
    return;
  }

  SDL_SetRenderDrawColor(r, 242, 239, 230, 255);
  cube = create_cube(0, 0, WINDOW_W, WINDOW_H);

  if (steps > MAX_STEPS) {
    SDL_RenderFillRect(r, cube);
    free(cube);
  } else {
    fill_tile(0, 0, WINDOW_W, WINDOW_H);
    // printf("WINDOW SIZE: %dx%d\n", WINDOW_W, WINDOW_H);
    // printf("STEPS = 1, CUBES = 1, TILE_W = %d, TILE_H = %d", WINDOW_W, WINDOW_H);
    for (int i = 1; i < steps; i++) {
      // int n = (int)pow(3, i * 2);
      int tile_w = WINDOW_W / (int)pow(3, i);
      int tile_h = WINDOW_H / (int)pow(3, i);
      // printf("STEPS = %d, CUBES = %d, TILE_W = %d, TILE_H = %d\n", i + 1, n, tile_w, tile_h);
      for (int j = 0; j < (int)pow(3, i); j += 1) {
        for (int k = 0; k < (int)pow(3, i); k += 1) {
          fill_tile(
              j * tile_w,           // x1
              k * tile_h,           // y1
              tile_w * j + tile_w,  // x2
              tile_h * k + tile_h   // y2
          );
        }
      }
    }
  }

  SDL_RenderPresent(r);
}

// Draws cube inside the tile
void fill_tile(int x1, int y1, int x2, int y2)
{
  double w = ceil((x2 - x1) / 3);
  double h = ceil((y2 - y1) / 3);
  cube->x = x1 + (int)w;
  cube->y = y1 + (int)h;
  cube->w = (int)w;
  cube->h = (int)h;
  SDL_RenderFillRect(r, cube);
}

SDL_Rect *create_cube(int x, int y, int w, int h)
{
  SDL_Rect *cube = (SDL_Rect *)malloc(sizeof(SDL_Rect));
  cube->x = x;
  cube->y = y;
  cube->w = w;
  cube->h = h;
  return cube;
}





