#pragma once
#include "GameObject.h"
#include "StateMachine.h"

class Rabbit :
	public GameObject
{
private:
	StateMachine<Rabbit> *_stateMachine;

public:
	Rabbit() : GameObject(2, "rabbit") {};
	virtual ~Rabbit();
	void update(Game &game) override;
	void moveRandom(Game &game) override;
};

