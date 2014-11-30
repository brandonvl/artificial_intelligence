#include "WanderingCowState.h"
#include "ChaseCowState.h"
#include "Game.h"
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "RandomGenerator.h"
#include "Cow.h"
#include <set>
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Drawer.h"
#include <iostream>

WanderingCowState::WanderingCowState()
{
}


WanderingCowState::~WanderingCowState()
{
}

bool WanderingCowState::onMessage(Cow *entity, const Telegram &msg, Game &game)
{
	switch (msg.msg)
	{
		case MessageType::Msg_PillUpgrade:
			std::cout << "Pill replied, cow now has pill! Lets chase" << std::endl;
			entity->changeState(&ChaseCowState::instance());
			return true;
	}

	return false;
}

void WanderingCowState::enter(Cow *entity, Game &game)
{
	game.getDrawer().setColorOverLay(entity->getName(), 0, 255, 0);
}

void WanderingCowState::update(Cow *entity, Game &game)
{
	if (!entity->hasPill()) {
		std::list<Edge*> edges = game.getGraph().getEdges(entity->getField()->getKey());

		Edge *edge = RandomGenerator::randomFromList<Edge*>(edges);

		if (edge != nullptr) {
			Vertex *newPlace = game.getGraph().getVertex(edge->getDestination());

			if (newPlace != nullptr) {
				std::set<GameObject*> objData = newPlace->getData();

				if (objData.size() > 0) {
					//std::cout << "MSG to all objects on vertex: CowVisiting" << std::endl;
					for (auto it : objData) {
						Dispatch.dispatchMessage(0.0, entity->getId(), it->getId(), MessageType::Msg_CowVisiting, entity);
					}
				}

				newPlace->setData(*entity);
			}

		}
	}
}

void WanderingCowState::exit(Cow *entity, Game &game)
{

}
