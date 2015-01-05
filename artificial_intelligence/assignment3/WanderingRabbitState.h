#pragma once
#include "State.h"

class Rabbit;

class WanderingRabbitState :
	public State<Rabbit>
{
private:
	WanderingRabbitState();
	virtual ~WanderingRabbitState();
	bool _receivedChasingCowMessage;

	const int ACTION_RANGE = 2;

	bool lookAround(Rabbit *entity, Game &game);
	bool isNextToCow(Rabbit *entity, Game &game, int fieldKey);
	void wander(Rabbit *entity, Game &game);
public:
	virtual bool onMessage(Rabbit *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Rabbit *entity, Game &game) override;
	virtual void update(Rabbit *entity, Game &game) override;
	virtual void exit(Rabbit *entity, Game &game) override;

	static WanderingRabbitState &instance() {
		static WanderingRabbitState _instance;
		return _instance;
	}
};

