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
	bool _hasWeapon = false, _hasPill = false;// , _hadPill = false;

	// chance distribution
	int _runChance = 30, _searchWeaponChance = 30, _searchPillChance = 30;

	const int
		CHANCE_SCALE_FACTOR = 10,
		CHANCE_BOUNDS_MIN = 5,
		CHANCE_BOUNDS_MAX = 100;

	void validateChances();

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
	void setPillUpgrade(const bool value = true) { _hasPill = value; }
	bool hasPill() { return _hasPill; }
	//bool hadPill() { return _hadPill; }

	const int getRunChance() { return _runChance; }
	const int getSearchWeaponChance() { return _searchWeaponChance; }
	const int getSearchPillChance() { return _hasPill ? 0 : _searchPillChance; }

	void updateRunChance(bool success);
	void updateSearchWeaponChance(bool success);
	void updateSearchPillChance(bool success);

};

