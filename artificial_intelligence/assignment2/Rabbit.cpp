#include "Rabbit.h"
#include "Game.h"
#include "Graph.h"
#include "Vertex.h"


Rabbit::~Rabbit()
{

}

void Rabbit::update(Game &game)
{

}

void Rabbit::moveRandom(Game &game)
{
	Vertex *newVertex = game.getGraph().getRandomVertex(getField()->getKey());

	if (newVertex != nullptr) {
		newVertex->setData(*this);
	}
}