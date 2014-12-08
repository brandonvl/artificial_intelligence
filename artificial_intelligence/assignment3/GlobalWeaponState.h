#pragma once
#include "State.h"

class Weapon;
class GlobalWeaponState :
	public State<Weapon>
{
private:
	GlobalWeaponState();
	virtual ~GlobalWeaponState();

public:
	virtual bool onMessage(Weapon *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Weapon *entity, Game &game) override;
	virtual void update(Weapon *entity, Game &game) override;
	virtual void exit(Weapon *entity, Game &game) override;

	static GlobalWeaponState &instance() {
		static GlobalWeaponState _instance;
		return _instance;
	}
};

