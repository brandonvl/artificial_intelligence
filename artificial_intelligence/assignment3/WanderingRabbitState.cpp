#include "WanderingRabbitState.h"
#include "Rabbit.h"
#include "Graph.h"
#include "Game.h"
#include "Vertex.h"
#include "Edge.h"
#include "RandomGenerator.h"
#include "MessageTypes.h"
#include "MessageDispatcher.h"
#include "Drawer.h"
#include "HighAwarenessRabbitState.h"
#include "EntityManager.h"
#include "Cow.h"
#include <iostream>
#include "AStarSearch.h"

WanderingRabbitState::WanderingRabbitState()
{
}


WanderingRabbitState::~WanderingRabbitState()
{
}

bool WanderingRabbitState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	switch (msg.msg)
	{
	case MessageType::Msg_WeaponUpgrade:
		std::cout << "Weapon replied! Rabbit entering high awareness!" << std::endl;
		entity->changeState(&HighAwarenessRabbitState::instance());
		return true;
	case MessageType::Msg_ChasingCowVisiting:
		std::cout << "The cow caught the rabbit!" << std::endl;
		Dispatch.dispatchMessage(0.0, entity->getId(), static_cast<Cow*>(msg.extraInfo)->getId(), MessageType::Msg_RabbitCaught, nullptr);
		EntityMgr.removeEntity(entity);
		return true;
	case MessageType::Msg_ChasingCowPresent:
		_receivedChasingCowMessage = true;
		return true;
	}


	return false;
}

void WanderingRabbitState::enter(Rabbit *entity, Game &game)
{
	game.getDrawer().setColorOverLay(entity->getName(), 0, 70, 255);
}

void WanderingRabbitState::update(Rabbit *entity, Game &game)
{
	if (!lookAround(entity, game)) {
		wander(entity, game);
	}
}

void WanderingRabbitState::exit(Rabbit *entity, Game &game)
{

}

void WanderingRabbitState::wander(Rabbit *entity, Game &game) {

	// stores the 'safe' fields to move to
	std::vector<int> candidates;

	for (auto edge : game.getGraph().getEdges(entity->getField()->getKey())) {
		auto vertex = game.getGraph().getVertex(entity->getField()->getKey() == edge->getSource() ? edge->getDestination() : edge->getSource());

		if (vertex != nullptr) {
			auto data = vertex->getData();

			// check if there are any game object on the neightbour vector
			if (data.size() > 0) {
				for (auto obj : data) {
					_receivedChasingCowMessage = false;

					Dispatch.dispatchMessage(0.0, entity->getId(), obj->getId(), MessageType::Msg_RabbitPeeking, entity);
					
					// if there is no cow on the next field or one of the fields surrounding the field
					if (!_receivedChasingCowMessage && !isNextToCow(entity, game, vertex->getKey())) {
						candidates.push_back(vertex->getKey());
					}
				}
			}
			else if (!isNextToCow(entity, game, vertex->getKey())) 
				candidates.push_back(vertex->getKey());
		}
	}

	if (candidates.size() > 0) {
		// move to a random available field
		auto newPlace = game.getGraph().getVertex(RandomGenerator::randomFromVector<int>(candidates));
		newPlace->setData(*entity);
	}
	else {
		std::cout << "Rabbit is trapped by the cow\n";
	}

}

bool WanderingRabbitState::lookAround(Rabbit *entity, Game &game) {
	// should the rabbit be scared (is there a cow next to him)
	if (isNextToCow(entity, game, entity->getField()->getKey())) {
		// choose an option based on chances (higher numbers for more likely actions)
		int option = RandomGenerator::chance({ _runChance, _searchWeaponChance, _searchPillChance });

		switch (option) {
		case 0: // run
			std::cout << "Rabbit runs away\n";
			return false;

		case 1: // search weapon
			std::cout << "Going to search for weapon\n";
			break;

		case 2: // search pill
			std::cout << "Going to search for pill\n";
			break;
		}

		return true;
	}

	return false;
}

bool WanderingRabbitState::isNextToCow(Rabbit *entity, Game &game, int fieldKey) {
	_receivedChasingCowMessage = false;

	// Loop trough the vectors in the neightbour edges
	for (auto edge : game.getGraph().getEdges(fieldKey)) {
		auto vertex = game.getGraph().getVertex(fieldKey == edge->getSource() ? edge->getDestination() : edge->getSource());

		if (vertex != nullptr) {
			auto data = vertex->getData();

			// check if there are any game object on the neightbour vector
			if (data.size() > 0) {
				for (auto obj : data) {
					Dispatch.dispatchMessage(0.0, entity->getId(), obj->getId(), MessageType::Msg_RabbitPeeking, entity);

					if (_receivedChasingCowMessage) {
						return true;
					}
				}
			}
		}
	}

	// Relief, no cow next to the field
	return false;
}