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
	bool _rabbitFound = false, _pathPrinted = false;

public:
	Cow() : GameObject(1,"cow") { };
	void makeMachine(Game &game);
	virtual ~Cow();
	void update(Game &game) override;
	StateMachine<Cow> *getFSM() { return _stateMachine; }
	void changeState(State<Cow> *newState) { _stateMachine->changeState(newState); }
	virtual bool handleMessage(const Telegram &msg) override;
};

