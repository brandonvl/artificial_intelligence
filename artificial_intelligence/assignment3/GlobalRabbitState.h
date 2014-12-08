#pragma once
#include "State.h"
class Rabbit;

class GlobalRabbitState : public State<Rabbit>
{
private:
	GlobalRabbitState();
	virtual ~GlobalRabbitState();

public:
	virtual bool onMessage(Rabbit *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Rabbit *entity, Game &game) override;
	virtual void update(Rabbit *entity, Game &game) override;
	virtual void exit(Rabbit *entity, Game &game) override;

	static GlobalRabbitState &instance() {
		static GlobalRabbitState _instance;
		return _instance;
	}
};

