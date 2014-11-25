#include "Cow.h"
#include "Game.h"
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "RandomGenerator.h"
#include "AStarSearch.h"
#include "SDL.h"
#include "Rabbit.h"
#include "EntityManager.h"

Cow::~Cow()
{
	delete _stateMachine;
}

void Cow::update(Game &game)
{
	if (_rabbitFound && !_pathPrinted) {
		std::cout << "Rabbit found!" << std::endl;
		_pathPrinted = true;
		_path = AStarSearch::getShortestPath(game.getGraph(), getField()->getKey(), game.getRabbit().getField()->getKey());
		std::cout << "Source: " << getField()->getKey() << ", Target: " << game.getRabbit().getField()->getKey() << std::endl;
		std::cout << "Shortest path: (from -> to)" << std::endl;
		//Vertex *from = getField();
		while (!_path.empty()) {
			Vertex *item = _path.top();
			std::cout << item->getKey() << std::endl;
			_path.pop();
		}
	}
	else if (!_rabbitFound) {
		moveRandom(game);
	}
}

void Cow::moveRandom(Game &game)
{
	if (!_rabbitFound) {
		std::list<Edge*> edges = game.getGraph().getEdges(getField()->getKey());

		Edge *edge = RandomGenerator::randomFromList<Edge*>(edges);

		if (edge != nullptr) {
			Vertex *newPlace = game.getGraph().getVertex(edge->getDestination());

			if (newPlace != nullptr) {
				GameObject *objData = newPlace->getData();

				if (objData != nullptr) {
					if (objData->getName() == "rabbit") {
						_rabbitFound = true;
						objData->moveRandom(game);
					}
				}

				newPlace->setData(*this);
			}
				
		}
	}
}