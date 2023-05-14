#include "SDL2/SDL.h"

typedef struct {
	public:
		SDL_Renderer *renderer;
		SDL_Window *window;
} App;

typedef struct {
	int x;
	int y;
	SDL_Texture *texture;
} Entity;