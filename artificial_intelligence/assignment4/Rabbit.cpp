#include "Rabbit.h"
#include "Cow.h"
#include "Game.h"
#include "Drawer.h"
#include "RabbitWanderState.h"

Rabbit::Rabbit(Game &game) : Vehicle(new Vector2D(350.0, 350.0), 10.0, new Vector2D(0.0, 0.0), 0.1, 4.0, 150.0, 15.0, 15.0, &game)
{
	setDrawColor(255, 0, 0);
	makeMachine(game);
	_behaviors.setCalculateType(SteeringBehaviors::CalculateType::Weighted);
}

void Rabbit::makeMachine(Game &game) {
	_stateMachine = new StateMachine<Rabbit>(this, game);
	_stateMachine->setCurrentState(new RabbitWanderState("RabbitWanderState"));
}

void Rabbit::update(Game &game, const double &time_elapsed) {

	//update the time elapsed
	_time_elapsed = time_elapsed;

	_stateMachine->update();

	Vehicle::update(game, time_elapsed);
}


Rabbit::~Rabbit()
{
}
