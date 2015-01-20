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
	Rabbit(Game &game);
	void respawn();
	virtual ~Rabbit();
	virtual void update(Game &game, const double &time_elapsed) override;
	virtual bool handleMessage(const Telegram &msg) override;
	virtual void draw(Game &game) override;
};