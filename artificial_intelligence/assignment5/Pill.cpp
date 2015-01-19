#include "Pill.h"
#include "GameGeneticInstance.h"
#include "Game.h"
#include "Drawer.h"

Pill::Pill() : Vehicle(new Vector2D(200.0, 400.0), 10.0, new Vector2D(0.0, 0.0), 0.1, 2.0, 150.0, 150.0, 15.0)
{
}


Pill::~Pill()
{
}

void Pill::update(Game &game, const double &time_elapsed) {

	//update the time elapsed
	_time_elapsed = time_elapsed;

	//_stateMachine->update();

	//Vehicle::update(game, time_elapsed);
}

void Pill::draw(Game &game) {
	std::string colorExtendtion = _gameGeneticInstance->getColorExtention();
	game.getDrawer().drawSprite("pill" + colorExtendtion, getPos()->x, getPos()->y);
}