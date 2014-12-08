#include "Rabbit.h"
#include "Game.h"
#include "Graph.h"
#include "Vertex.h"
#include "GlobalRabbitState.h"
#include "WanderingRabbitState.h"

Rabbit::~Rabbit()
{
	getField()->removeData(*this);
	delete _stateMachine;
}

void Rabbit::makeMachine(Game &game)
{
	_stateMachine = new StateMachine<Rabbit>(this, game);
	_stateMachine->setGlobalState(&GlobalRabbitState::instance());
	_stateMachine->changeState(&WanderingRabbitState::instance());
}


void Rabbit::update(Game &game)
{
	if (_stateMachine)
		_stateMachine->update();
}

bool Rabbit::handleMessage(const Telegram &msg)
{
	if (_stateMachine) {
		return _stateMachine->handleMessage(msg);
	}
	else
		return false;
}