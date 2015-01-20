#pragma once
#include "Vehicle.h"
#include "StateMachine.h"

class Cow :
	public Vehicle
{
private:
	StateMachine<Cow> *_stateMachine;
	void makeMachine(Game &game);
	bool _invulnerable = false;
public:
	bool isInvulnerable() { return _invulnerable; }
	StateMachine<Cow> &getStateMachine() { return *_stateMachine; }
	int getWanderSpeed() { return 100; }
	int getFleeSpeed() { return 100; }
	Cow(Game &game);
	virtual ~Cow();
	virtual void update(Game &game, const double &time_elapsed) override;
	virtual void draw(Game &game) override;
};

