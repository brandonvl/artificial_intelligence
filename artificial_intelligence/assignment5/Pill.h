#pragma once
#include "Vehicle.h"
class Pill :
	public Vehicle
{
public:
	Pill(Game &game);
	virtual ~Pill();
	void respawn();
	virtual void update(Game &game, const double &time_elapsed) override;
	virtual void draw(Game &game) override;
};

