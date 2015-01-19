#pragma once
#include "Vehicle.h"
class Weapon :
	public Vehicle
{
public:
	Weapon();
	virtual ~Weapon();
	virtual void update(Game &game, const double &time_elapsed) override;
	virtual void draw(Game &game) override;
};

