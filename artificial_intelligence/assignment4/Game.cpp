#include "Game.h"
#include "Drawer.h"
#include "Cow.h"
#include "Rabbit.h"
#include <memory>
#include <list>
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "Vehicle.h"
#include <iostream>

Game::Game()
{
	_drawer = new Drawer("KMINT - Application 4",1024,720);
	_drawer->load("cow", R"(assets/cow.png)");
	_drawer->load("rabbit", R"(assets/rabbit.png)");
	//_testObject = new Vehicle(new Vector2D(100.0, 100.0), 5.0, new Vector2D(1.0, 1.0), 50.0, 100.0, 150.0, 35.0, 25.0);
	//_drawer->load("weapon", R"(assets/weapon.png)");
	//_drawer->load("pill", R"(assets/pill.png)");
	//_drawer->load("gameover", R"(assets/gameover.png)");


	_rabbit = new Rabbit(*this);
	//_rabbit->makeMachine(*this);
	EntityMgr.registerEntity(_rabbit);

	int numberOfCows = 10;
	for (int i = 0; i < numberOfCows; i++)
	{
		Cow *cow = new Cow(*this);
		cow->setPosition(Vector2D(80 * (i + 1), 500));
		_cows.push_back(cow);
		EntityMgr.registerEntity(cow);
	}
}


Game::~Game()
{
	delete _drawer;
}

void Game::stop() {
	_running = false;
}

void Game::run()
{
	_running = true;

	Uint32 oldTime;
	Uint32 curTime = SDL_GetTicks();
	double time_elapsed;

	while (_running) {

		oldTime = curTime;
		curTime = SDL_GetTicks();
		time_elapsed = (curTime - oldTime) / 1000.0;

		Dispatch.dispatchDelayedMessages();
		handleEvents();
		update(time_elapsed);
		draw();
	}
}

void Game::update(const double &time_elapsed)
{
	_rabbit->update(*this, time_elapsed);
	for (size_t i = 0; i < _cows.size(); i++)
		_cows[i]->update(*this, time_elapsed);
}

void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			stop();
	}
}

void Game::draw()
{	
	_drawer->prepareForDraw();
	for (size_t i = 0; i < _cows.size(); i++)
		_cows[i]->draw(*this);
	_rabbit->draw(*this);
	_drawer->render();
}