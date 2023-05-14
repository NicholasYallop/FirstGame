#include "SDL2/SDL.h"

typedef struct {
	public:
		// SDL components
		SDL_Renderer *renderer;
		SDL_Window *window;

		// input flags	
		int up;
		int down;
		int left;
		int right;
		int fire;
} App;

typedef struct {
	int x, y;
	int w, h;
	int dx;
	int dy;
	int health;
	SDL_Texture *texture;
} Entity;