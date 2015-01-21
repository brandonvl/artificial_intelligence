#include "Pill.h"
#include "GameGeneticInstance.h"
#include "Game.h"
#include "Drawer.h"

Pill::Pill(Game &game) : Vehicle(new Vector2D(200.0, 400.0), 10.0, new Vector2D(0.0, 0.0), 0.1, 2.0, 150.0, 150.0, 15.0, game)
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
	std::string colorExtention = _geneticInstance->getColorExtention();
	game.getDrawer().drawSprite("pill" + colorExtention, getPos()->x, getPos()->y);
}

void Pill::respawn() {

	int xStart, xEnd, yStart, yEnd;

	int xHalf = _game->getCowSpawn().x / 2;
	int yHalf = _game->getCowSpawn().y / 2;

	xStart = _game->getCowSpawn().x - xHalf;
	xEnd = _game->getCowSpawn().x + xHalf;
	yStart = _game->getCowSpawn().y - yHalf;
	yEnd = _game->getCowSpawn().y + yHalf;

	_game->respawnRandom(this, xStart, xEnd, yStart, yEnd);
}