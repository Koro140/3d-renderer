#include "app.h"
#include "render.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

// the global instance of the app
SDL_Window* global_window = NULL;
SDL_Renderer* global_renderer = NULL;
SDL_Event global_event = {0};
bool app_init(int width, int height, const char* name) {
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
	printf("SDL Error: %s", SDL_GetError());
	exit(1);
  }
  
  SDL_Window* window =  SDL_CreateWindow("Hello window", width, height, SDL_WINDOW_OPENGL);
  if (window == NULL) {
	printf("SDL Error: %s", SDL_GetError());
	exit(1);
  }
  
  SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
 if (renderer == NULL) {
	printf("SDL Error: %s", SDL_GetError());
	exit(1);
  }
  
  // initializing subsystems
  render_init(renderer);

  global_window = window;
  global_renderer = renderer;
  
}

bool app_should_close() {
  SDL_PollEvent(&global_event);
  switch(global_event.type) {
  case SDL_EVENT_QUIT:
    return true;
    break;
  }
  
}

void app_quit() {
  SDL_DestroyRenderer(global_renderer);
  SDL_DestroyWindow(global_window);
  SDL_Quit();  
}
