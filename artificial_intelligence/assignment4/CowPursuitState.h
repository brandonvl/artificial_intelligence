#pragma once
#include "State.h"
#include <string>

class Game;
class Cow;
struct Telegram;

class CowPursuitState : public State<Cow>
{

public:

	virtual bool onMessage(Cow *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Cow *entity, Game &game) override;
	virtual void update(Cow *entity, Game &game) override;
	virtual void exit(Cow *entity, Game &game) override;

	const std::string getName() const { return _name; }

	CowPursuitState(std::string name);
	virtual ~CowPursuitState() {}
};