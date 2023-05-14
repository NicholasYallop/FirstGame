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

	//TODO: collect garbage
	//atexit(cleanup);

	while (1)
	{
		prepareScene();

		doInput();

		blit(player.texture, player.x, player.y);

		presentScene();

		SDL_Delay(16);
	}

	return 0;
}