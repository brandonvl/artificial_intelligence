#include "RabbitPursuitState.h"
#include "Cow.h"
#include "Game.h"
#include "Rabbit.h"
#include "GameGeneticInstance.h"

#include <iostream>

RabbitPursuitState::RabbitPursuitState(std::string name) : State(name) {

}

bool RabbitPursuitState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	return false;
}

void RabbitPursuitState::enter(Rabbit *entity, Game &game)
{
	entity->setMaxSpeed(entity->getPursuitSpeed());
	std::cout << "Rabbit Entered PursuitState";
}

void RabbitPursuitState::update(Rabbit *entity, Game &game)
{
	if (!entity->getSteeringBehaviors().isPursuitOn())
		entity->getSteeringBehaviors().pursuitOn(&entity->getGeneticInstance()->getCow());
	if (!entity->getSteeringBehaviors().isArriveOn())
		entity->getSteeringBehaviors().arriveOn(&entity->getGeneticInstance()->getCow());


	if (game.getCow().getPos() == entity->getPos())
	{
		// De koe is gevangen en moet gerespawned worden
		game.getCow().setPosition(game.getCowSpawn());
		entity->setPosition(game.getRabbitSpawn());
		entity->addPoints(10);
		std::cout << "The rabbit Caught the Cow, Rabbit has " + std::to_string(entity->getPoints()) + " points.\n";
	}

}

void RabbitPursuitState::exit(Rabbit *entity, Game &game)
{
	std::cout << "Rabbit left PursuitState";
}