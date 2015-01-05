#include "ChaseCowRabbitState.h"
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
#include "EntityManager.h"
#include "Weapon.h"

ChaseCowRabbitState::ChaseCowRabbitState() : State<Rabbit>("ChaseCowRabbitState")
{
}


ChaseCowRabbitState::~ChaseCowRabbitState()
{
}

bool ChaseCowRabbitState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	switch (msg.msg)
	{
	case MessageType::Msg_CowCaught:
		std::cout << "Headshot! Rabbit shot the cow.\n";
		_receivedCowCaughtMessage = true;
		entity->setWeapon(false);

		game.respawn(game.getWeapon());
		game.respawn(game.getCow());
		entity->changeState(&WanderingRabbitState::instance());
		return true;
	}

	return false;
}

void ChaseCowRabbitState::enter(Rabbit *entity, Game &game)
{
	game.getDrawer().setColorOverLay(entity->getName(), 150, 240, 50);
}

void ChaseCowRabbitState::update(Rabbit *entity, Game &game)
{
	if (entity->hasWeapon()) {

		_receivedCowCaughtMessage = false;

		std::stack<Vertex*> path = AStarSearch::getShortestPath(game.getGraph(), entity->getField()->getKey(), game.getCow().getField()->getKey());

		if (path.size() > 0) {
			Vertex *newPlace = game.getGraph().getVertex(path.top()->getKey());

			if (newPlace != nullptr) {
				std::set<GameObject*> objData = newPlace->getData();

				if (objData.size() > 0) {
					//std::cout << "MSG to all objects on vertex: RabbitVisiting" << std::endl;
					for (auto it : objData) {
						Dispatch.dispatchMessage(0.0, entity->getId(), it->getId(), MessageType::Msg_ChasingRabbitVisiting, entity);

						if (_receivedCowCaughtMessage) return;
					}
				}

				newPlace->setData(*entity);
			}
		}

	}
	else entity->changeState(&WanderingRabbitState::instance());
}

void ChaseCowRabbitState::exit(Rabbit *entity, Game &game)
{
}
