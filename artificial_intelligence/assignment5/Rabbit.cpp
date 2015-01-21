#include "Rabbit.h"
#include "Cow.h"
#include "Game.h"
#include "Drawer.h"
#include "GameGeneticInstance.h"
#include "RabbitPursuitState.h"

#include <iostream>

Rabbit::Rabbit(Game &game) : Vehicle(new Vector2D(350.0, 600.0), 10.0, new Vector2D(600.0, 600.0), 0.1, 4.0, 600.0, 15.0, 15.0, game)
{
	setDrawColor(255, 0, 0);
	makeMachine(game);
	respawn();
}

void Rabbit::makeMachine(Game &game) {
	_stateMachine = new StateMachine<Rabbit>(this, game);
	_stateMachine->changeState(&RabbitPursuitState::instance());
}

bool Rabbit::handleMessage(const Telegram &msg) {
	return _stateMachine->handleMessage(msg);
}

void Rabbit::update(Game &game, const double &time_elapsed) {

	//update the time elapsed
	_time_elapsed = time_elapsed;

	_stateMachine->update();

	Vehicle::update(game, time_elapsed);
}

void Rabbit::respawn()
{
	setPosition(_game->getRabbitSpawn());
}

void Rabbit::draw(Game &game)  {
	std::string colorExtention = _geneticInstance->getColorExtention();
	game.getDrawer().drawSprite("rabbit" + colorExtention, getPos()->x, getPos()->y);
}


Rabbit::~Rabbit()
{
}
