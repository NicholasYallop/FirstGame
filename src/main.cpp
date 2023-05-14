#include "common.h"

App app = App();
Entity player = Entity();

int main(void){
    memset(&app, 0, sizeof(App)); // empties the memory occupied by the app variable
	memset(&player, 0, sizeof(Entity));

	initSDL();

	player.x = 100;
	player.y = 100;
	player.texture = loadTexture("gfx/crash_test_dummy.png");

	SDL_Rect displayRect = SDL_Rect();
	displayRect.x = 100;
	displayRect.y = 100;
	displayRect.w = 100;
	displayRect.h = 100;

	//TODO: collect garbage
	//atexit(cleanup);

	while (1)
	{
		prepareScene();

		doInput();

		blit(player.texture, player.x, player.y, &displayRect);

		presentScene();

		SDL_Delay(16);
	}

	return 0;
}