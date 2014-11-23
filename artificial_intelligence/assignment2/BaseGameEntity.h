#pragma once

class Game;

class BaseGameEntity
{
private:

	int _id;

	static int _nextValidId;

public:
	BaseGameEntity();
	virtual ~BaseGameEntity() { }

	virtual void update(Game &game) = 0;

	int getId() const { return _id; }
};

