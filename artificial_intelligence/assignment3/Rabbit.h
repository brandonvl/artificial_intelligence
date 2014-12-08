#pragma once
#include "GameObject.h"
#include "StateMachine.h"
#include "State.h"

class Game;

class Rabbit :
	public GameObject
{
private:
	StateMachine<Rabbit> *_stateMachine;
	bool _hasWeapon = false;

public:
	Rabbit() : GameObject(2, "rabbit") {};
	virtual ~Rabbit();
	void makeMachine(Game &game);
	void update(Game &game) override;
	bool hasWeapon() { return _hasWeapon; }
	void setWeapon(const bool value = true) { _hasWeapon = value; }
	StateMachine<Rabbit> *getFSM() { return _stateMachine; }
	virtual bool handleMessage(const Telegram &msg) override;
	void changeState(State<Rabbit> *newState) { _stateMachine->changeState(newState); }
};

