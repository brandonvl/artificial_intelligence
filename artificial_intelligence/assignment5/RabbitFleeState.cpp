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

	if (!entity->getSteeringBehaviors().isEvadeOn())
		entity->getSteeringBehaviors().evadeOn(&game.getCow(),entity->getPanicDistance());

	if (Vec2DDistanceSq(*entity->getPos(), *game.getCow().getPos()) > entity->getSafeDistance())
		entity->getStateMachine().changeState(new RabbitWanderState("RabbitWanderState"));


	// Als koe dichtbij is
	
}

void RabbitFleeState::exit(Rabbit *entity, Game &game)
{
	std::cout << "Rabbit Left Entered FleeState \n";
}