#pragma once

class Game;
struct Telegram;

class BaseGameEntity
{
private:

	int _id;

	static int _nextValidId;

	void setID(int id);

public:
	BaseGameEntity(int id) { setID(id); }
	virtual ~BaseGameEntity() { }
	virtual bool handleMessage(const Telegram &msg) = 0;
	virtual void update(Game &game) = 0;

	int getId() const { return _id; }
};
