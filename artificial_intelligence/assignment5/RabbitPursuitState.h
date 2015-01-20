#pragma once
#include "State.h"
#include <string>

class Game;
class Rabbit;
struct Telegram;

class RabbitPursuitState : public State<Rabbit>
{

public:

	virtual bool onMessage(Rabbit *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Rabbit *entity, Game &game) override;
	virtual void update(Rabbit *entity, Game &game) override;
	virtual void exit(Rabbit *entity, Game &game) override;

	const std::string getName() const { return _name; }

	RabbitPursuitState(std::string name);
	virtual ~RabbitPursuitState() {}
};