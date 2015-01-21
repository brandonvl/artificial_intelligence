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
	double _hideChance = 0.0, _seekPillChance = 0.0, _seekWeaponChance = 0.0, _fleeChance = 0.0;

public:
	void setChances(double hide, double seekPill, double seekWeapon, double flee);
	bool isInvulnerable() { return _invulnerable; }
	bool hasPill() { return _hasPill; }
	bool hasWeapon() { return _hasWeapon; }
	void setPill(bool hasPill = true) { _hasPill = hasPill; }
	void setWeapon(bool hasWeapon = true) { _hasWeapon = hasWeapon; }
	void setInvulnerable(bool invulnerable = true) { _invulnerable = invulnerable; }
	double getHideChance() { return _hideChance; }
	double getSeekPillChance() { return _seekPillChance; }
	double getSeekWeaponChance() { return _seekWeaponChance; }
	double getFleeChance() { return _fleeChance; }
	void normalizeChancesTo100Scale();
	StateMachine<Cow> &getStateMachine() { return *_stateMachine; }
	void respawn();
	Cow(Game &game);
	virtual ~Cow();
	virtual void update(Game &game, const double &time_elapsed) override;
	virtual bool handleMessage(const Telegram &msg) override;
	virtual void draw(Game &game) override;
};

