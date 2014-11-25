#include "Rabbit.h"
#include "Game.h"
#include "Graph.h"
#include "Vertex.h"


Rabbit::~Rabbit()
{
	delete _stateMachine;
}

void Rabbit::update(Game &game)
{
	if (_stateMachine)
		_stateMachine->update(game);
}

void Rabbit::moveRandom(Game &game)
{
	Vertex *newVertex = game.getGraph().getRandomVertex(getField()->getKey());

	if (newVertex != nullptr) {
		newVertex->setData(*this);
	}
}