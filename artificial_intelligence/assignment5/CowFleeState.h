#pragma once
#include "State.h"
#include "Cow.h"

#include <string>

class Game;
struct Telegram;

class CowFleeState : public State<Cow>
{
public:
	virtual bool onMessage(Cow *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Cow *entity, Game &game) override;
	virtual void update(Cow *entity, Game &game) override;
	virtual void exit(Cow *entity, Game &game) override;

	CowFleeState();
	virtual ~CowFleeState() {}

	static CowFleeState &instance() {
		static CowFleeState instance;
		return instance;
	}
};