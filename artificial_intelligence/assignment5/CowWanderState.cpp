#include "CowWanderState.h"
#include "CowFleeState.h"
#include "CowHideState.h"
#include "CowChaseWeaponState.h"
#include "CowChasePillState.h"
#include "Cow.h"
#include "Game.h"
#include "Rabbit.h"
#include "SteeringBehaviors.h"
#include "GameGeneticInstance.h"
#include "RandomGenerator.h"
#include "MessageTypes.h"
#include "MessageDispatcher.h"

#include <iostream>

CowWanderState::CowWanderState() : State("CowWanderState") {

}

void CowWanderState::chooseOption(Cow *entity, Game &game) {
	int option = RandomGenerator::chance({ entity->getFleeChance(), entity->getSeekPillChance(), entity->getHideChance(), entity->getSeekWeaponChance() });

	switch (option) {
	case 0: // flee
		entity->getStateMachine().changeState(&CowFleeState::instance());
		break;
	case 1: // seek pill & flee
		entity->getStateMachine().changeState(&CowChasePillState::instance());
		break;
	case 2: // hide
		entity->getStateMachine().changeState(&CowHideState::instance());
		break;
	case 3: // seek weapon & flee
		entity->getStateMachine().changeState(&CowChaseWeaponState::instance());
		break;
	}
}

bool CowWanderState::onMessage(Cow *entity, const Telegram &msg, Game &game)
{
	return false;
}

void CowWanderState::enter(Cow *entity, Game &game)
{

}

void CowWanderState::update(Cow *entity, Game &game)
{
	if (!entity->getSteeringBehaviors().isWanderOn())
		entity->getSteeringBehaviors().wanderOn();

	if (Vec2DDistance(*entity->getPos(), *entity->getGeneticInstance()->getRabbit().getPos()) <= 300) {
		chooseOption(entity, game);
	}

}

void CowWanderState::exit(Cow *entity, Game &game)
{

}