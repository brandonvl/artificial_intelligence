#include "Cow.h"
#include "Game.h"
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "RandomGenerator.h"
#include "AStarSearch.h"
#include "SDL.h"
#include "Rabbit.h"

Cow::~Cow()
{
}

void Cow::update(Game &game)
{
	if (_rabbitFound && !_pathPrinted) {
		std::cout << "Rabbit found!" << std::endl;
		_pathPrinted = true;
		_path = AStarSearch::getShortestPath(game.getGraph(), getField()->getKey(), game.getRabbit().getField()->getKey());
		std::cout << "Source: " << getField()->getKey() << ", Target: " << game.getRabbit().getField()->getKey() << std::endl;
		std::cout << "Shortest path: (from -> to)" << std::endl;
		Vertex *from = getField();
		for (auto to : _path) {
			std::cout << from->getKey() << " -> " << to->getKey() << std::endl;
			from = to;
		}
	}
}

void Cow::moveRandom(Game &game)
{
	if (!_rabbitFound) {
		std::vector<Edge*> edges = getField()->getEdges();

		Edge *edge = RandomGenerator::randomFromVector<Edge*>(edges);

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