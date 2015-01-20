#pragma once
#include "Vehicle.h"
#include "StateMachine.h"

class Rabbit :
	public Vehicle
{
private:
	StateMachine<Rabbit> *_stateMachine;
	void makeMachine(Game &game);
public:
	StateMachine<Rabbit> &getStateMachine() { return *_stateMachine; }
	int getPursuitSpeed() { return 200; }
	Rabbit(Game &game);
	virtual ~Rabbit();
	virtual void update(Game &game, const double &time_elapsed) override;
	virtual void draw(Game &game) override;
};