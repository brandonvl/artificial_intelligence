#include "CowChasePillState.h"
#include "Cow.h"
#include "Pill.h"
#include "Rabbit.h"
#include "SteeringBehaviors.h"
#include "GameGeneticInstance.h"
#include "MessageTypes.h"
#include "MessageDispatcher.h"
#include "CowWanderState.h"

#include <iostream>

CowChasePillState::CowChasePillState() : State("CowChasePillState")
{
}

bool CowChasePillState::onMessage(Cow *entity, const Telegram &msg, Game &game)
{
	if (msg.msg == MessageType::Msg_RabbitVisiting) {
		if (!entity->hasPill()) {
			entity->getGeneticInstance()->getRabbit().addPoints(10);
			entity->getStateMachine().changeState(&CowWanderState::instance());
		}
		else
			entity->addPoints(1);

		entity->respawn();

		std::cout << entity->getGeneticInstance()->getColorExtention() << ": Pill or do seek \n";
		return true;
	}

	return false;
}

void CowChasePillState::enter(Cow *entity, Game &game)
{
	entity->setPill(false);
}

void CowChasePillState::update(Cow *entity, Game &game)
{
	if (!entity->hasPill()) {
		if (entity->getSteeringBehaviors().isWanderOn())
			entity->getSteeringBehaviors().wanderOff();

		if (!entity->getSteeringBehaviors().isFleeOn())
			entity->getSteeringBehaviors().fleeOn(&entity->getGeneticInstance()->getRabbit());

		if (!entity->getSteeringBehaviors().isPursuitOn())
			entity->getSteeringBehaviors().pursuitOn(&entity->getGeneticInstance()->getPill());

		if (Vec2DDistance(*entity->getPos(), *entity->getGeneticInstance()->getPill().getPos()) < 10) {
			entity->getGeneticInstance()->respawnPill();
			entity->setInvulnerable();
			entity->setPill();
			entity->getVelocity()->Zero();
			entity->getSteeringBehaviors().fleeOff();
			entity->getSteeringBehaviors().pursuitOff();
			entity->getSteeringBehaviors().wanderOff();
		}
	}
}

void CowChasePillState::exit(Cow *entity, Game &game)
{
	entity->setPill(false);
}
