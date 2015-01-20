#pragma once
#include "Vehicle.h"
#include "StateMachine.h"

class Cow :
	public Vehicle
{
private:
	StateMachine<Cow> *_stateMachine;
	void makeMachine(Game &game);
	bool _invulnerable = false, _hasPill = false, _hasWeapon = false;
	int _hideChance = 25, _seekPillChance = 25, _seekWeaponChance = 25, _fleeChance = 25;

public:
	bool isInvulnerable() { return _invulnerable; }
	bool hasPill() { return _hasPill; }
	bool hasWeapon() { return _hasWeapon; }
	void setPill(bool hasPill = true) { _hasPill = hasPill; }
	void setWeapon(bool hasWeapon = true) { _hasWeapon = hasWeapon; }
	void setInvulnerable(bool invulnerable = true) { _invulnerable = invulnerable; }
	int getHideChance() { return _hideChance; }
	int getSeekPillChance() { return _seekPillChance; }
	int getSeekWeaponChance() { return _seekWeaponChance; }
	int getFleeChance() { return _fleeChance; }
	void normalizeChancesTo100Scale();
	StateMachine<Cow> &getStateMachine() { return *_stateMachine; }
	void respawn();
	Cow(Game &game);
	virtual ~Cow();
	virtual void update(Game &game, const double &time_elapsed) override;
	virtual bool handleMessage(const Telegram &msg) override;
	virtual void draw(Game &game) override;
};

