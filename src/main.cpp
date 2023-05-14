#include "common.h"

App app = App();
Entity player = Entity();
Entity bullet = Entity();

int main(void){
    memset(&app, 0, sizeof(App)); // empties the memory occupied by the app variable
	memset(&player, 0, sizeof(Entity));
	memset(&bullet, 0, sizeof(Entity));

	initSDL();

	player.texture = loadTexture("gfx/crash_test_dummy.png");
	player.x = 100;
	player.y = 100;
	player.w = 100;
	player.h = 100;

	bullet.texture = loadTexture("gfx/gcse.png");
	bullet.x = 100;
	bullet.y = 100;
	bullet.w = 10;
	bullet.h = 10;

	//TODO: collect garbage
	//atexit(cleanup);

	while (1)
	{
		prepareScene();

		doInput();

		player.x += player.dx;
		player.y += player.dy;

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

		if (app.fire && bullet.health == 0)
		{
			bullet.x = player.x;
			bullet.y = player.y;
			bullet.dx = 16;
			bullet.dy = 0;
			bullet.health = 1;
		}

		bullet.x += bullet.dx;
		bullet.y += bullet.dy;

		if (bullet.x > SCREEN_WIDTH)
		{
			bullet.health = 0;
		}

		blit(player.texture, player.x, player.y, player.w, player.h);

		if (bullet.health > 0)
		{
			blit(bullet.texture, bullet.x, bullet.y, bullet.w, bullet.h);
		}
		presentScene();

		SDL_Delay(16);
	}

	return 0;
}