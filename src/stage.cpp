#include "common.h"

extern App app;
Stage stage;
SDL_Texture *bulletTexture;
Entity *player;

static void fireBullet(void)
{
	Entity *bullet;

	bullet = new Entity();
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->x = player->x;
	bullet->y = player->y;
	bullet->w = BULLET_WIDTH;
	bullet->h = BULLET_HEIGHT;
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->health = 1;
	bullet->texture = bulletTexture;

	bullet->y += (player->h / 2) - (bullet->h / 2);

	player->reload = 8;
}

static void doPlayer(void)
{
	player->dx = player->dy = 0;

	if (player->reload > 0)
	{
		player->reload--;
	}

	if (app.keyboard[SDL_SCANCODE_UP])
	{
		player->dy = -PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_DOWN])
	{
		player->dy = PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		player->dx = -PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT])
	{
		player->dx = PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0)
	{
		fireBullet();
	}

	player->x += player->dx;
	player->y += player->dy;
}

static void doBullets(void)
{
	Entity *b, *prev;

	prev = &stage.bulletHead;

	for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;

		if (b->x > SCREEN_WIDTH)
		{
			// 	all this removes an element from the linked list
			if (b == stage.bulletTail)
			{
				// if b was the first element, set the stage to contain what was first pointed to
				// i.e. make (a {pointer to b}, pointer to b) -> (b {pointer to c}, pointer to b)
				stage.bulletTail = prev;
			}

			// set stage's next pointer to to b's pointer
			// i.e. (b {pointer to c}, pointer to b) -> (b {pointer to c}, pointer to c)
			prev->next = b->next;

			// empty b
			free(b);

			// set b to last
			b = prev;
		}

		// record current value to be referenced as 'prev'
		prev = b;
	}
}

static void logic(void)
{
	doPlayer();

	doBullets();
}

static void drawPlayer(void)
{
	if (!player->h && !player->w){
		blit(player->texture, player->x, player->y);
		return;
	}

	blit(player->texture, player->x, player->y, player->w, player->h);
}

static void drawBullets(void)
{
	Entity *b;

	for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
	{
		if (!b->w && !b->h){
			blit(b->texture, b->x, b->y);
		}
		else{
			blit(b->texture, b->x, b->y, b->w, b->h);
		}
	}
}

static void draw(void)
{
	drawPlayer();

	drawBullets();
}

static void initPlayer()
{
	player = new Entity();
	memset(player, 0, sizeof(Entity));
	stage.fighterTail->next = player;
	stage.fighterTail = player;

	player->x = 100;
	player->y = 100;
	player->w = PLAYER_WIDTH;
	player->h = PLAYER_HEIGHT;
	player->texture = loadTexture("gfx/crash_test_dummy.png");
}

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;

	initPlayer();

	bulletTexture = loadTexture("gfx/gcse.png");
}