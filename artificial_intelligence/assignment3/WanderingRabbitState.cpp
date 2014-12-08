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

	}


	return false;
}

void WanderingRabbitState::enter(Rabbit *entity, Game &game)
{
	game.getDrawer().setColorOverLay(entity->getName(), 0, 70, 255);
}

void WanderingRabbitState::update(Rabbit *entity, Game &game)
{
	std::list<Edge*> edges = game.getGraph().getEdges(entity->getField()->getKey());

	Edge *edge = RandomGenerator::randomFromList<Edge*>(edges);

	if (edge != nullptr) {
		Vertex *newPlace = game.getGraph().getVertex(edge->getDestination());

		if (newPlace != nullptr) {
			std::set<GameObject*> objData = newPlace->getData();

			if (objData.size() > 0) {
				//std::cout << "MSG to all objects on vertex: RabbitVisiting" << std::endl;
				for (auto it : objData) {
					Dispatch.dispatchMessage(0.0, entity->getId(), it->getId(), MessageType::Msg_RabbitVisiting, entity);
				}
			}

			newPlace->setData(*entity);
		}

	}
}

void WanderingRabbitState::exit(Rabbit *entity, Game &game)
{

}
