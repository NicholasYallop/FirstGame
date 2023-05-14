#include "SDL2/SDL.h"

typedef struct {
	public:
		SDL_Renderer *renderer;
		SDL_Window *window;	
		int up;
		int down;
		int left;
		int right;
} App;

typedef struct {
	int x, y;
	int w, h;
	SDL_Texture *texture;
} Entity;