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

ChasePillRabbitState::ChasePillRabbitState()
{
}


ChasePillRabbitState::~ChasePillRabbitState()
{
}

bool ChasePillRabbitState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	switch (msg.msg)
	{
	case MessageType::Msg_PillUpgrade:
		std::cout << "Pill replied, Rabbit now has pill! Lets wander" << std::endl;
		entity->changeState(&WanderingRabbitState::instance());
		return true;
	}

	return false;
}

void ChasePillRabbitState::enter(Rabbit *entity, Game &game)
{
	clearPath();
	game.getDrawer().setColorOverLay(entity->getName(), 150, 200, 100);
}

void ChasePillRabbitState::update(Rabbit *entity, Game &game)
{
	if (!entity->hadPill()) {

		if (_path.empty()) {
			_path = AStarSearch::getShortestPath(game.getGraph(), entity->getField()->getKey(), game.getPill().getField()->getKey());
		}
		Vertex *newPlace = game.getGraph().getVertex(_path.top()->getKey());
		_path.pop();

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

void ChasePillRabbitState::clearPath()
{
	while (!_path.empty())
		_path.pop();
}

void ChasePillRabbitState::exit(Rabbit *entity, Game &game)
{
	clearPath();
}
