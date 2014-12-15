#pragma once
#include "State.h"
#include <stack>

class Rabbit;
class Vertex;

class ChaseWeaponRabbitState :
	public State<Rabbit>
{
public:
	ChaseWeaponRabbitState();
	virtual ~ChaseWeaponRabbitState();
public:


	virtual bool onMessage(Rabbit *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Rabbit *entity, Game &game) override;
	virtual void update(Rabbit *entity, Game &game) override;
	virtual void exit(Rabbit *entity, Game &game) override;

	static ChaseWeaponRabbitState &instance() {
		static ChaseWeaponRabbitState _instance;
		return _instance;
	}
};

