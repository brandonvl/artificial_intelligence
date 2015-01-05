#include "ChasePillRabbitState.h"
#include "Rabbit.h"
#include <set>
#include <list>
#include "Game.h"
#include "RandomGenerator.h"
#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"
#include "Drawer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "AStarSearch.h"
#include "Pill.h"
#include "WanderingRabbitState.h"
#include "Cow.h"

ChasePillRabbitState::ChasePillRabbitState() : State<Rabbit>("ChasePillRabbitState")
{
}


ChasePillRabbitState::~ChasePillRabbitState()
{
}

bool ChasePillRabbitState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	return false;
}

void ChasePillRabbitState::enter(Rabbit *entity, Game &game)
{
	game.getDrawer().setColorOverLay(entity->getName(), 150, 200, 100);
}

void ChasePillRabbitState::update(Rabbit *entity, Game &game)
{
	if (!entity->hasPill()) {

		std::stack<Vertex*> path = AStarSearch::getShortestPath(game.getGraph(), entity->getField()->getKey(), game.getPill().getField()->getKey(), &game.getCow());

		Vertex *newPlace = game.getGraph().getVertex(path.top()->getKey());

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
	else
		entity->changeState(&ChasePillRabbitState::instance());

}

void ChasePillRabbitState::exit(Rabbit *entity, Game &game)
{
}
