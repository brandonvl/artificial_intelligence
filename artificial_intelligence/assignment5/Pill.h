#pragma once
#include "Vehicle.h"
class Pill :
	public Vehicle
{
public:
	Pill();
	virtual ~Pill();
	virtual void update(Game &game, const double &time_elapsed) override;
	virtual void draw(Game &game) override;
};

