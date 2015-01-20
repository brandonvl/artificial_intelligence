#include "CowPursuitState.h"
#include "Cow.h"
#include "Game.h"
#include "Rabbit.h"

#include <iostream>

CowPursuitState::CowPursuitState(std::string name) : State(name) {

}

bool CowPursuitState::onMessage(Cow *entity, const Telegram &msg, Game &game)
{
	return false;
}

void CowPursuitState::enter(Cow *entity, Game &game)
{
	std::cout << "Cow is almighty";
}

void CowPursuitState::update(Cow *entity, Game &game)
{
	
	if (!entity->getSteeringBehaviors().isPursuitOn())
		entity->getSteeringBehaviors().pursuitOn(&game.getRabbit());
	if (!entity->getSteeringBehaviors().isArriveOn())
		entity->getSteeringBehaviors().arriveOn(&game.getRabbit());

	/*if (!entity->getSteeringBehaviors().isWanderOn())
		entity->getSteeringBehaviors().wanderOn();*/


	if (!entity->getSteeringBehaviors().isSeparationOn())
		entity->getSteeringBehaviors().separationOn();
	if (!entity->getSteeringBehaviors().isAlignmentOn())
		entity->getSteeringBehaviors().alignmentOn();
	if (!entity->getSteeringBehaviors().isCohesionOn())
		entity->getSteeringBehaviors().cohesionOn();


}

void CowPursuitState::exit(Cow *entity, Game &game)
{
	std::cout << "Cow has lost his divinity";
}