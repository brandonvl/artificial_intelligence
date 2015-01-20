#pragma once
#include "State.h"
#include "Cow.h"

#include <string>

class Game;
struct Telegram;

class CowWanderState : public State<Cow>
{
public:
	virtual bool onMessage(Cow *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Cow *entity, Game &game) override;
	virtual void update(Cow *entity, Game &game) override;
	virtual void exit(Cow *entity, Game &game) override;

	const std::string getName() const { return _name; }

	CowWanderState(std::string name);
	virtual ~CowWanderState() {}
};