#pragma once
#include "State.h"

class Cow;
class Game;
struct Telegram;

class CowChasePillState :
	public State<Cow>
{
public:
	virtual bool onMessage(Cow *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Cow *entity, Game &game) override;
	virtual void update(Cow *entity, Game &game) override;
	virtual void exit(Cow *entity, Game &game) override;

	CowChasePillState();
	virtual ~CowChasePillState() {}

	static CowChasePillState &instance() {
		static CowChasePillState instance;
		return instance;
	}
};

