#pragma once
#include "Vehicle.h"
#include "StateMachine.h"

class Cow :
	public Vehicle
{
private:
	StateMachine<Cow> *_stateMachine;
	void makeMachine(Game &game);
public:
	StateMachine<Cow> &getStateMachine() { return *_stateMachine; }
	Cow(Game &game);
	virtual ~Cow();
	virtual void update(Game &game, const double &time_elapsed) override;
	virtual void draw(Game &game) override;
};

