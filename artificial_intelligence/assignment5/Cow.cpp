#include "Cow.h"
#include "Game.h"
#include "Drawer.h"
#include "Rabbit.h"
#include "CowPursuitState.h"
#include "GameGeneticInstance.h"

Cow::Cow(Game &game) : Vehicle(new Vector2D(350.0, 200.0), 10.0, new Vector2D(0.0,0.0),0.1,2.0,150.0,150.0,15.0)
{
	setDrawColor(0, 0, 0);
	makeMachine(game);
}

void Cow::makeMachine(Game &game) {
	_stateMachine = new StateMachine<Cow>(this, game);
	_stateMachine->setCurrentState(new CowPursuitState("CowPursuitState"));
}

void Cow::update(Game &game, const double &time_elapsed) {

	//update the time elapsed
	_time_elapsed = time_elapsed;

	//_stateMachine->update();

	//Vehicle::update(game, time_elapsed);
}

void Cow::draw(Game &game) {
	std::string colorExtendtion = _gameGeneticInstance->getColorExtention();
	game.getDrawer().drawSprite("cow" + colorExtendtion, getPos()->x, getPos()->y);
}


Cow::~Cow()
{
}
