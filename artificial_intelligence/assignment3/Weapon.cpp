#include "Weapon.h"
#include "Vertex.h"
#include "GlobalWeaponState.h"

Weapon::~Weapon()
{
	getField()->removeData(*this);
	delete _stateMachine;
}

void Weapon::update(Game &game)
{

}


bool Weapon::handleMessage(const Telegram &msg)
{
	if (_stateMachine)
		return _stateMachine->handleMessage(msg);
	else
		return false;
}

void Weapon::makeMachine(Game &game)
{
	_stateMachine = new StateMachine<Weapon>(this, game);
	_stateMachine->setGlobalState(&GlobalWeaponState::instance());
}
