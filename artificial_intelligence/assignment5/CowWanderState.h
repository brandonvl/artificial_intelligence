#pragma once
#include "State.h"
#include "Cow.h"

#include <string>

class Game;
struct Telegram;

class CowWanderState : public State<Cow>
{
private:
	void chooseOption(Cow *entity, Game &game);
public:
	virtual bool onMessage(Cow *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Cow *entity, Game &game) override;
	virtual void update(Cow *entity, Game &game) override;
	virtual void exit(Cow *entity, Game &game) override;

	CowWanderState();
	virtual ~CowWanderState() {}

	static CowWanderState &instance() {
		static CowWanderState instance;
		return instance;
	}

};