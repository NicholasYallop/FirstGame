#include "common.h"

App app = App();

int main(void){
    //memset(&app, 0, sizeof(App));

	initSDL();

	//atexit(cleanup);

	while (1)
	{
		prepareScene();

		doInput();

		presentScene();

		SDL_Delay(16);
	}

	return 0;
}