#pragma once

class Game;

class BaseGameEntity
{
private:

	int _id;

	static int _nextValidId;

	void setID(int id) {

	};
public:
	BaseGameEntity(int id) { setID(id); }
	virtual ~BaseGameEntity() { }

	virtual void update(Game &game) = 0;

	int getId() const { return _id; }
};

