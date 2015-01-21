#include "RunRabbitState.h"
#include "Rabbit.h"
#include "Graph.h"
#include "Game.h"
#include "Vertex.h"
#include "Edge.h"
#include "RandomGenerator.h"
#include "MessageTypes.h"
#include "MessageDispatcher.h"
#include "Drawer.h"
#include "EntityManager.h"
#include "Cow.h"
#include <iostream>
#include "AStarSearch.h"
#include "ChasePillRabbitState.h"
#include "ChaseWeaponRabbitState.h"
#include "ChaseCowRabbitState.h"
#include "WanderingRabbitState.h"

RunRabbitState::RunRabbitState() : State("RunRabbitState")
{
}


RunRabbitState::~RunRabbitState()
{
}

bool RunRabbitState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	switch (msg.msg)
	{
	case MessageType::Msg_ChasingCowVisiting:
		entity->updateRunChance(false);
		return true;
	case MessageType::Msg_CowPresent:
		_receivedChasingCowMessage = true;
		return true;
	}


	return false;
}

void RunRabbitState::enter(Rabbit *entity, Game &game)
{
	game.getDrawer().setColorOverLay(entity->getName(), 0, 70, 255);
}

void RunRabbitState::update(Rabbit *entity, Game &game)
{
	if (!lookAround(entity, game)) {
		run(entity, game);
	}
}

void RunRabbitState::exit(Rabbit *entity, Game &game)
{

}

void RunRabbitState::run(Rabbit *entity, Game &game) {

	// stores the 'safe' fields to move to
	std::vector<int> candidates, alternatives;

	for (auto &edge : game.getGraph().getEdges(entity->getField()->getKey())) {
		auto vertex = game.getGraph().getVertex(edge->getDestination());// game.getGraph().getVertex(entity->getField()->getKey() == edge->getSource() ? edge->getDestination() : edge->getSource());

		if (vertex != nullptr) {
			auto data = vertex->getData();

			// check if there are any game object on the neightbour vector
			if (data.size() > 0) {
				for (auto &obj : data) {
					_receivedChasingCowMessage = false;

					Dispatch.dispatchMessage(0.0, entity->getId(), obj->getId(), MessageType::Msg_RabbitPeeking, entity);

					// if there is no cow on the next field or one of the fields surrounding the field
					if (!_receivedChasingCowMessage) {
						if (!isNextToCow(entity, game, vertex->getKey())) candidates.push_back(vertex->getKey());
						else alternatives.push_back(vertex->getKey());
					}
				}
			}
			else if (!isNextToCow(entity, game, vertex->getKey())) candidates.push_back(vertex->getKey());
			else alternatives.push_back(vertex->getKey());
		}
	}

	if (candidates.size() > 0 || alternatives.size() > 0) {
		// move to a random available field
		auto newPlace = game.getGraph().getVertex(RandomGenerator::randomFromVector<int>(candidates.size() > 0 ? candidates : alternatives));

		auto data = std::set<GameObject*>(newPlace->getData());
		for (auto &obj : data) {

			// Crash: Pill/Weapon upgrade (object) is removed
			Dispatch.dispatchMessage(0.0, entity->getId(), obj->getId(), MessageType::Msg_RabbitVisiting, entity);
		}

		newPlace->setData(*entity);
	}
	else {
		std::cout << "Rabbit is trapped by the cow\n";
	}

}

bool RunRabbitState::lookAround(Rabbit *entity, Game &game) {
	// should the rabbit be scared (is there a cow next to him)
	if (!isNextToCow(entity, game, entity->getField()->getKey())) {
		entity->updateRunChance(true);
		entity->changeState(&WanderingRabbitState::instance());
		entity->update(game);
	}

	return false;
}

bool RunRabbitState::isNextToCow(Rabbit *entity, Game &game, int fieldKey) {
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