#include "RabbitPursuitState.h"
#include "Cow.h"
#include "Game.h"
#include "Rabbit.h"
#include "GameGeneticInstance.h"
#include "MessageTypes.h"
#include "MessageDispatcher.h"

#include <iostream>

RabbitPursuitState::RabbitPursuitState() : State("RabbitPursuitState") {

}

bool RabbitPursuitState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	return false;
}

void RabbitPursuitState::enter(Rabbit *entity, Game &game)
{

}

void RabbitPursuitState::update(Rabbit *entity, Game &game)
{
	if (!entity->getSteeringBehaviors().isPursuitOn())
		entity->getSteeringBehaviors().pursuitOn(&entity->getGeneticInstance()->getCow());
	/*if (!entity->getSteeringBehaviors().isArriveOn())
		entity->getSteeringBehaviors().arriveOn(&entity->getGeneticInstance()->getCow());*/


	if (Vec2DDistance(*entity->getGeneticInstance()->getCow().getPos(),*entity->getPos()) <= 10)
	{
		Dispatch.dispatchMessage(0.0, entity->getId(), entity->getGeneticInstance()->getCow().getId(), MessageType::Msg_RabbitVisiting, entity);
		entity->respawn();
	}

}

void RabbitPursuitState::exit(Rabbit *entity, Game &game)
{

}