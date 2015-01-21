#include "CowChaseWeaponState.h"
#include "Cow.h"
#include "Rabbit.h"
#include "Weapon.h"
#include "GameGeneticInstance.h"
#include "SteeringBehaviors.h"
#include "MessageTypes.h"
#include "MessageDispatcher.h"
#include "CowWanderState.h"

#include <iostream>

CowChaseWeaponState::CowChaseWeaponState() : State("CowChaseWeaponState")
{
}

bool CowChaseWeaponState::onMessage(Cow *entity, const Telegram &msg, Game &game)
{
	if (msg.msg == MessageType::Msg_RabbitVisiting) {
		if (!entity->hasWeapon())
			entity->getGeneticInstance()->getRabbit().addPoints(10);

		entity->getStateMachine().changeState(&CowWanderState::instance());
		entity->respawn();
		
		return true;
	}

	return false;
}

void CowChaseWeaponState::enter(Cow *entity, Game &game)
{
	//std::cout << entity->getGeneticInstance()->getColorExtention() << ": Weapon seek \n";
	entity->setWeapon(false);
}

void CowChaseWeaponState::update(Cow *entity, Game &game)
{
	if (!entity->hasWeapon()) {
		if (entity->getSteeringBehaviors().isWanderOn())
			entity->getSteeringBehaviors().wanderOff();

		/*if (!entity->getSteeringBehaviors().isFleeOn())
			entity->getSteeringBehaviors().fleeOn(&entity->getGeneticInstance()->getRabbit());*/

		if (!entity->getSteeringBehaviors().isPursuitOn())
			entity->getSteeringBehaviors().pursuitOn(&entity->getGeneticInstance()->getWeapon());

		if (Vec2DDistance(*entity->getPos(), *entity->getGeneticInstance()->getWeapon().getPos()) < 10) {
			entity->getGeneticInstance()->respawnWeapon();
			entity->setWeapon();
			entity->getVelocity()->Zero();
			entity->getSteeringBehaviors().resetBehavior();
		}
	}

}

void CowChaseWeaponState::exit(Cow *entity, Game &game)
{
	entity->getSteeringBehaviors().resetBehavior();
	entity->setWeapon(false);
}
