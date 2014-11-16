#pragma once
#include "GameObject.h"
class Rabbit :
	public GameObject
{
public:
	Rabbit() : GameObject("rabbit") {};
	virtual ~Rabbit();
	void update(Game &game) override;
	void moveRandom(Game &game) override;
};

