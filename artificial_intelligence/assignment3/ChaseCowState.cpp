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
#include "SleepingCowState.h"

ChaseCowState::ChaseCowState() : State<Cow>("ChaseCowState")
{
}


ChaseCowState::~ChaseCowState()
{
}

bool ChaseCowState::onMessage(Cow *entity, const Telegram &msg, Game &game)
{
	switch (msg.msg)
	{
		case MessageType::Msg_RabbitCaught:
			//std::cout << "Cow is almighty, rabbit caught!" << std::endl;
			return true;
		case MessageType::Msg_CowSleep:
			entity->changeState(&SleepingCowState::instance());
			return true;
	}

	return false;
}

void ChaseCowState::enter(Cow *entity, Game &game)
{
	game.getDrawer().setColorOverLay(entity->getName(), 255, 0, 0);
}

void ChaseCowState::update(Cow *entity, Game &game)
{
	// Get the sortest path to the rabbit
	std::stack<Vertex*> path = AStarSearch::getShortestPath(game.getGraph(), entity->getField()->getKey(), game.getRabbit().getField()->getKey());

	Vertex *newPlace;
	if (!path.empty()) newPlace = game.getGraph().getVertex(path.top()->getKey());
	else newPlace = game.getGraph().getVertex(RandomGenerator::randomFromList<Edge*>(game.getGraph().getEdges(entity->getField()->getKey()))->getDestination());

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

void ChaseCowState::exit(Cow *entity, Game &game)
{
}
