#include "Pill.h"
#include "GlobalPillState.h"
#include "Vertex.h"

Pill::~Pill()
{
	getField()->removeData(*this);
	delete _stateMachine;
}

void Pill::update(Game &game)
{

}

bool Pill::handleMessage(const Telegram &msg)
{
	if (_stateMachine) {
		return _stateMachine->handleMessage(msg);
	}
	else
		return false;
}

void Pill::makeMachine(Game &game)
{
	_stateMachine = new StateMachine<Pill>(this, game);
	_stateMachine->setGlobalState(&GlobalPillState::instance());
}
