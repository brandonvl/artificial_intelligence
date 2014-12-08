#pragma once
#include "GameObject.h"
#include <stack>
#include "StateMachine.h"
#include "State.h"

class Vertex;
class Game;

class Cow :
	public GameObject
{
private:
	StateMachine<Cow> *_stateMachine;
	std::stack<Vertex*> _path;
	bool _rabbitFound = false;
	bool _pathPrinted = false;
	bool _hasPill = false;

public:
	Cow() : GameObject(1,"cow") { };
	void makeMachine(Game &game);
	virtual ~Cow();
	void setPillUpgrade(const bool value = true) { _hasPill = value; }
	void update(Game &game) override;
	StateMachine<Cow> *getFSM() { return _stateMachine; }
	void changeState(State<Cow> *newState) { _stateMachine->changeState(newState); }
	virtual bool handleMessage(const Telegram &msg) override;
	bool hasPill() { return _hasPill; }
};

