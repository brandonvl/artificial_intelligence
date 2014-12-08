#pragma once
#include "GameObject.h"
#include "StateMachine.h"

class Pill :
	public GameObject
{
private:
	StateMachine<Pill> *_stateMachine;

public:
	Pill() : GameObject(3, "pill") { };
	virtual ~Pill();
	void makeMachine(Game &game);
	void update(Game &game) override;
	virtual bool handleMessage(const Telegram &msg) override;
};

