#include "RabbitFleeState.h"
#include "Cow.h"
#include "Game.h"
#include "Rabbit.h"
#include "RabbitWanderState.h"

#include <iostream>

RabbitFleeState::RabbitFleeState(std::string name) : State(name) {

}

bool RabbitFleeState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	return false;
}

void RabbitFleeState::enter(Rabbit *entity, Game &game)
{
	std::cout << "Rabbit Has Entered FleeState \n";
	entity->setMaxSpeed(entity->getFleeSpeed());
}

void RabbitFleeState::update(Rabbit *entity, Game &game)
{
	if (entity->getSteeringBehaviors().isWanderOn())
		entity->getSteeringBehaviors().wanderOff();
	
	auto cows = game.getCows();
	double closestCow = 0.0;
	int cowID = 0;
	for (size_t i = 0; i < cows.size(); i++)
	{
		double distance = Vec2DDistanceSq(*entity->getPos(), *cows[i]->getPos());
		if (distance < closestCow || closestCow == 0.0)
		{
			cowID = i;
			closestCow = distance;
		}
	}

	if (closestCow < entity->getPanicDistance())
		entity->getSteeringBehaviors().evadeOn(cows[cowID], entity->getPanicDistance());

	if (closestCow > entity->getSafeDistance())
		entity->getStateMachine().changeState(new RabbitWanderState("RabbitWanderState"));
}

void RabbitFleeState::exit(Rabbit *entity, Game &game)
{
	std::cout << "Rabbit Left Entered FleeState \n";
}