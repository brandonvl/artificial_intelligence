#pragma once

#include <string>
#include <iostream>
#include "BaseGameEntity.h"

class Vertex;
class Game;

class GameObject : public BaseGameEntity
{
public:
	GameObject(const int id,const std::string &name) : BaseGameEntity(id), _name(name) {};
	~GameObject() {};
	std::string getName() { return _name; }
	Vertex *getField() { return _field; }
	void setField(Vertex *field) { _field = field; }
	virtual void update(Game &game) = 0;
	virtual bool handleMessage(const Telegram &msg) = 0;
private:
	std::string _name;
	Vertex *_field;
};

