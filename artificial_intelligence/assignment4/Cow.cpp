#include "Cow.h"
#include "Game.h"
#include "Drawer.h"
#include "Rabbit.h"
#include "CowPursuitState.h"
//#include "SteeringBehaviors.h"

Cow::Cow(Game &game) : Vehicle(new Vector2D(100.0, 50.0), 10.0, new Vector2D(0.0, 0.0), 0.1, 4.0, 150.0, 150.0, 15.0, &game)
{
	setDrawColor(0, 0, 0);
	makeMachine(game);
	_behaviors.setCalculateType(SteeringBehaviors::CalculateType::Priority);
}

void Cow::makeMachine(Game &game) {
	_stateMachine = new StateMachine<Cow>(this, game);
	_stateMachine->setCurrentState(new CowPursuitState("CowPursuitState"));
}

void Cow::update(Game &game, const double &time_elapsed) {

	//update the time elapsed
	_time_elapsed = time_elapsed;

	_stateMachine->update();

	Vehicle::update(game, time_elapsed);
}


Cow::~Cow()
{
}
