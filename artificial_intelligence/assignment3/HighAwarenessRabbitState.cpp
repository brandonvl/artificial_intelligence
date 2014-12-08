#include "HighAwarenessRabbitState.h"
#include "Game.h"
#include "Rabbit.h"
#include "Drawer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Graph.h"
#include "Edge.h"
#include <list>
#include "Vertex.h"
#include "RandomGenerator.h"

HighAwarenessRabbitState::HighAwarenessRabbitState()
{
}


HighAwarenessRabbitState::~HighAwarenessRabbitState()
{
}

bool HighAwarenessRabbitState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	switch (msg.msg)
	{
		case MessageType::Msg_ChasingCowPresent:
			_receivedChasingCowMessage = true;
			return true;
		case MessageType::Msg_ChasingCowVisiting:
			std::cout << "Rabbit got caught, but had a weapon!" << std::endl;
			doTeleport(entity, game, nullptr);
			return true;
	}

	return false;
}

void HighAwarenessRabbitState::enter(Rabbit *entity, Game &game)
{
	game.getDrawer().setColorOverLay(entity->getName(), 0, 128, 128);
}

void HighAwarenessRabbitState::update(Rabbit *entity, Game &game)
{
	std::set<int> attemped;
	std::list<Edge*> edges = game.getGraph().getEdges(entity->getField()->getKey());
	std::vector<int> candidates;
	for (auto it : edges)
	{
		candidates.push_back(it->getDestination());
	}

	Vertex *newPlace = nullptr;

	do
	{
		_receivedChasingCowMessage = false;
		auto candidate = candidates.begin() + RandomGenerator::random(0, candidates.size() - 1);
		if (candidate != candidates.end()) {
			newPlace = game.getGraph().getVertex(*candidate);

			if (newPlace != nullptr) {
				std::set<GameObject*> objData = newPlace->getData();

				if (objData.size() > 0) {
					std::cout << "Rabbit peeking to see if there is a chasing cow!" << std::endl;
					for (auto it : objData) {
						Dispatch.dispatchMessage(0.0, entity->getId(), it->getId(), MessageType::Msg_RabbitPeeking, entity);
					}
				}

				if (_receivedChasingCowMessage) {
					attemped.insert(*candidate);
					candidates.erase(candidate);
				}
			}
		}
	} while (_receivedChasingCowMessage && candidates.size() > 0);

	if (attemped.size() == edges.size()) {
		attemped.insert(entity->getField()->getKey());
		doTeleport(entity, game, &attemped);
	}
	else
		newPlace->setData(*entity);
}

void HighAwarenessRabbitState::exit(Rabbit *entity, Game &game)
{

}

void HighAwarenessRabbitState::doTeleport(Rabbit *entity, Game &game, std::set<int> *attempts)
{
	std::cout << "Rabbit teleporting, thus losing it's status!" << std::endl;
	Vertex *destination = game.getGraph().getRandomVertex(attempts);

	if (destination != nullptr) {
		destination->setData(*entity);
	}

	entity->setWeapon(false);
	entity->getFSM()->revertToPreviousState();
}