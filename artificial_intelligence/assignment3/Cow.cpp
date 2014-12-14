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
#include "GlobalCowState.h"
#include "ChaseCowState.h"

Cow::~Cow()
{
	delete _stateMachine;
}

void Cow::makeMachine(Game &game)
{
	_stateMachine = new StateMachine<Cow>(this, game);
	_stateMachine->setGlobalState(&GlobalCowState::instance());
	_stateMachine->changeState(&ChaseCowState::instance());
}

void Cow::update(Game &game)
{
	/*if (_rabbitFound && !_pathPrinted) {
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
	}*/

	_stateMachine->update();
}

bool Cow::handleMessage(const Telegram &msg)
{
	if (_stateMachine) {
		return _stateMachine->handleMessage(msg);
	}
	else
		return false;
}