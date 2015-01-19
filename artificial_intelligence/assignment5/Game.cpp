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
#include "GameGeneticInstance.h"

Game::Game()
{
	_drawer = new Drawer("KMINT - Application 5",800,800);
	//_drawer->load("cow", R"(assets/cow.png)");
	//_drawer->load("rabbit", R"(assets/rabbit.png)");
	//_drawer->load("weapon", R"(assets/weapon.png)");
	//_drawer->load("pill", R"(assets/pill.png)");
	//_drawer->load("gameover", R"(assets/gameover.png)");
	loadInstanceColorImages();


	//_rabbit = new Rabbit(*this);
	//_rabbit->makeMachine(*this);
	//EntityMgr.registerEntity(_rabbit);
	//_cow = new Cow(*this);
	//_cow->makeMachine(*this);
	//EntityMgr.registerEntity(_cow);
	_geneticInstance = new GameGeneticInstance(*this, GameGeneticInstanceColor::RED);
	
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
	_geneticInstance->update(*this, time_elapsed);
	//_cow->update(*this, time_elapsed);
	//_rabbit->update(*this, time_elapsed);
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
	_geneticInstance->draw(*this, 0.0);
	_drawer->render();
}

void Game::loadInstanceColorImages() {

	// RED
	_drawer->load("cowRed", R"(assets/cow.png)");
	_drawer->load("rabbitRed", R"(assets/rabbit.png)");
	_drawer->load("weaponRed", R"(assets/weapon.png)");
	_drawer->load("pillRed", R"(assets/pill.png)");

	_drawer->setColorOverLay("cowRed", 255, 0, 0);
	_drawer->setColorOverLay("rabbitRed", 255, 0, 0);
	_drawer->setColorOverLay("weaponRed", 255, 0, 0);
	_drawer->setColorOverLay("pillRed", 255, 0, 0);

	// BLUE
	_drawer->load("cowBlue", R"(assets/cow.png)");
	_drawer->load("rabbitBlue", R"(assets/rabbit.png)");
	_drawer->load("weaponBlue", R"(assets/weapon.png)");
	_drawer->load("pillBlue", R"(assets/pill.png)");

	_drawer->setColorOverLay("cowBlue", 0, 255, 255);
	_drawer->setColorOverLay("rabbitBlue", 0, 255, 255);
	_drawer->setColorOverLay("weaponBlue", 0, 255, 255);
	_drawer->setColorOverLay("pillBlue", 0, 255, 255);

	// GREEN
	_drawer->load("cowGreen", R"(assets/cow.png)");
	_drawer->load("rabbitGreen", R"(assets/rabbit.png)");
	_drawer->load("weaponGreen", R"(assets/weapon.png)");
	_drawer->load("pillGreen", R"(assets/pill.png)");

	_drawer->setColorOverLay("cowGreen", 0, 255, 0);
	_drawer->setColorOverLay("rabbitGreen", 0, 255, 0);
	_drawer->setColorOverLay("weaponGreen", 0, 255, 0);
	_drawer->setColorOverLay("pillGreen", 0, 255, 0);

	// YELLOW
	_drawer->load("cowYellow", R"(assets/cow.png)");
	_drawer->load("rabbitYellow", R"(assets/rabbit.png)");
	_drawer->load("weaponYellow", R"(assets/weapon.png)");
	_drawer->load("pillYellow", R"(assets/pill.png)");

	_drawer->setColorOverLay("cowYellow", 255, 255, 0);
	_drawer->setColorOverLay("rabbitYellow", 255, 255, 0);
	_drawer->setColorOverLay("weaponYellow", 255, 255, 0);
	_drawer->setColorOverLay("pillYellow", 255, 255, 0);
}