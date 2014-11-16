#pragma once

#include <string>
#include <iostream>

class Vertex;
class Game;

class GameObject
{
public:
	GameObject(const std::string &name) : _name(name) {};
	~GameObject() {};
	std::string getName() { return _name; }
	Vertex *getField() { return _field; }
	void setField(Vertex *field) { _field = field; }
	virtual void update(Game &game) = 0;
	virtual void moveRandom(Game &game) = 0;
private:
	std::string _name;
	Vertex *_field;
};

