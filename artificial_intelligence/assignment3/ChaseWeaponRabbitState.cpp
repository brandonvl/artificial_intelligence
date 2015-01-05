#include "ChaseWeaponRabbitState.h"
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
#include "Weapon.h"
#include "WanderingRabbitState.h"
#include "Cow.h"

ChaseWeaponRabbitState::ChaseWeaponRabbitState() : State<Rabbit>("ChaseWeaponRabbitState")
{
}


ChaseWeaponRabbitState::~ChaseWeaponRabbitState()
{
}

bool ChaseWeaponRabbitState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	return false;
}

void ChaseWeaponRabbitState::enter(Rabbit *entity, Game &game)
{
	game.getDrawer().setColorOverLay(entity->getName(), 150, 10, 200);
}

void ChaseWeaponRabbitState::update(Rabbit *entity, Game &game)
{
	if (!entity->hasWeapon()) {

		std::stack<Vertex*> path = AStarSearch::getShortestPath(game.getGraph(), entity->getField()->getKey(), game.getWeapon().getField()->getKey(), &game.getCow());

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
		entity->changeState(&ChaseWeaponRabbitState::instance());

}

void ChaseWeaponRabbitState::exit(Rabbit *entity, Game &game)
{
}
