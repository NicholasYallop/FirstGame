#include "common.h"

extern App app;
static Stage stage;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static Entity *player;
float enemySpawnTimer;

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

static int bulletHitFighter(Entity *b)
{
	Entity *e;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
		if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
		{
			b->health = 0;
			e->health = 0;

			return 1;
		}
	}

	return 0;
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
}

static void doBullets(void)
{
	Entity *b, *prev;

	prev = &stage.bulletHead;

	for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;

		if (bulletHitFighter(b) || b->x > SCREEN_WIDTH)
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

static void doFighters(void)
{
	Entity *e, *prev;

	prev = &stage.fighterHead;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;

		if (e != player && (e->x < -e->w || e->health == 0))
		{
			if (e == stage.fighterTail)
			{
				stage.fighterTail = prev;
			}
		
			prev->next = e->next;
			free(e);
			e = prev;
		}
		
		prev = e;
	}
}

static void spawnEnemies(void)
{
	Entity *enemy;

	if (--enemySpawnTimer <= 0)
	{
		enemy = new Entity();
		stage.fighterTail->next = enemy;
		stage.fighterTail = enemy;

		enemy->x = SCREEN_WIDTH;
		enemy->y = rand() % SCREEN_HEIGHT;
		enemy->w = ENEMY_WIDTH;
		enemy->h = ENEMY_HEIGHT;
		enemy->health = 1;
		enemy->side = SIDE_ALIEN;
		enemy->texture = enemyTexture;

		enemy->dx = -(2 + (rand() % 4));

		enemySpawnTimer = 30 + (rand() % 60);
	}
}

static void logic(void)
{
	doPlayer();

	doFighters();

	doBullets();

	spawnEnemies();
}

static void drawFighters(void)
{
	Entity *e;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
		if (!e->h || !e->w){
			blit(e->texture, e->x, e->y);
		}
		else{
			blit(e->texture, e->x, e->y, e->w, e->h);
		}
	}
}

static void drawBullets(void)
{
	Entity *b;

	for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
	{
		if (!b->w || !b->h){
			blit(b->texture, b->x, b->y);
		}
		else{
			blit(b->texture, b->x, b->y, b->w, b->h);
		}
	}
}

static void draw(void)
{
	drawFighters();

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
	player->side = SIDE_PLAYER;
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
	enemyTexture = loadTexture("gfx/eye_test.jpg");

	enemySpawnTimer = 0;
}