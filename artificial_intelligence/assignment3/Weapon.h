#pragma once
#include "GameObject.h"
#include "StateMachine.h"

class Weapon :
	public GameObject
{
private:
	StateMachine<Weapon> *_stateMachine;

public:
	Weapon() : GameObject(4, "weapon") { };
	virtual ~Weapon();
	void makeMachine(Game &game);
	void update(Game &game) override;
	virtual bool handleMessage(const Telegram &msg) override;
};

