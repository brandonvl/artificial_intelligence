#pragma once
#include "GameObject.h"
#include <stack>
#include "StateMachine.h"

class Vertex;

class Cow :
	public GameObject
{
private:
	StateMachine<Cow> *_stateMachine;
	std::stack<Vertex*> _path;
	bool _rabbitFound = false;
	bool _pathPrinted = false;

public:
	Cow() : GameObject(1,"cow") { };
	virtual ~Cow();
	void update(Game &game) override;
	void moveRandom(Game &game) override;
};

