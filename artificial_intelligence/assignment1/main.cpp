
#include "SDL.h"
#include <iostream>


int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	std::cin.get();

	SDL_Quit();
	return 0;
}