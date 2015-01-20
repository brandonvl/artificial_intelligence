#include "RabbitWanderState.h"
#include "RabbitFleeState.h"
#include "Cow.h"
#include "Game.h"
#include "Rabbit.h"

#include <iostream>

RabbitWanderState::RabbitWanderState(std::string name) : State(name) {

}

bool RabbitWanderState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	return false;
}

void RabbitWanderState::enter(Rabbit *entity, Game &game)
{
	std::cout << "Rabbit Has Entered Wander" << "\n";
	entity->setMaxSpeed(entity->getWanderSpeed());
}

void RabbitWanderState::update(Rabbit *entity, Game &game)
{
	if (entity->getSteeringBehaviors().isEvadeOn())
		entity->getSteeringBehaviors().evadeOff();

	if (!entity->getSteeringBehaviors().isWanderOn())
		entity->getSteeringBehaviors().wanderOn();

	auto cows = game.getCows();
	double closestCow = 0.0;
	for (size_t i = 0; i < cows.size(); i++)
	{
		double distance = Vec2DDistanceSq(*entity->getPos(), *cows[i]->getPos());
		if (distance < closestCow || closestCow == 0.0)
			closestCow = distance;
	}

	if (closestCow < entity->getPanicDistance())
		entity->getStateMachine().changeState(new RabbitFleeState("RabbitFleeState"));
}

void RabbitWanderState::exit(Rabbit *entity, Game &game)
{
	std::cout << "Rabbit Left Wander" << "\n";
}