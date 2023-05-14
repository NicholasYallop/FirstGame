#include "common.h"

App app = App();
Entity player = Entity();

int main(void){
    memset(&app, 0, sizeof(App)); // empties the memory occupied by the app variable
	memset(&player, 0, sizeof(Entity));

	initSDL();

	player.texture = loadTexture("gfx/crash_test_dummy.png");
	player.x = 100;
	player.y = 100;
	player.w = 100;
	player.h = 100;

	//TODO: collect garbage
	//atexit(cleanup);

	while (1)
	{
		prepareScene();

		doInput();

		if (app.up)
		{
			player.y -= 4;
		}

		if (app.down)
		{
			player.y += 4;
		}

		if (app.left)
		{
			player.x -= 4;
		}

		if (app.right)
		{
			player.x += 4;
		}

		blit(player.texture, player.x, player.y, player.w, player.h);

		presentScene();

		SDL_Delay(16);
	}

	return 0;
}