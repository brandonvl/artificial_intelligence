#include "SDL.h"
#include <iostream>
#include "Game.h"

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	Game *game = new Game();
	game->run();
	delete game;
	SDL_Quit();

	return 0;
}

