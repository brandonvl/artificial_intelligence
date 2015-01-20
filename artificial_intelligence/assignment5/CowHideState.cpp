#include "CowHideState.h"
#include "Cow.h"
#include "Rabbit.h"
#include "SteeringBehaviors.h"
#include "GameGeneticInstance.h"
#include "MessageTypes.h"
#include "MessageDispatcher.h"
#include "CowWanderState.h"

#include <iostream>

CowHideState::CowHideState() : State("CowHideState")
{
}


bool CowHideState::onMessage(Cow *entity, const Telegram &msg, Game &game)
{
	if (msg.msg == MessageType::Msg_RabbitVisiting) {
		entity->respawn();
		entity->getStateMachine().changeState(&CowWanderState::instance());
		std::cout << entity->getGeneticInstance()->getColorExtention() << ": Hide \n";
		return true;
	}

	return false;
}

void CowHideState::enter(Cow *entity, Game &game)
{
	entity->getVelocity()->Zero();
}

void CowHideState::update(Cow *entity, Game &game)
{
	if (entity->getSteeringBehaviors().isWanderOn())
		entity->getSteeringBehaviors().wanderOff();

}

void CowHideState::exit(Cow *entity, Game &game)
{

}
