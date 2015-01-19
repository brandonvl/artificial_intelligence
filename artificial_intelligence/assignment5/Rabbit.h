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
	double getPanicDistance() { return 70 * 70; }
	double getSafeDistance() { return 150 * 150; }
	int getWanderSpeed() { return 150; }
	int getFleeSpeed() { return 250; }
	Rabbit(Game &game);
	virtual ~Rabbit();
	virtual void update(Game &game, const double &time_elapsed) override;
	virtual void draw(Game &game) override;
};