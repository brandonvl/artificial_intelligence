#include "CowFleeState.h"
#include "CowWanderState.h"
#include "Cow.h"
#include "Game.h"
#include "Rabbit.h"
#include "SteeringBehaviors.h"
#include "GameGeneticInstance.h"
#include "MessageTypes.h"
#include "MessageDispatcher.h"

#include <iostream>

CowFleeState::CowFleeState() : State("CowFleeState") {

}

bool CowFleeState::onMessage(Cow *entity, const Telegram &msg, Game &game)
{
	if (msg.msg == MessageType::Msg_RabbitVisiting) {
		entity->respawn();
		entity->getGeneticInstance()->getRabbit().addPoints(10);
		entity->getStateMachine().changeState(&CowWanderState::instance());
		
		return true;
	}

	return false;
}

void CowFleeState::enter(Cow *entity, Game &game)
{
	//std::cout << entity->getGeneticInstance()->getColorExtention() << ": Flee \n";
}

void CowFleeState::update(Cow *entity, Game &game)
{
	if (entity->getSteeringBehaviors().isWanderOn())
		entity->getSteeringBehaviors().wanderOff();

	if (!entity->getSteeringBehaviors().isFleeOn())
		entity->getSteeringBehaviors().fleeOn(&entity->getGeneticInstance()->getRabbit());

}

void CowFleeState::exit(Cow *entity, Game &game)
{
	entity->getSteeringBehaviors().resetBehavior();
}