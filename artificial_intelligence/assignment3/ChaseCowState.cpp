#include "ChaseCowState.h"
#include "Cow.h"
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
#include "Rabbit.h"
#include "WanderingCowState.h"

ChaseCowState::ChaseCowState()
{
}


ChaseCowState::~ChaseCowState()
{
}

bool ChaseCowState::onMessage(Cow *entity, const Telegram &msg, Game &game)
{
	switch (msg.msg)
	{
		case MessageType::Msg_RabbitPeeking:
			Dispatch.dispatchMessage(0.0, entity->getId(), msg.sender, MessageType::Msg_ChasingCowPresent, nullptr);
			return true;
		case MessageType::Msg_RabbitCaught:
			std::cout << "Cow is almighty, reverting to wandering!" << std::endl;
			//entity->setPillUpgrade(false);
			entity->changeState(&WanderingCowState::instance());
			return true;
	}

	return false;
}

void ChaseCowState::enter(Cow *entity, Game &game)
{
	clearPath();
	game.getDrawer().setColorOverLay(entity->getName(), 255, 0, 0);
}

void ChaseCowState::update(Cow *entity, Game &game)
{
	// Get the sortest path to the rabbit
	if (_path.empty()) {
		_path = AStarSearch::getShortestPath(game.getGraph(), entity->getField()->getKey(), game.getRabbit().getField()->getKey());
	}

	// Determine the new position for the cow
	Vertex *newPlace = game.getGraph().getVertex(_path.top()->getKey());
	_path.pop();

	// Let the cow visit the new location
	if (newPlace != nullptr) {
		std::set<GameObject*> objData = newPlace->getData();

		if (objData.size() > 0) {
			//std::cout << "MSG to all objects on vertex: CowVisiting" << std::endl;
			for (auto it : objData) {
				Dispatch.dispatchMessage(0.0, entity->getId(), it->getId(), MessageType::Msg_ChasingCowVisiting, entity);
			}
		}

		newPlace->setData(*entity);
	}

}

void ChaseCowState::clearPath()
{
	while (!_path.empty())
		_path.pop();
}

void ChaseCowState::exit(Cow *entity, Game &game)
{
	clearPath();
}
